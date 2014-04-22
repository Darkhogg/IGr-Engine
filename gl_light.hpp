#include "common.h"

#include <array>

namespace igr {

  class gl_light {
    private:
      static std::array<bool, 8> lights_used;

      GLenum id;

    public:
      gl_light ();
      ~gl_light ();

      GLenum gl_id () { return id; }

      /* Move-Only */
      gl_light (const gl_light&) = delete;
      gl_light& operator= (const gl_light&) = delete;
  };

}