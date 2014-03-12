#ifndef __COLOR__HPP__
#define __COLOR__HPP__

#include "common.h"

namespace igr {

  struct color {
    float red, green, blue, alpha;

    color ();
    color (float r, float g, float b);
    color (float r, float g, float b, float a);

    void gl_set () const;

    static const color white;
  };

}

#endif