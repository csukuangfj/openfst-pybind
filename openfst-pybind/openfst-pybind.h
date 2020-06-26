// openfst-pybind/openfst-pybind.h

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#ifndef OPENFST_PYBIND_OPENFST_PYBIND_H_
#define OPENFST_PYBIND_OPENFST_PYBIND_H_

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;

#define DEF_CLASS(name) py::class_<PyClass> pyclass(m, name);

#define DEF_INIT() pyclass.def(py::init<>())

#define DEF(name) pyclass.def(#name, &PyClass::name)

#define DEF_REF(name) \
  pyclass.def(#name, &PyClass::name, py::return_value_policy::reference)

#endif  // OPENFST_PYBIND_OPENFST_PYBIND_H_
