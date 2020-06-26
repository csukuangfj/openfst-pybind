# please sort the files in alphabetic order
pybind11_add_module(fst
  float-weight.cc
  openfst-pybind.cc
)

target_include_directories(fst PRIVATE ${CMAKE_SOURCE_DIR})

if(CMAKE_VERSION VERSION_LESS 3.8)
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
else()
  target_compile_features(fst PRIVATE cxx_std_11)
endif()

target_link_libraries(fst PRIVATE openfst::openfst)
