#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2015 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import matlab_swig as matlab

import numpy

class qa_fftmat (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
	#src_data = gr.gr_complex(numpy.random.randn(64),numpy.random.randn(64));
	fft_size = 64
	src_data = numpy.random.randn(512)+numpy.random.randn(512)*1j;
	#print src_data[0:63]
	#src_data = (-3, 4, -5.5, 2, 3)
        expected_result = numpy.random.randn(512) + numpy.random.randn(512)*1j;
        src = blocks.vector_source_c(src_data)
	s2v = blocks.stream_to_vector(gr.sizeof_gr_complex, fft_size)
        op = matlab.fftmat()
 	v2s = blocks.vector_to_stream(gr.sizeof_gr_complex, fft_size)
        dst = blocks.vector_sink_c()
	print "STARTING11"
        self.tb.connect(src, s2v, op, v2s, dst)
        #self.tb.run()
        result_data = dst.data()
	print "Done"
        #self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

	# set up fg
        self.tb.run ()
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_fftmat, "qa_fftmat.xml")
