// openfst-pybind/openfst-pybind.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#include "openfst-pybind/openfst-pybind.h"

#include "openfst-pybind/float-weight.h"

PYBIND11_MODULE(fst, m) {
  m.doc() = "pybind11 binding of Openfst";
  PybindFloatWeight(m);
}
