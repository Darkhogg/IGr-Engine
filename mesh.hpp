/**
 * @author Daniel Escoz Solana
 */
#ifndef __MESH__HPP__
#define __MESH__HPP__

#include "vec.hpp"
#include "matr.hpp"
#include "color.hpp"

#include <vector>
#include <tuple>
#include <ostream>

namespace igr {

  class mesh {

    public:
      using point_t    = vec<double>;
      using vector_t   = vec<double>;
      using color_t    = color;
      using texcoord_t = vec<double>;
      using index_t    = std::size_t;
      using matrix_t   = matr<double>;

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

    public:
      std::vector<vertex_t> vertices;
      std::vector<index_t>  indices;

    public:
      mesh () {}

      void clear ();

      void add_vertex (point_t pt, vector_t normal, color_t col, texcoord_t texcoord);
      void add_face (index_t idx1, index_t idx2, index_t idx3);

      void transform (matrix_t matrix);
      mesh transformed (matrix_t matrix) const;

      void gl_store() const;
      void gl_draw();
      void gl_draw_immediate() const;

      void gl_draw_normals() const;

      static mesh make_aligned_box (color_t col);
      static mesh make_aligned_cylinder (color_t col, std::size_t sides);
      static mesh make_aligned_sphere (color_t col, std::size_t meridians, std::size_t parallels);

      friend std::ostream& operator<< (std::ostream& os, const igr::mesh& m);
  };
  
}

#endif