# Project metadata

project = '@PROJECT_NAME@'
copyright = '@COWL_COPYRIGHT_YEAR@, @COWL_VENDOR@'
author = '@COWL_VENDOR@'
version = '@PROJECT_VERSION@'
release = '@PROJECT_VERSION@'
logo = '@COWL_ICON@'
git_url = '@COWL_GIT_URL@'

# Sphinx

primary_domain = 'cpp'
default_role = 'any'
extensions = ['breathe']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']
rst_prolog = """
:github_url: @COWL_GIT_URL@
"""
rst_epilog = """
.. _git_url: @COWL_GIT_URL@
"""

# HTML

html_theme = 'sphinx_rtd_theme'
html_theme_options = { 'logo_only': False }
templates_path = ['@SPHINX_INPUT_DIRECTORY@/_templates']
html_static_path = ['@SPHINX_INPUT_DIRECTORY@/_static', '@DOCS_IMAGES_DIRECTORY@']
html_logo = logo
html_short_title = '{} docs'.format(project)
html_copy_source = False
html_show_sphinx = False
html_use_index = False

# Breathe

breathe_projects = { project: '@DOXYGEN_XML_OUTPUT_DIRECTORY@' }
breathe_default_project = project
breathe_default_members = ('members', 'undocmembers')

# Setup

def setup(app):
    app.add_css_file('style.css')
