#
# Copyright (c) 2024 Ivano Bilenchi <https://ivanobilenchi.com>
# SPDX-License-Identifier: ISC
#
# This program allows replacing whatever is being documented by some docstring
# with something else. It is useful as a Doxygen input filter, as it allows documenting
# function-like macros as functions with type information.
#
# As an example, the following docstring:
#
# /**
#  * Returns the maximum between a and b.
#  * @param a First number.
#  * @param b Second number.
#  * @return Maximum between a and b.
#  * @alias T max(T a, T b);
#  */
# #define max(a, b) (((a) > (b)) ? (a) : (b))
#
# Will be replaced by:
#
# /**
#  * Returns the maximum between a and b.
#  * @param a First number.
#  * @param b Second number.
#  * @return Maximum between a and b.
#  */
# T max(T a, T b);
#
import sys

# Constants
COMMAND_PATTERNS = ('@', '\\')
ALIAS_COMMANDS = ('@alias ', '\\alias ')
DOC_SINGLE_LINE_PATTERN = '///'
DOC_BLOCK_START_PATTERN = '/**'
DOC_BLOCK_END_PATTERN = '*/'
DOC_BLOCK_CONT_PATTERN = '*'
DOC_BLOCK_STRIP = f' \t{DOC_BLOCK_CONT_PATTERN}'

# Exit codes
EXIT_OK = 0
EXIT_ERR = 1

# States
WRITING_UNTIL_DOC_BLOCK = 0
LOOKING_FOR_ALIAS = 1
ALIAS_CONTINUATION = 2
LOOKING_FOR_INSERTION = 3
FOUND_INSERTION = 4
DISCARDING_UNTIL_DOCSTRING = 5


class InputFilter:

    def __init__(self):
        self.alias: str | None = None
        self.state = LOOKING_FOR_ALIAS

    def _find_alias(self, line: str) -> bool:
        for cmd in ALIAS_COMMANDS:
            idx = line.find(cmd)
            if idx >= 0:
                idx += len(cmd)
                self.alias = line[idx:]
                return True
        return False

    def _alias_continuation(self, line: str) -> bool:
        line = line.lstrip(DOC_BLOCK_STRIP)
        for p in COMMAND_PATTERNS:
            if line.startswith(p):
                return False
        if line:
            self.alias += f' {line}'
        return True

    def _write_until_doc_block(self, line: str) -> str | None:
        sline = line.strip()
        if (sline.startswith(DOC_BLOCK_START_PATTERN) and
                not sline.endswith(DOC_BLOCK_END_PATTERN)):
            self.state = LOOKING_FOR_ALIAS
        return line

    def _look_for_alias(self, line: str) -> str | None:
        sline = line.strip()
        if sline.startswith(DOC_BLOCK_END_PATTERN):
            self.state = WRITING_UNTIL_DOC_BLOCK
        elif self._find_alias(sline):
            self.state = ALIAS_CONTINUATION
            line = None
        return line

    def _continue_alias(self, line: str) -> str | None:
        sline = line.strip()
        if sline.startswith(DOC_BLOCK_END_PATTERN):
            self.state = FOUND_INSERTION
        elif self._alias_continuation(sline):
            line = None
        else:
            self.state = LOOKING_FOR_INSERTION
        return line

    def _look_for_insertion(self, line: str) -> str | None:
        sline = line.strip()
        if sline.startswith(DOC_BLOCK_END_PATTERN):
            self.state = FOUND_INSERTION
        return line

    def _insert_alias(self) -> str | None:
        alias = self.alias + '\n'
        self.alias = None
        self.state = DISCARDING_UNTIL_DOCSTRING
        return alias

    def _discard_until_docstring(self, line: str) -> str | None:
        sline = line.strip()
        if sline.startswith(DOC_BLOCK_START_PATTERN):
            if sline.endswith(DOC_BLOCK_END_PATTERN):
                self.state = WRITING_UNTIL_DOC_BLOCK
            else:
                self.state = LOOKING_FOR_ALIAS
            self.state = LOOKING_FOR_ALIAS
        elif sline.startswith(DOC_SINGLE_LINE_PATTERN):
            self.state = WRITING_UNTIL_DOC_BLOCK
        else:
            line = None
        return line

    def _compute_state_transition(self, line: str) -> str | None:
        if self.state == WRITING_UNTIL_DOC_BLOCK:
            return self._write_until_doc_block(line)
        elif self.state == LOOKING_FOR_ALIAS:
            return self._look_for_alias(line)
        elif self.state == ALIAS_CONTINUATION:
            return self._continue_alias(line)
        elif self.state == LOOKING_FOR_INSERTION:
            return self._look_for_insertion(line)
        elif self.state == FOUND_INSERTION:
            return self._insert_alias()
        else:  # self.state == DISCARDING_UNTIL_DOCSTRING
            return self._discard_until_docstring(line)

    def filter_line(self, line: str) -> None:
        line = self._compute_state_transition(line)
        if line:
            print(line, end='')


def main() -> int:
    if len(sys.argv) < 2:
        print('Usage: python alias.py <input_file>', file=sys.stderr)
        return EXIT_ERR

    input_filter = InputFilter()

    with open(sys.argv[1]) as input_file:
        for line in input_file:
            input_filter.filter_line(line)

    return EXIT_OK


if __name__ == '__main__':
    try:
        sys.exit(main())
    except Exception as e:
        print(str(e), file=sys.stderr)
        sys.exit(EXIT_ERR)
