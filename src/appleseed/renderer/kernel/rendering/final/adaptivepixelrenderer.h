
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

#ifndef APPLESEED_RENDERER_KERNEL_RENDERING_FINAL_ADAPTIVEPIXELRENDERER_H
#define APPLESEED_RENDERER_KERNEL_RENDERING_FINAL_ADAPTIVEPIXELRENDERER_H

// appleseed.renderer headers.
#include "renderer/kernel/rendering/ipixelrenderer.h"
#include "renderer/utility/paramarray.h"

// appleseed.foundation headers.
#include "foundation/platform/compiler.h"

// Standard headers.
#include <cstddef>

// Forward declarations.
namespace renderer  { class Frame; }
namespace renderer  { class ISampleRendererFactory; }

namespace renderer
{

//
// Adaptive pixel renderer.
//

class AdaptivePixelRendererFactory
  : public IPixelRendererFactory
{
  public:
    // Constructor.
    AdaptivePixelRendererFactory(
        const Frame&                frame,
        ISampleRendererFactory*     factory,
        const ParamArray&           params);

    // Delete this instance.
    virtual void release() APPLESEED_OVERRIDE;

    // Return a new adaptive pixel renderer instance.
    virtual IPixelRenderer* create(
        const size_t                thread_index) APPLESEED_OVERRIDE;

  private:
    const Frame&                    m_frame;
    ISampleRendererFactory*         m_factory;
    ParamArray                      m_params;
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_KERNEL_RENDERING_FINAL_ADAPTIVEPIXELRENDERER_H
