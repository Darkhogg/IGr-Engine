#include "color.hpp"

const igr::color igr::color::white = {1.f, 1.f, 1.f};


igr::color::color ()
  : color{0.f, 0.f, 0.f}
{}


igr::color::color (float r, float g, float b)
  : color{r, g, b, 1.f}
{}


igr::color::color (float r, float g, float b, float a)
  : red{r}, green{g}, blue{b}, alpha{a}
{}


void igr::color::gl_set () const {
  glColor4f(red, green, blue, alpha);
}