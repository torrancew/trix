# Derived from http://llvm.org/svn/llvm-project/llvm/trunk/cmake/modules/AddSphinxTarget.cmake

function(sphinx_add_docs targetName builder filesOrDirs)
  set(SPHINX_BUILD_DIR   "${CMAKE_CURRENT_BINARY_DIR}/${builder}")
  set(SPHINX_DOCTREE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_doctrees")

  add_custom_target(
    ${targetName} ALL
    COMMAND ${SPHINX_EXECUTABLE}
            -b ${builder}
            -d "${SPHINX_DOCTREE_DIR}"
            -q
            "${filesOrDirs}"
            "${SPHINX_BUILD_DIR}"
    COMMENT "Generating ${builder} documentation with Sphinx"
  )

  set_property(
    DIRECTORY APPEND PROPERTY
    ADDITIONAL_MAKE_CLEAN_FILES
    "${SPHINX_BUILD_DIR}"
  )

  get_property(
    _CURRENT_MAKE_CLEAN_FILES
    DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  )

  list(FIND _CURRENT_MAKE_CLEAN_FILES "${SPHINX_DOCTREE_DIR}" _INDEX)
  if (_INDEX EQUAL -1)
    set_property(
      DIRECTORY APPEND PROPERTY
      ADDITIONAL_MAKE_CLEAN_FILES
      "${SPHINX_DOCTREE_DIR}"
    )
  endif()

endfunction(sphinx_add_docs)
