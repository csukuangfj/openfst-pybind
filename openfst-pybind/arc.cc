// openfst-pybind/arc.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#include "openfst-pybind/arc.h"

#include "fst/arc.h"

using namespace fst;

template <typename W>
static void PybindArcTpl(py::module& m, const char* name) {
  using PyClass = ArcTpl<W>;
  using Weight = typename PyClass::Weight;
  using Label = typename PyClass::Label;
  using StateId = typename PyClass::StateId;

  DEF_CLASS(name);
  DEF_P(ilabel);
  DEF_P(olabel);
  DEF_P(weight);
  DEF_P(nextstate);

  DEF_INIT();
  pyclass.def(py::init<Label, Label, Weight, StateId>(), py::arg("ilabel"),
              py::arg("olabel"), py::arg("weight"), py::arg("nextstate"));
  pyclass.def(py::init<Label, Label, StateId>(), py::arg("ilabel"),
              py::arg("olabel"), py::arg("nextstate"),
              "The weight is set to Weight::One()");
  DEF_STATIC(Type);
}

void PybindArc(py::module& m) {
  PybindArcTpl<TropicalWeight>(m, "StdArc");
  PybindArcTpl<LogWeight>(m, "LogArc");
  PybindArcTpl<RealWeight>(m, "RealArc");
}
