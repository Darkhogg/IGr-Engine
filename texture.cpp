#include "texture.hpp"

namespace igr {

  void texture::bind (GLenum target) const {
    glBindTexture(target, _globj->handle);
  }

}