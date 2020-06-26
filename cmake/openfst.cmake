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
endfunction()

download_openfst()
