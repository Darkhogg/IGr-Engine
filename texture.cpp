/**
 * @author Daniel Escoz Solana
 */
#include "texture.hpp"

namespace igr {

  void texture::gl_bind (GLenum target) const {
    glBindTexture(target, _globj->handle);
  }

}