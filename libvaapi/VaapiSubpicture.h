// VaapiSubpicture.h: VA subpicture abstraction
// 
// Copyright (C) 2009, 2010 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef GNASH_VAAPISUBPICTURE_H
#define GNASH_VAAPISUBPICTURE_H

#include <vector>

#include "vaapi_common.h"
#include "VaapiImageFormat.h"
#include "dsodefs.h"

namespace gnash {

// Forward declarations
class VaapiImage;

/// VA subpicture abstraction
class DSOEXPORT VaapiSubpicture
{
    boost::shared_ptr<VaapiImage>       _image;
    VASubpictureID                      _subpicture;

    /// Create VA subpicture
    bool create();

    /// Destroy VA subpicture
    void destroy();

public:
    VaapiSubpicture(boost::shared_ptr<VaapiImage> image);
    ~VaapiSubpicture();

    /// Return VA subpicture id
    VASubpictureID get() const { return _subpicture; }
};

 } // gnash namespace

#endif // GNASH_VAAPISUBPICTURE_H

// local Variables:
// mode: C++
// indent-tabs-mode: nil
// End:

