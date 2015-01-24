/* -*- c++ -*- */
/* 
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "fftmat_impl.h"
#include <iostream>

//MATLAB Datatypes
//#include <tmwtypes.h>
#include "rtwtypes.h"
#include <fft_from_matlab.h>

namespace gr {
  namespace matlab {

    fftmat::sptr
    fftmat::make()
    {
      return gnuradio::get_initial_sptr
        (new fftmat_impl());
    }

    /*
     * The private constructor
     */
    fftmat_impl::fftmat_impl()
      : gr::block("fftmat",
              gr::io_signature::make( 1, 1, 64*sizeof(gr_complex)),
              gr::io_signature::make( 1, 1, 64*sizeof(gr_complex)))
    {}

    /*
     * Our virtual destructor.
     */
    fftmat_impl::~fftmat_impl()
    {
    }

    void
    fftmat_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
    }

    int
    fftmat_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

	int noutput = noutput_items;

	std::cout<<"Inside GR Block\n";

	// Convert to MATLAB compatable type
	//creal_T input_mat[noutput];
	creal_T input_mat[64];
	for (int i=0; i<noutput; i++)
	{
		input_mat[i].re = in[i].real();
		input_mat[i].im = in[i].imag();
	}
	// Pass to MATLAB generated C++ function
	//creal_T output_mat[noutput];
	creal_T output_mat[64];
	fft_from_matlab(input_mat, output_mat);

	std::cout<<"Out of MATLAB C++ function\n";

	// Convert back to GR type
	for (int j=0; j<noutput; j++)
	{
		out[j] = gr_complex(output_mat[j].re,output_mat[j].im);
	}
        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace matlab */
} /* namespace gr */

