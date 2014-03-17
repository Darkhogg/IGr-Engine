#ifndef __MESH__HPP__
#define __MESH__HPP__

#include "vec.hpp"
#include "matr.hpp"
#include "color.hpp"

#include <vector>
#include <tuple>
#include <iostream>

namespace igr {

  class mesh {

    public:
      using point_t    = vec<double>;
      using vector_t   = vec<double>;
      using color_t    = color;
      using texcoord_t = vec<double>;
      using index_t    = std::size_t;
      using matrix_t   = matr<double>;

    private:
      /* Description of a vertex */
      struct vertex_t {
        point_t    point;
        vector_t   normal;
        color_t    color;
        texcoord_t texcoord;

        vertex_t (point_t p, vector_t n, color_t c, texcoord_t t)
          : point{p}, normal{n}, color{c}, texcoord{t}
          {}
      };

    private:
      std::vector<vertex_t> vertices;
      std::vector<index_t>  indices;

    public:
      mesh () {}

      void clear ();

      void add_vertex (point_t pt, vector_t normal, color_t col, texcoord_t texcoord);
      void add_face (index_t idx1, index_t idx2, index_t idx3);

      void transform (matrix_t matrix);

      void gl_store();
      void gl_draw();
      void gl_draw_immediate();

      static mesh make_aligned_box (color_t col);
  };

}

#endif