// openfst-pybind/symbol-table.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#include "openfst-pybind/symbol-table.h"

#include "fst/symbol-table.h"

using namespace fst;

static void PybindSymbolTableTextOptions(py::module& m) {
  using PyClass = SymbolTableTextOptions;
  DEF_CLASS("SymbolTableTextOptions");
  pyclass.def(py::init<bool>(), py::arg("allow_negative_labels") = false);
  DEF_P(allow_negative_labels);
  DEF_P(fst_field_separator);
}
static void PybindSymbolTableImpl(py::module& m) {
  using PyClass = SymbolTable;
  using SymbolType = typename PyClass::SymbolType;
  DEF_CLASS("SymbolTable");
  pyclass.def(py::init<const std::string&>(),
              py::arg("name") = "<unspecified>");

  pyclass.def_static(
      "ReadText",
      overload_cast_<const std::string&, const SymbolTableTextOptions&>()(
          &PyClass::ReadText),
      py::arg("source"), py::arg("opts") = SymbolTableTextOptions(),
      py::return_value_policy::take_ownership);

  pyclass.def_static("Read",
                     overload_cast_<const std::string&>()(&PyClass::Read),
                     py::arg("source"));
  pyclass.def("Write",
              (bool (PyClass::*)(const std::string&) const)(&PyClass::Write),
              py::arg("source"));

  pyclass.def(
      "WriteText",
      (bool (PyClass::*)(const std::string&) const)(&PyClass::WriteText),
      py::arg("source"));

  DEF(Copy, py::return_value_policy::take_ownership);
  DEF(AddTable);
  pyclass.def("AddSymbol",
              overload_cast_<SymbolType, int64>()(&PyClass::AddSymbol),
              py::arg("symbol"), py::arg("key"));

  pyclass.def("AddSymbol", overload_cast_<SymbolType>()(&PyClass::AddSymbol),
              py::arg("symbol"));

  DEF(AvailableKey);
  DEF(GetNthKey);

  pyclass.def("Find", (std::string(PyClass::*)(int64) const)(&PyClass::Find),
              py::arg("key"));

  pyclass.def("Find", (int64(PyClass::*)(SymbolType) const)(&PyClass::Find),
              py::arg("symbol"));

  DEF_REF(LabeledCheckSum);

  pyclass.def("Member", (bool (PyClass::*)(int64) const)(&PyClass::Member),
              py::arg("key"));
  pyclass.def("Member", (bool (PyClass::*)(SymbolType) const)(&PyClass::Member),
              py::arg("symbol"));
  DEF(Name);
  DEF(NumSymbols);
  DEF(RemoveSymbol, py::arg("key"));
  DEF(SetName, py::arg("new_name"));
  pyclass.def("ToText", [](const PyClass& self) {
    std::ostringstream os;
    self.WriteText(os);
    return os.str();
  });

  pyclass.def(
      "__iter__",
      [](const PyClass& self) {
        return py::make_iterator(self.begin(), self.end());
      },
      py::keep_alive<0, 1>());
}

void PybindSymbolTable(py::module& m) {
  m.attr("kNoSymbol") = kNoSymbol;
  PybindSymbolTableTextOptions(m);
  PybindSymbolTableImpl(m);

  m.def(
      "SymbolTableToString",
      [](const SymbolTable& table) {
        std::string result;
        SymbolTableToString(&table, &result);
        return result;
      },
      py::arg("table"));

  m.def("StringToSymbolTable", &StringToSymbolTable, py::arg("str"),
        py::return_value_policy::take_ownership);
}
