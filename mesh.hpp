#ifndef __MESH__HPP__
#define __MESH__HPP__

#include "vec.hpp"
#include "matr.hpp"
#include "color.hpp"

#include <vector>
#include <tuple>

namespace igr {

  class mesh {
    public:
      using point_t  = vec<double>;
      using vector_t = vec<double>;
      using color_t  = color;
      using vertex_t = std::tuple<point_t, vector_t, color_t>;
      using index_t  = std::size_t;
      using matrix_t = matr<double>;

    private:
      std::vector<vertex_t> vertices;
      std::vector<index_t> indices;

    public:
      mesh () {}

      mesh (std::vector<vertex_t> vs, std::vector<index_t> is)
        : vertices{vs}, indices{is}
      {}

      void transform (matrix_t matrix);

      void gl_store();
      void gl_draw();

      static mesh make_aligned_box (point_t from, point_t to, color_t col);
  };

}

#endif