// openfst-pybind/fst.h

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#ifndef OPENFST_PYBIND_FST_H_
#define OPENFST_PYBIND_FST_H_

#include "fst/fst.h"
#include "openfst-pybind/openfst-pybind.h"

void PybindFst(py::module& m);

template <typename A>
void PybindFstTpl(py::module& m, const char* name) {
  using namespace fst;

  using PyClass = Fst<A>;
  using Arc = typename PyClass::Arc;
  using StateId = typename PyClass::StateId;
  using Weight = typename PyClass::Weight;

  DEF_CLASS(name);

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

  DEF_REF(InputSymbols);
  DEF_REF(OutputSymbols);
}

template <typename FST>
void PybindStateIterator(py::module& m, const char* name) {
  using namespace fst;
  using PyClass = StateIterator<FST>;
  DEF_CLASS(name);

  pyclass.def(py::init<const FST&>(), py::arg("fst"));

  DEF(Done);
  DEF(Value);
  DEF(Next);
  DEF(Reset);
}

template <typename FST>
void PybindArcIterator(py::module& m, const char* name) {
  using namespace fst;
  using PyClass = ArcIterator<FST>;
  using StateId = typename PyClass::StateId;
  DEF_CLASS(name);
  pyclass.def(py::init<const FST&, StateId>(), py::arg("fst"), py::arg("s"));

  DEF(Done);
  DEF_REF(Value);
  DEF(Next);
  DEF(Reset);
  DEF(Seek, py::arg("a"));
  DEF(Position);
  DEF(Flags);
  DEF(SetFlags, py::arg("flags"), py::arg("mask"));
}

#endif  // OPENFST_PYBIND_FST_H_
