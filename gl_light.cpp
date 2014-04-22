#include "gl_light.hpp"

std::array<bool, 8> igr::gl_light::lights_used {false, false, false, false, false, false, false, false};

igr::gl_light::gl_light () : id{-1} {
  for (std::size_t i = 0; i < 8; ++i) {
    if (!lights_used[i]) {
      lights_used[i] = true;
      id = GL_LIGHT0 + i;
      return;
    }
  }

  /* TODO exception */
}

igr::gl_light::~gl_light () {
  if (id >= 0) {
    lights_used[id - GL_LIGHT0] = false;
    id = -1;
  }
}