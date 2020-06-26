// openfst-pybind/fst-util.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#include "openfst-pybind/fst-util.h"

using namespace fst;

// this following function is copied from openfst/src/script/info-impl.cc
void PrintFstInfoImpl(const FstInfo& fstinfo, std::ostream& ostrm) {
  using namespace fst;
  ostrm.setf(std::ios::left);
  ostrm.width(50);
  ostrm << "fst type" << fstinfo.FstType() << std::endl;
  ostrm.width(50);
  ostrm << "arc type" << fstinfo.ArcType() << std::endl;
  ostrm.width(50);
  ostrm << "input symbol table" << fstinfo.InputSymbols() << std::endl;
  ostrm.width(50);
  ostrm << "output symbol table" << fstinfo.OutputSymbols() << std::endl;
  if (!fstinfo.LongInfo()) {
    return;
  }
  ostrm.width(50);
  ostrm << "# of states" << fstinfo.NumStates() << std::endl;
  ostrm.width(50);
  ostrm << "# of arcs" << fstinfo.NumArcs() << std::endl;
  ostrm.width(50);
  ostrm << "initial state" << fstinfo.Start() << std::endl;
  ostrm.width(50);
  ostrm << "# of final states" << fstinfo.NumFinal() << std::endl;
  ostrm.width(50);
  ostrm << "# of input/output epsilons" << fstinfo.NumEpsilons() << std::endl;
  ostrm.width(50);
  ostrm << "# of input epsilons" << fstinfo.NumInputEpsilons() << std::endl;
  ostrm.width(50);
  ostrm << "# of output epsilons" << fstinfo.NumOutputEpsilons() << std::endl;
  ostrm.width(50);
  ostrm << "input label multiplicity" << fstinfo.InputLabelMultiplicity()
        << std::endl;
  ostrm.width(50);
  ostrm << "output label multiplicity" << fstinfo.OutputLabelMultiplicity()
        << std::endl;
  ostrm.width(50);
  std::string arc_type = "";
  if (fstinfo.ArcFilterType() == "epsilon")
    arc_type = "epsilon ";
  else if (fstinfo.ArcFilterType() == "iepsilon")
    arc_type = "input-epsilon ";
  else if (fstinfo.ArcFilterType() == "oepsilon")
    arc_type = "output-epsilon ";
  const auto accessible_label = "# of " + arc_type + "accessible states";
  ostrm.width(50);
  ostrm << accessible_label << fstinfo.NumAccessible() << std::endl;
  const auto coaccessible_label = "# of " + arc_type + "coaccessible states";
  ostrm.width(50);
  ostrm << coaccessible_label << fstinfo.NumCoAccessible() << std::endl;
  const auto connected_label = "# of " + arc_type + "connected states";
  ostrm.width(50);
  ostrm << connected_label << fstinfo.NumConnected() << std::endl;
  const auto numcc_label = "# of " + arc_type + "connected components";
  ostrm.width(50);
  ostrm << numcc_label << fstinfo.NumCc() << std::endl;
  const auto numscc_label = "# of " + arc_type + "strongly conn components";
  ostrm.width(50);
  ostrm << numscc_label << fstinfo.NumScc() << std::endl;
  ostrm.width(50);
  ostrm << "input matcher"
        << (fstinfo.InputMatchType() == MATCH_INPUT  ? 'y'
            : fstinfo.InputMatchType() == MATCH_NONE ? 'n'
                                                     : '?')
        << std::endl;
  ostrm.width(50);
  ostrm << "output matcher"
        << (fstinfo.OutputMatchType() == MATCH_OUTPUT ? 'y'
            : fstinfo.OutputMatchType() == MATCH_NONE ? 'n'
                                                      : '?')
        << std::endl;
  ostrm.width(50);
  ostrm << "input lookahead" << (fstinfo.InputLookAhead() ? 'y' : 'n')
        << std::endl;
  ostrm.width(50);
  ostrm << "output lookahead" << (fstinfo.OutputLookAhead() ? 'y' : 'n')
        << std::endl;
  uint64 prop = 1;
  for (auto i = 0; i < 64; ++i, prop <<= 1) {
    if (prop & kBinaryProperties) {
      char value = 'n';
      if (fstinfo.Properties() & prop) value = 'y';
      ostrm.width(50);
      ostrm << PropertyNames[i] << value << std::endl;
    } else if (prop & kPosTrinaryProperties) {
      char value = '?';
      if (fstinfo.Properties() & prop)
        value = 'y';
      else if (fstinfo.Properties() & prop << 1)
        value = 'n';
      ostrm.width(50);
      ostrm << PropertyNames[i] << value << std::endl;
    }
  }
}
