# Copyright (c) 2020 Fangjun Kuang (csukuangfj@gmail.com)
# See ../LICENSE for clarification regarding multiple authors

function(download_openfst)
  if(CMAKE_VERSION VERSION_LESS 3.11)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
  endif()

  include(FetchContent)

  set(openfst_URL  "http://www.openfst.org/twiki/pub/FST/FstDownload/openfst-1.7.7.tar.gz")
  set(openfst_HASH "SHA256=3246eaff369d334f24a684e94918a2fda99d7e633a1081718bb4a3a3e9bcf3be")

  FetchContent_Declare(openfst
    URL               ${openfst_URL}
    URL_HASH          ${openfst_HASH}
  )

  FetchContent_GetProperties(openfst)
  if(NOT openfst_POPULATED)
    message(STATUS "Downloading openfst")
    FetchContent_Populate(openfst)
  endif()
  message(STATUS "openfst is downloaded to ${openfst_SOURCE_DIR}")

  set(openfst_install_dir ${openfst_BINARY_DIR})
  file(MAKE_DIRECTORY ${openfst_install_dir}/include)

  set(openfst_lib_files ${openfst_install_dir}/lib/libfst${CMAKE_SHARED_LIBRARY_SUFFIX})

  add_custom_command(
    OUTPUT ${openfst_lib_files}
    WORKING_DIRECTORY ${openfst_SOURCE_DIR}
    COMMENT "Configuring Openfst"
    COMMAND ./configure --prefix=${openfst_install_dir}
    COMMENT "Building Openfst"
    COMMAND make -j -s
    COMMENT "Install Openfst to ${openfst_SOURCE_DIR}/install"
    COMMAND make install
    COMMAND ls -l ${openfst_install_dir}/*

  )
  add_custom_target(build_openfst DEPENDS ${openfst_lib_files})

  add_library(openfst::openfst SHARED IMPORTED GLOBAL)
  set_property(TARGET openfst::openfst PROPERTY IMPORTED_LOCATION ${openfst_lib_files})
  add_dependencies(openfst::openfst build_openfst ${openfst_lib_files})
  target_include_directories(openfst::openfst INTERFACE "${openfst_install_dir}/include")
endfunction()

download_openfst()
