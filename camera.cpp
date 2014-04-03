#include "camera.hpp"

void igr::camera::gl_update () {
  up = up.cross(look - eye).cross(eye - look).normalized();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
}

void igr::camera::transform (matr<double> matrix) {
  eye = eye * matrix;
  look = look * matrix;
  up = up * matrix;
}

igr::camera igr::camera::transformed (matr<double> matrix) const {
  camera cam {*this};
  cam.transform(matrix);
  return cam;
}
