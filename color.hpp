/**
 * @author Daniel Escoz Solana
 */
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
  };

  struct colors {
    static const color white, red, green, blue, yellow, aqua, magenta, black;
  };
}

#endif