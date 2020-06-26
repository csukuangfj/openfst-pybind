function(add_py_test source)
  get_filename_component(name ${source} NAME_WE)

  add_test(NAME ${name}
    COMMAND
      "${PYTHON_EXECUTABLE}"
      "${CMAKE_CURRENT_SOURCE_DIR}/${source}"
  )

  set_property(TEST ${name}
    PROPERTY ENVIRONMENT "PYTHONPATH=$<TARGET_FILE_DIR:fst>"
  )
endfunction()

# please sort the files in alphabetic order
set(py_test_files
  float-weight-test.py
  vector-fst-test.py
)

foreach(source IN LISTS py_test_files)
  add_py_test(${source})
endforeach()
