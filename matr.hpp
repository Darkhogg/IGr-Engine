/**
 * @author Daniel Escoz Solana
 */
#ifndef __MATR__H__
#define __MATR__H__

#include <array>

#include "common.h"

namespace igr {

  template <typename C=double>
  class matr {
    private:
      std::array<C, 16> data;

    public:
      matr () : data{
        { 1.0, 0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0,
          0.0, 0.0, 0.0, 1.0 }
      }
      {}

      C  operator() (std::size_t i, std::size_t j) const;
      C& operator() (std::size_t i, std::size_t j);

      matr<C> operator+= (const matr<C> other);
      matr<C> operator-= (const matr<C> other);
      matr<C> operator*= (const C scale);
      matr<C> operator/= (const C scale);

      void gl_load (GLenum);
      void gl_store () const;

      static matr<C> make_translation (const vec<C> translation);
      static matr<C> make_scalation (const vec<C> scalation);
      static matr<C> make_rotation (const vec<C> around, double angle);

      static matr<C> make_rotation_x (double angle);
      static matr<C> make_rotation_y (double angle);
      static matr<C> make_rotation_z (double angle);

      template<typename M>
      friend std::ostream& operator<< (std::ostream&, const matr<M>&);
  };


  /* ======================= */
  /* === POSITION ACCESS === */

  template<typename C>
  C matr<C>::operator() (std::size_t i, std::size_t j) const {
    return data[j + 4 * i];
  }


  template<typename C>
  C& matr<C>::operator() (std::size_t i, std::size_t j) {
    return data[j + 4 * i];
  }


  /* ========================= */
  /* === OPENGL LOAD/STORE === */

  template<typename C>
  void matr<C>::gl_load (GLenum matrix) {

  }

  template<typename C>
  void matr<C>::gl_store () const {
    glLoadMatrixf(data.data());
  }


  /* =========================== */
  /* === STATIC CONSTRUCTION === */

  template<typename C>
  matr<C> matr<C>::make_translation (vec<C> translation) {
    matr<C> m;
    //m(0, 0) = m(1, 1) = m(2, 2) = 0.0;
    m(0, 3) = translation.x;
    m(1, 3) = translation.y;
    m(2, 3) = translation.z;
    return m;
  }

  template<typename C>
  matr<C> matr<C>::make_scalation (vec<C> scalation) {
    matr<C> m;
    m(0, 0) = scalation.x;
    m(1, 1) = scalation.y;
    m(2, 2) = scalation.z;
    return m;
  }

  template<typename C>
  matr<C> matr<C>::make_rotation (vec<C> u, double angle) {
    u.normalize();

    auto c  = cos(angle);
    auto s  = sin(angle);
    auto c1 = 1 - c;

    auto ux = u.x;
    auto ux2 = ux * ux;

    auto uy = u.y;
    auto uy2 = uy * uy;

    auto uz = u.z;
    auto uz2 = uz * uz;

    matr<C> m;

    m(0, 0) = c + ux2 * c1;
    m(0, 1) = ux * uy * c1 - uz * s;
    m(0, 2) = ux * uz * c1 + uy * s;
    m(0, 3) = 0.0;

    m(1, 0) = uy * ux * c1 + uz * s;
    m(1, 1) = c + uy2 * c1;
    m(1, 2) = uy * uz * c1 - ux * s;
    m(1, 3) = 0.0;

    m(2, 0) = uz * ux * c1 - uy * s;
    m(2, 1) = uz * uy * c1 + ux * s;
    m(2, 2) = c + uz2 * c1;
    m(2, 3) = 0.0;

    m(3, 0) = 0.0;
    m(3, 1) = 0.0;
    m(3, 2) = 0.0;
    m(3, 3) = 1.0;

    return m;
  }

  template<typename C>
  matr<C> matr<C>::make_rotation_x (double angle) {
    matr<C> m;
    m(1, 1) = cos(angle);
    m(1, 2) = sin(angle);
    m(2, 1) = -sin(angle);
    m(2, 2) = cos(angle);
    return m;
  }

  template<typename C>
  matr<C> matr<C>::make_rotation_y (double angle) {
    matr<C> m;
    m(0, 0) = cos(angle);
    m(0, 2) = sin(angle);
    m(2, 0) = -sin(angle);
    m(2, 2) = cos(angle);
    return m;
  }

  template<typename C>
  matr<C> matr<C>::make_rotation_z (double angle) {
    matr<C> m;
    m(0, 0) = cos(angle);
    m(0, 1) = sin(angle);
    m(1, 0) = -sin(angle);
    m(1, 1) = cos(angle);
    return m;
  }


  /* ================= */
  /* === OPERATORS === */

  template<typename C>
  matr<C> matr<C>::operator+= (matr<C> other) {
    for (std::size_t i = 0; i < 16; i++) {
      data[i] += other.data[i];
    }
  }

  template<typename C>
  matr<C> matr<C>::operator-= (matr<C> other) {
    for (std::size_t i = 0; i < 16; i++) {
      data[i] -= other.data[i];
    }
  }

  template<typename C>
  matr<C> matr<C>::operator*= (C scale) {
    for (std::size_t i = 0; i < 16; i++) {
      data[i] *= scale;
    }
  }

  template<typename C>
  matr<C> matr<C>::operator/= (C scale) {
    for (std::size_t i = 0; i < 16; i++) {
      data[i] /= scale;
    }
  }


  template<typename C>
  matr<C> operator+ (matr<C> m1, matr<C> m2) {
    m1 += m2;
    return m1;
  }

  template<typename C>
  matr<C> operator- (matr<C> m1, matr<C> m2) {
    m1 -= m2;
    return m1;
  }

  template<typename C>
  matr<C> operator* (matr<C> m, C s) {
    m *= s;
    return m;
  }

  template<typename C>
  matr<C> operator/ (matr<C> m, matr<C> s) {
    m /= s;
    return m;
  }

  template<typename C>
  matr<C> operator* (matr<C> m1, matr<C> m2) {
    matr<C> m;

    for (std::size_t i = 0; i < 4; i++) {
      for (std::size_t j = 0; j < 4; j++) {
        C pos = 0;
        for (std::size_t k = 0; k < 4; k++) {
          pos += m1(i, k) * m2(k, j);
        }
        m(i, j) = pos;
      }
    }

    return m;
  }

  template<typename C>
  vec<C> operator* (matr<C> m, vec<C> v) {
    vec<C> rv;
    for (std::size_t i = 0; i < 4; ++i) {
      C pos = 0;
      for (std::size_t k = 0; k < 4; ++k) {
        pos += m(i, k) * v[k];
      }
      rv[i] = pos;
    }
    return rv;
  }

  template<typename C>
  vec<C> operator* (vec<C> v, matr<C> m) {
    vec<C> rv;
    for (std::size_t j = 0; j < 4; ++j) {
      C pos = 0;
      for (std::size_t k = 0; k < 4; ++k) {
        pos += m(k, j) * v[k];
      }
      rv[j] = pos;
    }
    return rv;
  }

  template<typename C>
  std::ostream& operator<< (std::ostream& os, const matr<C>& m) {
    for (std::size_t i = 0; i < 4; ++i) {
      os << "|  ";
      for (std::size_t j = 0; j < 4; ++j) {
        os << m(i, j) << "  ";
      }
      os << "|" << std::endl;
    }
    return os;
  }


}

#endif