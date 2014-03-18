#ifndef __MATR__H__
#define __MATR__H__

namespace igr {

  template <typename C=double>
  class matr {
    private:
      C data[4][4];

    public:
      matr () : data{{
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
      }}
      {}

      const C& operator() (std::size_t i, std::size_t j) const;
      C& operator() (std::size_t i, std::size_t j);

      static matr<C> make_translation (vec<C> translation);
      static matr<C> make_scalation (vec<C> scalation);
      static matr<C> make_rotation (vec<C> around, double angle);
  };


  /* ======================= */
  /* === POSITION ACCESS === */

  template<typename C>
  const C& matr<C>::operator() (std::size_t i, std::size_t j) const {
    return data[i][j];
  }


  template<typename C>
  C& matr<C>::operator() (std::size_t i, std::size_t j) {
    return data[i][j];
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

}

#endif