/**
 * @author Daniel Escoz Solana
 */
#include "mesh.hpp"

void igr::mesh::clear () {
  vertices.clear();
  indices.clear();
}

void igr::mesh::add_vertex (point_t pt, vector_t normal, color_t col, texcoord_t texcoord) {
  pt.w = 1;
  normal.w = 0;
  vertices.emplace_back(pt, normal.normalized(), col, texcoord);
}

void igr::mesh::add_face (index_t idx1, index_t idx2, index_t idx3) {
  indices.push_back(idx1);
  indices.push_back(idx2);
  indices.push_back(idx3);
}



void igr::mesh::transform (matrix_t matr) {
  for (std::size_t i = 0; i < vertices.size(); ++i) {
    vertex_t v = vertices[i];
    v.point  = matr * v.point;
    v.normal = matr * v.normal;
    vertices[i] = v;
  }
}

igr::mesh igr::mesh::transformed (matrix_t matr) const {
  mesh other {*this};
  other.transform(matr);
  return other;
}


void igr::mesh::gl_draw_immediate () const {
  glBegin(GL_TRIANGLES);
  for (auto idx : indices) {
    auto vx = vertices[idx];
    glColor4f(vx.color.red, vx.color.green, vx.color.blue, vx.color.alpha);
    glNormal3f(vx.normal.x, vx.normal.y, vx.normal.z);
    glVertex3f(vx.point.x, vx.point.y, vx.point.z);
  }
  glEnd();
}

void igr::mesh::gl_draw_normals () const {
  glBegin(GL_LINES);
  for (auto idx : indices) {
    auto vx = vertices[idx];
    glColor4f(vx.color.red, vx.color.green, vx.color.blue, vx.color.alpha);
    glVertex3f(vx.point.x, vx.point.y, vx.point.z);
    glVertex3f(vx.point.x + vx.normal.x, vx.point.y + vx.normal.y, vx.point.z + vx.normal.z);
  }
  glEnd();
}


