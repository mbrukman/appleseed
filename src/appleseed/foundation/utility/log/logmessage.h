
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

#ifndef APPLESEED_FOUNDATION_UTILITY_LOG_LOGMESSAGE_H
#define APPLESEED_FOUNDATION_UTILITY_LOG_LOGMESSAGE_H

// appleseed.main headers.
#include "main/dllsymbol.h"

namespace foundation
{

//
// Log message.
//

class APPLESEED_DLLSYMBOL LogMessage
{
  public:
    // Message categories.
    enum Category
    {
        Info,                       // general information, statistics, progress messages, etc.
        Debug,                      // debug message
        Warning,                    // warning message; execution can continue
        Error,                      // severe error message; the program will attempt to continue
        Fatal,                      // fatal error message; the program will terminate afterward
        NumMessageCategories        // number of message categories (keep at the end)
    };

    //
    // Return the category matching a given name:
    //
    //   Name       Value
    //   ------------------
    //   "info"     Info
    //   "debug"    Debug
    //   "warning"  Warning
    //   "error"    Error
    //   "fatal"    Fatal
    //   Otherwise  NumMessageCategories
    //

    static Category get_category_value(const char* name);

    // Return a string identifying a given message category.
    static const char* get_category_name(const Category c);

    // Return a category name padded with spaces to the right.
    static const char* get_padded_category_name(const Category c);
};

}       // namespace foundation

#endif  // !APPLESEED_FOUNDATION_UTILITY_LOG_LOGMESSAGE_H
