# Source: https://eb2.co/blog/2012/03/sphinx-and-cmake-beautiful-documentation-for-c---projects/

find_program(
  SPHINX_EXECUTABLE
  NAMES sphinx-build
  HINTS $ENV{SPHINX_DIR}
  PATH_SUFFIXES bin
  DOC "Sphinx documentation generator"
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
  Sphinx
  DEFAULT_MSG
  SPHINX_EXECUTABLE
)

option(
  SPHINX_OUTPUT_HTML
  "Output stand-alone HTML files"
  ON
)

option(
  SPHINX_OUTPUT_MAN
  "Output man pages"
  OFF
)

mark_as_advanced(SPHINX_EXECUTABLE)
