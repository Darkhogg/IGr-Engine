/**
 * @author Daniel Escoz Solana
 */
#ifndef __CAMERA__HPP__
#define __CAMERA__HPP__

#include "common.h"

#include "vec.hpp"
#include "matr.hpp"

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

      void transform (matr<double> matrix);
      camera transformed (matr<double> matrix) const;

    void gl_update ();
  };

}

#endif
