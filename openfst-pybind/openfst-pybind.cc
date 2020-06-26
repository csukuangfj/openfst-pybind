// openfst-pybind/openfst-pybind.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#include "openfst-pybind/openfst-pybind.h"

#include "openfst-pybind/arc.h"
#include "openfst-pybind/const-fst.h"
#include "openfst-pybind/float-weight.h"
#include "openfst-pybind/fst.h"
#include "openfst-pybind/symbol-table.h"
#include "openfst-pybind/vector-fst.h"
#include "openfst-pybind/weight.h"

PYBIND11_MODULE(fst, m) {
  m.doc() = "pybind11 binding of Openfst";
  PybindFloatWeight(m);
  PybindArc(m);
  PybindWeight(m);
  PybindSymbolTable(m);
  PybindFst(m);
  PybindVectorFst(m);
  PybindConstFst(m);
}
