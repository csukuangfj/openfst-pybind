// openfst-pybind/openfst-pybind.h

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#ifndef OPENFST_PYBIND_OPENFST_PYBIND_H_
#define OPENFST_PYBIND_OPENFST_PYBIND_H_

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;

template <typename... Args>
using overload_cast_ = py::detail::overload_cast_impl<Args...>;

#define DEF_CLASS(name) py::class_<PyClass> pyclass(m, name);

#define DEF_INIT() pyclass.def(py::init<>())

#define DEF(name, ...) pyclass.def(#name, &PyClass::name, ##__VA_ARGS__)

#define DEF_STATIC(name, ...) \
  pyclass.def_static(#name, &PyClass::name, ##__VA_ARGS__)

#define DEF_REF(name) \
  pyclass.def(#name, &PyClass::name, py::return_value_policy::reference)

#define DEF_P(name, ...) \
  pyclass.def_readwrite(#name, &PyClass::name, ##__VA_ARGS__)

#endif  // OPENFST_PYBIND_OPENFST_PYBIND_H_
