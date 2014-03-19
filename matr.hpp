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
        { 0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0,
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
  matr<C> matr<C>::make_rotation (vec<C> around, double angle) {
    matr<C> m;

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
        C pos;
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
    
  }

}

#endif