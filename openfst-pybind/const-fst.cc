// openfst-pybind/const-fst.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#include "openfst-pybind/const-fst.h"

#include "fst/const-fst.h"
#include "openfst-pybind/fst.h"

using namespace fst;

// TODO(fangjun): use inheritance
template <typename A>
static void PybindConstFstTpl(py::module& m, const char* name) {
  using PyClass = ConstFst<A, uint32>;
  using Arc = typename PyClass::Arc;
  using StateId = typename PyClass::StateId;

  DEF_CLASS(name);
  DEF_INIT();
  pyclass.def(py::init<const Fst<Arc>&>(), py::arg("fst"));
  pyclass.def(py::init<const PyClass&, bool>(), py::arg("fst"),
              py::arg("unused_safe") = false);

  DEF(NumStates);

  DEF(Start);
  DEF(Final);
  DEF(NumArcs);
  DEF(NumInputEpsilons);
  DEF(NumOutputEpsilons);
  DEF(Properties, py::arg("mask"), py::arg("test"));
  DEF_REF(Type);
  DEF(Copy, py::arg("safe") = false, py::return_value_policy::take_ownership);
  pyclass.def_static(
      "Read", overload_cast_<const std::string&>()(&PyClass::Read),
      py::arg("source"), py::return_value_policy::take_ownership);

  pyclass.def("Write",
              (bool (PyClass::*)(const std::string&) const)(&PyClass::Write),
              py::arg("source"));
}

void PybindConstFst(py::module& m) {
  PybindConstFstTpl<StdArc>(m, "StdConstFst");
  PybindStateIterator<StdConstFst>(m, "StdConstFstStateIterator");
  PybindArcIterator<StdConstFst>(m, "StdConstFstArcIterator");
}
