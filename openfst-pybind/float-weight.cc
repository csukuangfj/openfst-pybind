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

template <typename T>
static void PybindTropicalWeightTpl(py::module& m, const char* name) {
  using PyClass = TropicalWeightTpl<T>;
  using ValueType = typename PyClass::ValueType;
  py::class_<PyClass, FloatWeightTpl<T>> pyclass(m, name);

  DEF_INIT();
  pyclass.def(py::init<ValueType>());
  DEF_STATIC(Zero);
  DEF_STATIC(One);
  DEF_STATIC(NoWeight);
  DEF_STATIC(Type);
  DEF(Member);
  DEF(Quantize, py::arg("delta") = kDelta);
  DEF(Reverse);
  DEF_STATIC(Properties);

  m.def("Plus",
        [](const PyClass& w1, const PyClass& w2) { return Plus(w1, w2); });

  m.def("Times",
        [](const PyClass& w1, const PyClass& w2) { return Times(w1, w2); });

  m.def("Divide",
        [](const PyClass& w1, const PyClass& w2) { return Divide(w1, w2); });
}

template <typename T>
static void PybindLogWeightTpl(py::module& m, const char* name) {
  using PyClass = LogWeightTpl<T>;
  using ValueType = typename PyClass::ValueType;
  py::class_<PyClass, FloatWeightTpl<T>> pyclass(m, name);
  DEF_INIT();
  pyclass.def(py::init<ValueType>());
  DEF_STATIC(Zero);
  DEF_STATIC(One);
  DEF_STATIC(NoWeight);
  DEF_STATIC(Type);
  DEF(Member);
  DEF(Quantize, py::arg("delta") = kDelta);
  DEF(Reverse);
  DEF_STATIC(Properties);

  m.def("Plus",
        [](const PyClass& w1, const PyClass& w2) { return Plus(w1, w2); });

  m.def("Times",
        [](const PyClass& w1, const PyClass& w2) { return Times(w1, w2); });

  m.def("Divide",
        [](const PyClass& w1, const PyClass& w2) { return Divide(w1, w2); });
}

template <typename T>
static void PybindRealWeightTpl(py::module& m, const char* name) {
  using PyClass = RealWeightTpl<T>;
  using ValueType = typename PyClass::ValueType;
  py::class_<PyClass, FloatWeightTpl<T>> pyclass(m, name);
  DEF_INIT();
  pyclass.def(py::init<ValueType>());
  DEF_STATIC(Zero);
  DEF_STATIC(One);
  DEF_STATIC(NoWeight);
  DEF_STATIC(Type);
  DEF(Member);
  DEF(Quantize, py::arg("delta") = kDelta);
  DEF(Reverse);
  DEF_STATIC(Properties);

  m.def("Plus",
        [](const PyClass& w1, const PyClass& w2) { return Plus(w1, w2); });

  m.def("Minus",
        [](const PyClass& w1, const PyClass& w2) { return Minus(w1, w2); });

  m.def("Times",
        [](const PyClass& w1, const PyClass& w2) { return Times(w1, w2); });

  m.def("Divide",
        [](const PyClass& w1, const PyClass& w2) { return Divide(w1, w2); });
}

void PybindFloatWeight(py::module& m) {
  PybindFloatWeightTpl<float>(m, "FloatWeight");
  PybindTropicalWeightTpl<float>(m, "TropicalWeight");
  PybindLogWeightTpl<float>(m, "LogWeight");
  PybindRealWeightTpl<float>(m, "RealWeight");
}
