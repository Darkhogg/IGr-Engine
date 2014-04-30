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
  normal.normalize();
  vertices.emplace_back(pt, normal, col, texcoord);
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
  #define BOXDIV 6

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

  std::size_t k = 0;

  /* Bottom */
  for (std::size_t i = 0; i < BOXDIV; ++i) {
    for (std::size_t j = 0; j < BOXDIV; ++j) {
      double step = (1.0 / (double) BOXDIV);

      box.add_vertex({v1.x + step * i,     v1.y, v1.z + step * j},     {0.f, -1.f, 0.f}, col, {});
      box.add_vertex({v1.x + step * i,     v1.y, v1.z + step * (j+1)}, {0.f, -1.f, 0.f}, col, {});
      box.add_vertex({v1.x + step * (i+1), v1.y, v1.z + step * j},     {0.f, -1.f, 0.f}, col, {});
      box.add_vertex({v1.x + step * (i+1), v1.y, v1.z + step * (j+1)}, {0.f, -1.f, 0.f}, col, {});

      box.add_face(k, k + 1, k + 2);   box.add_face(k + 1, k + 3, k + 2);
      k += 4;
    }
  }

  /* Top */
  for (std::size_t i = 0; i < BOXDIV; ++i) {
    for (std::size_t j = 0; j < BOXDIV; ++j) {
      double step = (1.0 / (double) BOXDIV);

      box.add_vertex({v1.x + step * i,     v2.y, v1.z + step * j},     {0.f, +1.f, 0.f}, col, {});
      box.add_vertex({v1.x + step * i,     v2.y, v1.z + step * (j+1)}, {0.f, +1.f, 0.f}, col, {});
      box.add_vertex({v1.x + step * (i+1), v2.y, v1.z + step * j},     {0.f, +1.f, 0.f}, col, {});
      box.add_vertex({v1.x + step * (i+1), v2.y, v1.z + step * (j+1)}, {0.f, +1.f, 0.f}, col, {});

      box.add_face(k, k + 2, k + 1);   box.add_face(k + 1, k + 2, k + 3);
      k += 4;
    }
  }

  /* Left */
  for (std::size_t i = 0; i < BOXDIV; ++i) {
    for (std::size_t j = 0; j < BOXDIV; ++j) {
      double step = (1.0 / (double) BOXDIV);

      box.add_vertex({v1.x, v1.y + step * i,     v1.z + step * j},     {-1.f, 0.f, 0.f}, col, {});
      box.add_vertex({v1.x, v1.y + step * i,     v1.z + step * (j+1)}, {-1.f, 0.f, 0.f}, col, {});
      box.add_vertex({v1.x, v1.y + step * (i+1), v1.z + step * j},     {-1.f, 0.f, 0.f}, col, {});
      box.add_vertex({v1.x, v1.y + step * (i+1), v1.z + step * (j+1)}, {-1.f, 0.f, 0.f}, col, {});

      box.add_face(k, k + 2, k + 1);   box.add_face(k + 1, k + 2, k + 3);
      k += 4;
    }
  }

  /* Right */
  for (std::size_t i = 0; i < BOXDIV; ++i) {
    for (std::size_t j = 0; j < BOXDIV; ++j) {
      double step = (1.0 / (double) BOXDIV);

      box.add_vertex({v2.x, v1.y + step * i,     v1.z + step * j},     {+1.f, 0.f, 0.f}, col, {});
      box.add_vertex({v2.x, v1.y + step * i,     v1.z + step * (j+1)}, {+1.f, 0.f, 0.f}, col, {});
      box.add_vertex({v2.x, v1.y + step * (i+1), v1.z + step * j},     {+1.f, 0.f, 0.f}, col, {});
      box.add_vertex({v2.x, v1.y + step * (i+1), v1.z + step * (j+1)}, {+1.f, 0.f, 0.f}, col, {});

      box.add_face(k, k + 1, k + 2);   box.add_face(k + 1, k + 3, k + 2);
      k += 4;
    }
  }

  /* Near */
  for (std::size_t i = 0; i < BOXDIV; ++i) {
    for (std::size_t j = 0; j < BOXDIV; ++j) {
      double step = (1.0 / (double) BOXDIV);

      box.add_vertex({v1.x + step * i,     v1.y + step * j,     v1.z}, {0.f, 0.f, -1.f}, col, {});
      box.add_vertex({v1.x + step * i,     v1.y + step * (j+1), v1.z}, {0.f, 0.f, -1.f}, col, {});
      box.add_vertex({v1.x + step * (i+1), v1.y + step * j,     v1.z}, {0.f, 0.f, -1.f}, col, {});
      box.add_vertex({v1.x + step * (i+1), v1.y + step * (j+1), v1.z}, {0.f, 0.f, -1.f}, col, {});

      box.add_face(k, k + 2, k + 1);   box.add_face(k + 1, k + 2, k + 3);
      k += 4;
    }
  }

  /* Far */
  for (std::size_t i = 0; i < BOXDIV; ++i) {
    for (std::size_t j = 0; j < BOXDIV; ++j) {
      double step = (1.0 / (double) BOXDIV);

      box.add_vertex({v1.x + step * i,     v1.y + step * j,     v2.z}, {0.f, 0.f, +1.f}, col, {});
      box.add_vertex({v1.x + step * i,     v1.y + step * (j+1), v2.z}, {0.f, 0.f, +1.f}, col, {});
      box.add_vertex({v1.x + step * (i+1), v1.y + step * j,     v2.z}, {0.f, 0.f, +1.f}, col, {});
      box.add_vertex({v1.x + step * (i+1), v1.y + step * (j+1), v2.z}, {0.f, 0.f, +1.f}, col, {});

      box.add_face(k, k + 1, k + 2);   box.add_face(k + 1, k + 3, k + 2);
      k += 4;
    }
  }



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

igr::mesh igr::mesh::make_aligned_sphere (color_t col, std::size_t meridians, std::size_t parallels) {
  mesh sph;

  sph.add_vertex({0.0, -0.5, 0.0}, {0.0, -1.0, 0.0}, col, {});
  sph.add_vertex({0.0,  0.5, 0.0}, {0.0,  1.0, 0.0}, col, {});

  for (std::size_t p = 0; p < parallels; ++p) {
    double angy = M_PI * (((double) p + 1.0) / ((double) parallels + 1.0));
    double siny = sin(angy);
    double posY = -cos(angy) * 0.5;

    for (std::size_t m = 0; m < meridians; ++m) {
      double ang = m * (2.0 * M_PI / (double) meridians);
      double posX = 0.5 * cos(ang) * siny;
      double posZ = 0.5 * sin(ang) * siny;

      sph.add_vertex({posX, posY, posZ}, {posX, posY, posZ}, col, {});

      /* Join vertex with the next */
      std::size_t k00 = 2 + m * parallels + p;
      std::size_t k01 = 2 + m * parallels + ((p + 1) % parallels);
      std::size_t k10 = 2 + ((m + 1) % meridians) * parallels + p;
      std::size_t k11 = 2 + ((m + 1) % meridians) * parallels + ((p + 1) % parallels);

      if (m < meridians - 1) {
        // Case 1: we are in an interior row
        sph.add_face(k00, k01, k10);
        sph.add_face(k10, k01, k11);

      } else {
        // Case 2: we are in the LAST row
        sph.add_face(k00, k01, 1);
      }

      // Special case: we are in the FIRST row
      if (m == 0) {
        sph.add_face(k01, k00, 0);
      }
    }

  }

  return sph;
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