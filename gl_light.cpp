#include "gl_light.hpp"

std::array<bool, 8> igr::gl_light::lights_used {false, false, false, false, false, false, false, false};

igr::gl_light::gl_light () : id{-1}, cutoff{180}{
  for (std::size_t i = 0; i < 8; ++i) {
    if (!lights_used[i]) {
      lights_used[i] = true;
      id = GL_LIGHT0 + i;
      glEnable(id);
      return;
    }
  }

  /* TODO exception */
}

igr::gl_light::~gl_light () {
  if (id >= 0) {
    glDisable(id);
    lights_used[id - GL_LIGHT0] = false;
    id = -1;
  }
}

void igr::gl_light::gl_update () {

  GLfloat d[] = {diffuse.red, diffuse.green, diffuse.blue, diffuse.alpha};
  glLightfv(id, GL_DIFFUSE, d);

  GLfloat a[] = {ambient.red, ambient.green, ambient.blue, ambient.alpha};
  glLightfv(id, GL_AMBIENT, a);

  GLfloat s[] = {specular.red, specular.green, specular.blue, specular.alpha};
  glLightfv(id, GL_SPECULAR, s);

  GLfloat p[] = {position.x, position.y, position.z, position.w};
  glLightfv(id, GL_POSITION, p);

  GLfloat dr[] = {direction.x, direction.y, direction.z, direction.w};
  glLightfv(id, GL_SPOT_DIRECTION, dr);

  glLightf(id, GL_SPOT_EXPONENT, exponent);
  glLightf(id, GL_SPOT_CUTOFF, cutoff);
}

void igr::gl_light::gl_enable () {
  glEnable(id);
}

void igr::gl_light::gl_disable () {
  glDisable(id);
}

void igr::set_ambient_light_color (color c) {
  GLfloat amb[] = {c.red, c.green, c.blue, c.alpha};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}
