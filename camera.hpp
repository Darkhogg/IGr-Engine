#ifndef __CAMERA__HPP__
#define __CAMERA__HPP__

#include "common.h"

#include "vec.hpp"

namespace igr {

  struct camera {
    vec<float> eye;
    vec<float> look;
    vec<float> up;

    camera ()
    {}

    camera (vec<float> eye, vec<float> look, vec<float> up)
      : eye(eye), look(look), up(up)
    {}

    void gl_update ();
  };

}

#endif
