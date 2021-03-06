// openfst-pybind/vector-fst.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#include "openfst-pybind/vector-fst.h"

#include "fst/vector-fst.h"
#include "openfst-pybind/fst-util.h"
#include "openfst-pybind/fst.h"

using namespace fst;

// TODO(fangjun): use inheritance
template <typename A>
static void PybindVectorFstTpl(py::module& m, const char* name) {
  using PyClass = VectorFst<A>;
  using Arc = typename PyClass::Arc;
  using StateId = typename PyClass::StateId;
  using Weight = typename Arc::Weight;

  DEF_CLASS(name);

  DEF_INIT();
  pyclass.def(py::init<const Fst<Arc>&>(), py::arg("fst"));
  pyclass.def(py::init<const PyClass&, bool>(), py::arg("fst"),
              py::arg("unused_safe") = false);
  DEF(Copy, py::arg("safe") = false, py::return_value_policy::take_ownership);

  DEF(NumStates);

  DEF(SetStart, py::arg("s"));
  DEF(SetFinal, py::arg("s"), py::arg("weight") = Weight::One());

  DEF(SetProperties, py::arg("props"), py::arg("mask"));
  DEF(AddState);
  DEF(AddStates);
  pyclass.def("AddArc",
              (void (PyClass::*)(StateId, const Arc&))(&PyClass::AddArc),
              py::arg("s"), py::arg("arc"));

  pyclass.def(
      "DeleteStates",
      (void (PyClass::*)(const std::vector<StateId>&))(&PyClass::DeleteStates),
      py::arg("dstates"));

  pyclass.def("DeleteStates", (void (PyClass::*)())(&PyClass::DeleteStates));

  pyclass.def("DeleteArcs",
              (void (PyClass::*)(StateId, size_t))(&PyClass::DeleteArcs),
              py::arg("s"), py::arg("n"));

  pyclass.def("DeleteArcs", (void (PyClass::*)(StateId))(&PyClass::DeleteArcs),
              py::arg("s"));

  DEF(ReserveStates, py::arg("n"));
  DEF(ReserveArcs, py::arg("s"), py::arg("n"));

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

  DEF_REF(MutableInputSymbols);
  DEF_REF(MutableOutputSymbols);

  DEF(SetInputSymbols);
  DEF(SetOutputSymbols);

  pyclass.def_static(
      "Read", overload_cast_<const std::string&>()(&PyClass::Read),
      py::arg("source"), py::return_value_policy::take_ownership);

  pyclass.def("Write",
              (bool (PyClass::*)(const std::string&) const)(&PyClass::Write),
              py::arg("source"));

  pyclass
      .def("Info",
           [](const PyClass& self) -> std::string {
             std::ostringstream os;
             auto _fst = fst::script::FstClass(self);
             auto fst_info = fst::FstInfo(*_fst.GetFst<Arc>(), true);
             PrintFstInfoImpl(fst_info, os);
             return os.str();
           })
      .def("__str__",
           [](const PyClass& self) -> std::string {
             std::ostringstream os;
             auto _fst = fst::script::FstClass(self);
             fst::FstPrinter<Arc>(*_fst.GetFst<Arc>(), _fst.InputSymbols(),
                                  _fst.OutputSymbols(),
                                  nullptr,  // state symbol table, ssyms
                                  false,  // false means not in acceptor format
                                  false,  // false means not to show weight one
                                  "      ",  // fst field separator, 6 spaces
                                  ""         // missing symbol
                                  )
                 .Print(os, "standard output");
             return os.str();
           })
      .def(
          "ToString",
          [](const PyClass& self, bool is_acceptor = false,
             bool show_weight_one = false,
             const std::string& fst_field_separator = "      ",
             const std::string& missing_symbol = "",
             const std::string& dest = "stardard output") {
            std::ostringstream os;
            auto _fst = fst::script::FstClass(self);
            fst::FstPrinter<Arc>(*_fst.GetFst<Arc>(), _fst.InputSymbols(),
                                 _fst.OutputSymbols(), nullptr, is_acceptor,
                                 show_weight_one, fst_field_separator,
                                 missing_symbol)
                .Print(os, dest);
            return os.str();
          },
          "see fstprint for help, e.g., fstprint --help",
          py::arg("is_acceptor") = false, py::arg("show_weight_one") = false,
          py::arg("fst_field_separator") = "      ",
          py::arg("missing_symbol") = "", py::arg("dest") = "stardard output");
}

void PybindVectorFst(py::module& m) {
  PybindVectorFstTpl<StdArc>(m, "StdVectorFst");
  PybindStateIterator<StdVectorFst>(m, "StdVectorFstStateIterator");
  PybindArcIterator<StdVectorFst>(m, "StdVectorFstArcIterator");
}
