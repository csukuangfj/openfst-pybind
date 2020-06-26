// openfst-pybind/fst-util.h

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../LICENSE for clarification regarding multiple authors

#ifndef OPENFST_PYBIND_FST_UTIL_H_
#define OPENFST_PYBIND_FST_UTIL_H_

#include "fst/script/fst-class.h"
#include "fst/script/info-impl.h"
#include "fst/script/print-impl.h"
#include "fst/vector-fst.h"

void PrintFstInfoImpl(const fst::FstInfo& fstinfo, std::ostream& ostrm);

#endif  // OPENFST_PYBIND_FST_UTIL_H_
