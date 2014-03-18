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

      const C& operator() (std::size_t i, std::size_t j) const;
      C& operator() (std::size_t i, std::size_t j);

      void gl_load (GLenum);
      void gl_store () const;

      static matr<C> transform (vec<C> from, vec<C> to);

      static matr<C> make_translation (vec<C> translation);
      static matr<C> make_scalation (vec<C> scalation);
      static matr<C> make_rotation (vec<C> around, double angle);
  };


  /* ======================= */
  /* === POSITION ACCESS === */

  template<typename C>
  const C& matr<C>::operator() (std::size_t i, std::size_t j) const {
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
    const C* md = data.data();
    float mf[16];
    for (std::size_t i = 0; i <16; i++) {
      mf[i] = (float) md[i];
    }

    glLoadMatrixf(mf);
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


  /* ====================== */
  /* === TRANSFORMATION === */

  template<typename C>
  matr<C> matr<C>::transform (vec<C> from, vec<C> to) {
    matr<C> m;
    for (std::size_t i = 0; i < 4; i++) {
      for (std::size_t j = 0; j < 4; j++) {
        m(i, j) = from[i] * to[j];
      }
    }
    return m;
  }

}

#endif