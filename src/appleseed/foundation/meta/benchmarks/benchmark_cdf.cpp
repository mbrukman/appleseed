
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014-2016 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// appleseed.foundation headers.
#include "foundation/math/rng/distribution.h"
#include "foundation/math/rng/xorshift.h"
#include "foundation/math/cdf.h"
#include "foundation/utility/benchmark.h"

// Standard headers.
#include <cassert>
#include <cstddef>

using namespace foundation;
using namespace std;

BENCHMARK_SUITE(Foundation_Math_CDF)
{
    template <size_t Size>
    struct Fixture
    {
        typedef CDF<size_t, double> CDFType;

        CDFType     m_cdf;
        Xorshift    m_rng;
        double      m_x;

        Fixture()
          : m_x(0.0)
        {
            for (size_t i = 0; i < Size; ++i)
                m_cdf.insert(i, rand_double1(m_rng));

            assert(m_cdf.valid());

            m_cdf.prepare();
        }
    };

    BENCHMARK_CASE_F(DoublePrecisionSampling_10Elements, Fixture<10>)
    {
        for (size_t i = 0; i < 100; ++i)
            m_x += m_cdf.sample(rand_double2(m_rng)).second;
    }

    BENCHMARK_CASE_F(DoublePrecisionSampling_1000Elements, Fixture<1000>)
    {
        for (size_t i = 0; i < 100; ++i)
            m_x += m_cdf.sample(rand_double2(m_rng)).second;
    }

    BENCHMARK_CASE_F(DoublePrecisionSampling_1000000Elements, Fixture<1000000>)
    {
        for (size_t i = 0; i < 100; ++i)
            m_x += m_cdf.sample(rand_double2(m_rng)).second;
    }
}
