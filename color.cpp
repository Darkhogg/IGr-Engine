/**
 * @author Daniel Escoz Solana
 */
#include "color.hpp"

const igr::color igr::colors::black   = {0.f, 0.f, 0.f};
const igr::color igr::colors::red     = {1.f, 0.f, 0.f};
const igr::color igr::colors::green   = {0.f, 1.f, 0.f};
const igr::color igr::colors::blue    = {0.f, 0.f, 1.f};
const igr::color igr::colors::yellow  = {1.f, 1.f, 0.f};
const igr::color igr::colors::aqua    = {0.f, 1.f, 1.f};
const igr::color igr::colors::magenta = {1.f, 0.f, 1.f};
const igr::color igr::colors::white   = {1.f, 1.f, 1.f};


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