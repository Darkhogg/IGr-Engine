#include "mesh.hpp"




igr::mesh igr::mesh::make_aligned_box (point_t from, point_t to, color_t col) {
  point_t v1 { std::min(from.x, to.x),
               std::min(from.y, to.y),
               std::min(from.z, to.z) };

  point_t v2 { std::max(from.x, to.x),
               std::max(from.y, to.y),
               std::max(from.z, to.z) };

  float sq3 = sqrtf(3);

  return {
    /* List of vertices */
    {
      std::tuple<point_t, vector_t, color_t>({v1.x, v1.y, v1.z}, {-sq3, -sq3, -sq3}, col),
      std::tuple<point_t, vector_t, color_t>({v2.x, v1.y, v1.z}, {+sq3, -sq3, -sq3}, col),
      std::tuple<point_t, vector_t, color_t>({v1.x, v2.y, v1.z}, {-sq3, +sq3, -sq3}, col),
      std::tuple<point_t, vector_t, color_t>({v2.x, v2.y, v1.z}, {+sq3, +sq3, -sq3}, col),
      std::tuple<point_t, vector_t, color_t>({v1.x, v1.y, v2.z}, {-sq3, -sq3, +sq3}, col),
      std::tuple<point_t, vector_t, color_t>({v2.x, v1.y, v2.z}, {+sq3, -sq3, +sq3}, col),
      std::tuple<point_t, vector_t, color_t>({v1.x, v2.y, v2.z}, {-sq3, +sq3, +sq3}, col),
      std::tuple<point_t, vector_t, color_t>({v2.x, v2.y, v2.z}, {+sq3, +sq3, +sq3}, col)
    },

    /* Indices for GL_TRIANGLES */
    {
      0, 1, 2,   1, 2, 3,
      0, 2, 4,   2, 4, 6,
      0, 1, 4,   1, 4, 5,
      1, 3, 5,   3, 5, 7,
      2, 3, 6,   3, 6, 7,
      4, 5, 6,   5, 6, 7
    }
  };
}