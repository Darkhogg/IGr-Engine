/**
 * @author Daniel Escoz Solana
 */
#include "camera.hpp"

void igr::camera::gl_update () {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
}