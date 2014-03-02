#ifndef __GL_OBJ__HPP__
#define __GL_OBJ__HPP__

#include "common.h"

namespace igr {

  template<
    void (*func_create)(GLsizei, GLuint*),
    void (*func_delete)(GLsizei, const GLuint*)
  >
  struct gl_obj
  {
      GLuint handle;


      gl_obj () : handle{} 
      {
        func_create(1, &handle);
      }


      gl_obj (const gl_obj<func_create, func_delete>& other)
        = delete;


      gl_obj (gl_obj<func_create, func_delete>&& other)
      {
        std::swap(handle, other.handle);
      }


      ~gl_obj ()
      {
        func_delete(1, &handle);
      }


      gl_obj<func_create, func_delete>&
      operator= (const gl_obj<func_create, func_delete>& other)
        = delete;


      gl_obj<func_create, func_delete>&
      operator= (gl_obj<func_create, func_delete>&& other)
      {
        std::swap(handle, other.handle);
        return *this;
      }
  };


  using gl_texture = gl_obj<glGenTextures, glDeleteTextures>;

};

#endif