#ifndef __GL_LIGHT__HPP__
#define __GL_LIGHT__HPP__

#include "common.h"
#include "color.hpp"
#include "vec.hpp"

#include <array>

namespace igr {

  class gl_light {
    private:
      static std::array<bool, 8> lights_used;

      GLenum id;

    public:
      color ambient, diffuse, specular;
      vec<double> position, direction;
      double cutoff, exponent;

      gl_light ();
      ~gl_light ();

      GLenum gl_id () { return id; }

      /* Move-Only */
      gl_light (const gl_light&) = delete;
      gl_light& operator= (const gl_light&) = delete;

      void gl_update ();

      void gl_enable ();
      void gl_disable ();
  };

  void set_ambient_light_color (color c);

}

#endif