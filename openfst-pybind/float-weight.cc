// openfst-pybind/float-weight.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#include "openfst-pybind/float-weight.h"

#include "fst/float-weight.h"

using namespace fst;

template <typename T>
static void PybindFloatWeightTpl(py::module& m, const char* name) {
  using PyClass = FloatWeightTpl<T>;
  using ValueType = typename PyClass::ValueType;
  DEF_CLASS(name);
  DEF_INIT();
  pyclass.def(py::init<ValueType>());
  DEF(Hash);
  DEF_REF(Value);
}

void PybindFloatWeight(py::module& m) {
  PybindFloatWeightTpl<float>(m, "FloatWeight");
}