igr::mesh igr::mesh::make_aligned_box (color_t col) {
  point_t v1 { -0.5f, -0.5f, -0.5f };
  point_t v2 { +0.5f, +0.5f, +0.5f };

  mesh box {};

  /*box.add_vertex({v1.x, v1.y, v1.z}, {-1.f, -1.f, -1.f}, col, {});
  box.add_vertex({v2.x, v1.y, v1.z}, {+1.f, -1.f, -1.f}, col, {});
  box.add_vertex({v1.x, v2.y, v1.z}, {-1.f, +1.f, -1.f}, col, {});
  box.add_vertex({v2.x, v2.y, v1.z}, {+1.f, +1.f, -1.f}, col, {});
  box.add_vertex({v1.x, v1.y, v2.z}, {-1.f, -1.f, +1.f}, col, {});
  box.add_vertex({v2.x, v1.y, v2.z}, {+1.f, -1.f, +1.f}, col, {});
  box.add_vertex({v1.x, v2.y, v2.z}, {-1.f, +1.f, +1.f}, col, {});
  box.add_vertex({v2.x, v2.y, v2.z}, {+1.f, +1.f, +1.f}, col, {});

  box.add_face(0, 1, 2);   box.add_face(1, 3, 2);
  box.add_face(0, 2, 4);   box.add_face(4, 2, 6);
  box.add_face(1, 0, 4);   box.add_face(1, 4, 5);
  box.add_face(1, 5, 3);   box.add_face(5, 7, 3);
  box.add_face(2, 3, 6);   box.add_face(6, 3, 7);
  box.add_face(5, 4, 6);   box.add_face(5, 6, 7);*/

  /* Bottom */
  box.add_vertex({v1.x, v1.y, v1.z}, {0.f, -1.f, 0.f}, col, {});
  box.add_vertex({v1.x, v1.y, v2.z}, {0.f, -1.f, 0.f}, col, {});
  box.add_vertex({v2.x, v1.y, v1.z}, {0.f, -1.f, 0.f}, col, {});
  box.add_vertex({v2.x, v1.y, v2.z}, {0.f, -1.f, 0.f}, col, {});

  box.add_face(0, 1, 2);   box.add_face(1, 3, 2);

  /* Top */
  box.add_vertex({v1.x, v2.y, v1.z}, {0.f, +1.f, 0.f}, col, {});
  box.add_vertex({v1.x, v2.y, v2.z}, {0.f, +1.f, 0.f}, col, {});
  box.add_vertex({v2.x, v2.y, v1.z}, {0.f, +1.f, 0.f}, col, {});
  box.add_vertex({v2.x, v2.y, v2.z}, {0.f, +1.f, 0.f}, col, {});

  box.add_face(4, 6, 5);   box.add_face(5, 6, 7);

  /* Left */
  box.add_vertex({v1.x, v1.y, v1.z}, {-1.f, 0.f, 0.f}, col, {});
  box.add_vertex({v1.x, v1.y, v2.z}, {-1.f, 0.f, 0.f}, col, {});
  box.add_vertex({v1.x, v2.y, v1.z}, {-1.f, 0.f, 0.f}, col, {});
  box.add_vertex({v1.x, v2.y, v2.z}, {-1.f, 0.f, 0.f}, col, {});

  box.add_face(8, 10, 9);   box.add_face(9, 10, 11);

  /* Right */
  box.add_vertex({v2.x, v1.y, v1.z}, {+1.f, 0.f, 0.f}, col, {});
  box.add_vertex({v2.x, v1.y, v2.z}, {+1.f, 0.f, 0.f}, col, {});
  box.add_vertex({v2.x, v2.y, v1.z}, {+1.f, 0.f, 0.f}, col, {});
  box.add_vertex({v2.x, v2.y, v2.z}, {+1.f, 0.f, 0.f}, col, {});

  box.add_face(12, 13, 14);   box.add_face(13, 15, 14);

  /* Near */
  box.add_vertex({v1.x, v1.y, v1.z}, {0.f, 0.f, -1.f}, col, {});
  box.add_vertex({v1.x, v2.y, v1.z}, {0.f, 0.f, -1.f}, col, {});
  box.add_vertex({v2.x, v1.y, v1.z}, {0.f, 0.f, -1.f}, col, {});
  box.add_vertex({v2.x, v2.y, v1.z}, {0.f, 0.f, -1.f}, col, {});

  box.add_face(16, 18, 17);   box.add_face(17, 18, 19);

  /* Far */
  box.add_vertex({v1.x, v1.y, v2.z}, {0.f, 0.f, +1.f}, col, {});
  box.add_vertex({v1.x, v2.y, v2.z}, {0.f, 0.f, +1.f}, col, {});
  box.add_vertex({v2.x, v1.y, v2.z}, {0.f, 0.f, +1.f}, col, {});
  box.add_vertex({v2.x, v2.y, v2.z}, {0.f, 0.f, +1.f}, col, {});

  box.add_face(20, 21, 22);   box.add_face(21, 23, 22);



  return box;
}

igr::mesh igr::mesh::make_aligned_cylinder (color_t col, std::size_t sides) {
  mesh cyl;

  cyl.add_vertex(
      {0.0, 0.0, 0.5},
      {0.0, 0.0, 1.0},
      col, {}
  );
  cyl.add_vertex(
      {0.0, 0.0, -0.5},
      {0.0, 0.0, -1.0},
      col, {}
  );

  for (std::size_t i = 1; i <= sides; ++i) {
    double ang = (i - 1) * 2.0 * M_PI / (double) sides;

    /* Add the two vertices */
    cyl.add_vertex(
      {0.5 * cos(ang), 0.5 * sin(ang), 0.5},
      {cos(ang), sin(ang), 0},
      col, {}
    );
    cyl.add_vertex(
      {0.5 * cos(ang), 0.5 * sin(ang), -0.5},
      {cos(ang), sin(ang), 0},
      col, {}
    );

    std::size_t j = i - 1;

    std::size_t f00 = 2 + (j * 2);
    std::size_t f01 = 3 + (j * 2);
    std::size_t f10 = 2 + (((j + 1) * 2 )    % (sides * 2));
    std::size_t f11 = 2 + (((j + 1) * 2 + 1) % (sides * 2));

    /* Add the two faces */
    cyl.add_face(f00, f10, f01);
    cyl.add_face(f01, f10, f11);

    cyl.add_face(0, f10, f00);
    cyl.add_face(1, f01, f11);

  }

  return cyl;
}


std::ostream& igr::operator<< (std::ostream& os, const igr::mesh& m) {
  os << "mesh{" << std::endl << "  ";
  for (auto v : m.vertices) {
    os << v.point << std::endl << "  ";
  }
  for (auto i : m.indices) {
    os << i << ' ';
  }
  os << std::endl << "}" << std::flush;
  return os;
}