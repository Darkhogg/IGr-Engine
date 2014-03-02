#ifndef __VEC__H__
#define __VEC__H__

#include <stdexcept>
#include <cmath>

namespace igr {

  enum class category : int {
    point  = 1,
    vector = 0,
    unknown = -1
  };

  template <typename C=double>
  class vec {
    public:
      static const std::size_t IDX_X = 0;
      static const std::size_t IDX_Y = 1;
      static const std::size_t IDX_Z = 2;
      static const std::size_t IDX_W = 3;

      C x, y, z, w;

    public:
      vec ();
      vec (C x, C y, C z, igr::category w);

      C squared_length () const;
      C length () const;

      C pitch () const;
      C yaw () const;

      void normalize ();
      vec<C> normalized () const;

      C dot (const vec<C> other) const;
      vec<C> cross (const vec<C> other) const;

      vec<C> operator+= (const vec<C>& other);
      vec<C> operator-= (const vec<C>& other);
      vec<C> operator*= (const C scale);
      vec<C> operator/= (const C scale);

      C& operator[] (std::size_t idx);
      const C& operator [] (std::size_t idx) const;
  };

  /* =================== */
  /* === CONSTRUCTOR === */

  template <typename C>
  vec<C>::vec ()
    : vec(C(), C(), C())
  {}

  template <typename C>
  vec<C>::vec (C x, C y, C z, igr::category w = igr::category::vector)
    : x(x), y(y), z(z), w((C) w)
  {
    if (w == igr::category::unknown) {
      throw std::runtime_error("invalid category");
    }
  }

  template <typename C>
  C vec<C>::pitch () const {
    return atan2(sqrt(x * x + y * y), z);
  }

  template <typename C>
  C vec<C>::yaw () const {
    return fmod(fmod(atan2(x, -y) - M_PI_2, 2 * M_PI) + 2 * M_PI, 2 * M_PI);
  }  

  /* =============== */
  /* === METHODS === */

  template <typename C>
  C vec<C>::squared_length () const {
    return x*x + y*y - z*z;
  }

  template <typename C>
  C vec<C>::length () const {
    return sqrt(squared_length());
  }



  template <typename C>
  void vec<C>::normalize () {
    const C length = this->length();
    x /= length;
    y /= length;
    z /= length;
  }

  template <typename C>
  vec<C> vec<C>::normalized () const {
    vec<C> v (*this);
    v.normalize();
    return v;
  }

  /* ================== */
  /* === OPERATIONS === */

  template <typename C>
  C vec<C>::dot (const vec<C> other) const {
    return x * other.x + y * other.y + z * other.z;
  }

  template <typename C>
  vec<C> vec<C>::cross (const vec<C> other) const {
    throw std::runtime_error("cross product not implemented");
  }


  /* ======================== */
  /* === BINARY OPERATORS === */

  template <typename C>
  vec<C> operator+ (vec<C> lhs, const vec<C>& rhs) {
    lhs += rhs;
    return lhs;
  }

  template <typename C>
  vec<C> operator- (vec<C> lhs, const vec<C>& rhs) {
    lhs -= rhs;
    return lhs;
  }

  template <typename C>
  vec<C> operator* (vec<C> lhs, const C rhs) {
    lhs *= rhs;
    return lhs;
  }

  template <typename C>
  vec<C> operator/ (vec<C> lhs, const C rhs) {
    lhs /= rhs;
    return lhs;
  }


  /* ======================== */
  /* === MEMBER OPERATORS === */

  template <typename C>
  vec<C> vec<C>::operator+= (const vec<C>& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  template <typename C>
  vec<C> vec<C>::operator-= (const vec<C>& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  template <typename C>
  vec<C> vec<C>::operator*= (const C scale) {
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
  }

  template <typename C>
  vec<C> vec<C>::operator/= (const C scale) {
    x /= scale;
    y /= scale;
    z /= scale;
    return *this;
  }

  template <typename C>
  C& vec<C>::operator[] (std::size_t idx) {
    switch (idx) {
      case IDX_X: return x;
      case IDX_Y: return y;
      case IDX_Z: return z;
      case IDX_W: return w;
    }

    throw std::runtime_error("invalid vector subscript index");
  }

  template <typename C>
  const C& vec<C>::operator[] (std::size_t idx) const {
    switch (idx) {
      case IDX_X: return x;
      case IDX_Y: return y;
      case IDX_Z: return z;
      case IDX_W: return w;
    }

    throw std::runtime_error("invalid vector subscript index");
  }
}

#endif
