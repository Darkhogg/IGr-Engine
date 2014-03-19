#include "mesh.hpp"

void igr::mesh::clear () {
  vertices.clear();
  indices.clear();
}

void igr::mesh::add_vertex (point_t pt, vector_t normal, color_t col, texcoord_t texcoord) {
  vertices.emplace_back(pt, normal.normalized(), col, texcoord);
}

void igr::mesh::add_face (index_t idx1, index_t idx2, index_t idx3) {
  indices.push_back(idx1);
  indices.push_back(idx2);
  indices.push_back(idx3);
}

void igr::mesh::gl_draw_immediate () {
  glBegin(GL_TRIANGLES);
  for (auto idx : indices) {
    auto vx = vertices[idx];
    glColor4f(vx.color.red, vx.color.green, vx.color.blue, vx.color.alpha);
    glNormal3f(vx.normal.x, vx.normal.y, vx.normal.z);
    glVertex3f(vx.point.x, vx.point.y, vx.point.z);
  }
  glEnd();
}


igr::mesh igr::mesh::make_aligned_box (color_t col) {
  point_t v1 { -0.5f, -0.5f, -0.5f };
  point_t v2 { +0.5f, +0.5f, +0.5f };

  mesh box {};

  box.add_vertex({v1.x, v1.y, v1.z}, {-1.f, -1.f, -1.f}, col, {});
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
  box.add_face(5, 4, 6);   box.add_face(5, 6, 7);

  return box;
}