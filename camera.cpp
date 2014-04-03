/**
 * @author Daniel Escoz Solana
 */
#include "camera.hpp"
 #include <iostream>

void igr::camera::normalize () {
  std::cout << up << "{" << up.length() << "}";
  eye.w  = 1.0;
  look.w = 1.0;
  up.w   = 0.0;

  up = up.cross(look - eye).cross(eye - look).normalized();
  std::cout << " -> " << up << "{" << up.length() << "}" << std::endl;
}

void igr::camera::gl_update () {
  normalize();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
}

void igr::camera::transform (matr<double> matrix) {
  normalize();

  eye = eye * matrix;
  look = look * matrix;
  up = up * matrix;
}


void igr::camera::yaw (double ang) {
  normalize();
  auto rot = matr<double>::make_rotation({0.0, 1.0, 0.0}, ang);

  auto dir = look - eye;
  dir = rot * dir;
  look = eye + dir;

  up = rot * up;
}

void igr::camera::pitch (double ang) {
  normalize();
  auto rot = matr<double>::make_rotation((look - eye).cross({0.0, 1.0, 0.0}), ang);

  auto dir = look - eye;
  dir = rot * dir;
  look = eye + dir;

  up = rot * up;
}

void igr::camera::roll (double ang) {
  normalize();
  up = matr<double>::make_rotation(look - eye, ang) * up;
}


igr::camera igr::camera::transformed (matr<double> matrix) const {
  camera cam {*this};
  cam.transform(matrix);
  return cam;
}
