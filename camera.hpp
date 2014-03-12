#ifndef __CAMERA__HPP__
#define __CAMERA__HPP__

#include "common.h"

#include "vec.hpp"

namespace igr {

  struct camera {
    vec<double> eye;
    vec<double> look;
    vec<double> up;

    camera ()
    {}

    camera (vec<double> eye, vec<double> look, vec<double> up)
      : eye(eye), look(look), up(up)
    {}

    void gl_update ();
  };

}

#endif
