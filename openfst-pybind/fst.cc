// openfst-pybind/fst.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#include "openfst-pybind/fst.h"

#include "fst/fst.h"

using namespace fst;

static void PybindFstHeader(py::module& m) {
  using PyClass = FstHeader;
  DEF_CLASS("FstHeader");

  py::enum_<FstHeader::Flags>(pyclass, "Flags", py::arithmetic())
      .value("HAS_ISYMBOLS", FstHeader::Flags::HAS_ISYMBOLS)
      .value("HAS_OSYMBOLS", FstHeader::Flags::HAS_OSYMBOLS)
      .value("IS_ALIGNED", FstHeader::Flags::IS_ALIGNED)
      .export_values();

  DEF_INIT();
  DEF_REF(FstType);
  DEF_REF(ArcType);
  DEF(Version);
  DEF(GetFlags);
  DEF(Properties);
  DEF(Start);
  DEF(NumStates);
  DEF(NumArcs);
  DEF(SetFstType, py::arg("type"));
  DEF(SetArcType, py::arg("type"));
  DEF(SetVersion, py::arg("version"));
  DEF(SetFlags, py::arg("flags"));
  DEF(SetProperties, py::arg("properties"));
  DEF(SetStart, py::arg("start"));
  DEF(SetNumStates, py::arg("numstates"));
  DEF(SetNumArcs, py::arg("numarcs"));
  DEF(DebugString);
}

static void PybindFstReadOptions(py::module& m) {
  using PyClass = FstReadOptions;
  DEF_CLASS("FstReadOptions");

  py::enum_<FstReadOptions::FileReadMode>(pyclass, "FileReadMode",
                                          py::arithmetic())
      .value("READ", FstReadOptions::FileReadMode::READ)
      .value("MAP", FstReadOptions::FileReadMode::MAP)
      .export_values();
  DEF_P(source);
  DEF_P(header);
  DEF_P(isymbols);
  DEF_P(osymbols);
  DEF_P(mode);
  DEF_P(read_isymbols);
  DEF_P(read_osymbols);
  pyclass.def(py::init<const std::string&, const FstHeader*, const SymbolTable*,
                       const SymbolTable*>(),
              py::arg("source") = "<unspecified>", py::arg("header") = nullptr,
              py::arg("isymbols") = nullptr, py::arg("osymbols") = nullptr);
  pyclass.def(
      py::init<const std::string&, const SymbolTable*, const SymbolTable*>(),
      py::arg("source"), py::arg("isymbols"), py::arg("osymbols") = nullptr);
  DEF_STATIC(ReadMode, py::arg("mode"));
  DEF(DebugString);
}

static void PybindFstWriteOptions(py::module& m) {
  using PyClass = FstWriteOptions;
  DEF_CLASS("FstWriteOptions");

  DEF_P(source);
  DEF_P(write_header);
  DEF_P(write_isymbols);
  DEF_P(write_osymbols);
  DEF_P(align);
  DEF_P(stream_write);

  pyclass.def(
      py::init<const std::string&, bool, bool, bool, bool, bool>(),
      py::arg("source") = "<unspecified>", py::arg("write_header") = true,
      py::arg("write_isymbols") = true, py::arg("write_osymbols") = true,
      py::arg("align") = FLAGS_fst_align, py::arg("stream_write") = false);
}

void PybindFst(py::module& m) {
  m.attr("kNoLabel") = kNoLabel;
  m.attr("kNoStateId") = kNoStateId;
  PybindFstHeader(m);
  PybindFstReadOptions(m);
  PybindFstWriteOptions(m);

  // PybindFstTpl<StdArc>(m, "StdFst");
}
