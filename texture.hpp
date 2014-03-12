#ifndef __TEXTURE__HPP__
#define __TEXTURE__HPP__

#include "common.h"
#include "gl_obj.hpp"

#include <memory>

namespace igr {

  class texture {
    private:
      std::shared_ptr<gl_texture> _globj;

    public:
      texture () :
        _globj{std::make_shared<gl_texture>()}
      {}

      void gl_bind (GLenum target) const;
  };

}

#endif