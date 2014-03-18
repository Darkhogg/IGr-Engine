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

      template<typename VC>
      static matr<VC> make_translation (vec<VC> translation);

      template<typename VC>
      static matr<VC> make_scalation (vec<VC> scalation);

      template<typename VC>
      static matr<VC> make_rotation (vec<VC> around, double angle);
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

    template<typename VC>
    matr<VC> matr::make_translation (vec<VC> translation) {
      matr<VC> m;

      return m;
    }

    template<typename VC>
    matr<VC> matr::make_scalation (vec<VC> scalation) {

    }

    template<typename VC>
    matr<VC> matr::make_rotation (vec<VC> around, double angle) {

    }

}

#endif