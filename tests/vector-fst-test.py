#!/usr/bin/env python3
#
# Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)
#
# See ../LICENSE for clarification regarding multiple authors

# To run this single test, use
#
#  ctest --verbose -R vector-fst-test
#

import unittest

import fst


class TestVectorFst(unittest.TestCase):
    def test(self):
        vector_fst = fst.StdVectorFst()

        s0 = vector_fst.AddState()
        s1 = vector_fst.AddState()
        vector_fst.SetStart(s0)
        vector_fst.SetFinal(s1, fst.TropicalWeight(0.25))

        w = fst.TropicalWeight(0.5)
        print(type(w))
        arc = fst.StdArc(ilabel=1, olabel=1, weight=w, nextstate=1)
        vector_fst.AddArc(s0, arc)
        vector_fst.Write('a.fst')

        # fstprint tests/a.fst


if __name__ == '__main__':
    unittest.main()
