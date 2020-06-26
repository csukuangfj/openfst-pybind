// openfst-pybind/weight.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#include "openfst-pybind/weight.h"

#include "fst/weight.h"

using namespace fst;

void PybindWeight(py::module& m) { m.attr("kDelta") = kDelta; }
