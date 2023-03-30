# Project metadata

project = '@PROJECT_NAME@'
copyright = '@COWL_COPYRIGHT_YEAR@, @COWL_VENDOR@'
author = '@COWL_VENDOR@'
version = '@PROJECT_VERSION@'
release = '@PROJECT_VERSION@'
logo = '@COWL_ICON@'
git_url = '@COWL_GIT_URL@'
poliba_url = 'http://www.poliba.it'
sisinflab_url = 'http://sisinflab.poliba.it'
swot_url = '@COWL_VENDOR_URL@'

# Sphinx

primary_domain = 'cpp'
default_role = 'any'
extensions = ['breathe', 'sphinx.ext.intersphinx']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']
rst_prolog = f':github_url: {git_url}'
rst_epilog = (
    f'.. _git_url: {git_url}\n'
    f'.. _swot_url: {swot_url}\n'
    f'.. _poliba_url: {poliba_url}\n'
)

# HTML

html_theme = 'sphinx_rtd_theme'
html_theme_options = {'logo_only': False}
templates_path = ['@SPHINX_INPUT_DIRECTORY@/_templates']
html_static_path = ['@SPHINX_INPUT_DIRECTORY@/_static', '@DOCS_IMAGES_DIRECTORY@']
html_logo = logo
html_short_title = f'{project} docs'
html_context = {
    'poliba_url': poliba_url,
    'sisinflab_url': sisinflab_url,
    'swot_url': swot_url
}
html_copy_source = False
html_show_sphinx = False
html_use_index = False

# Intersphinx

intersphinx_mapping = {
    'ulib': ('https://ivanobilenchi.com/docs/ulib', '@ULIB_DOCS_INVENTORY_FILE@')
}

# Breathe

breathe_projects = {project: '@DOXYGEN_XML_OUTPUT_DIRECTORY@'}
breathe_default_project = project
breathe_default_members = ('members', 'undocmembers')

# Setup

def setup(app):
    app.add_css_file('style.css')
