#include <cstdint>
#include <iostream>
#include <sstream>

namespace dhg {

  enum class loglvl : int8_t {
    debug = 0,
    info  = 1,
    warn  = 2,
    error = 3
  };

  class logger {
    public:
      class session {
          std::stringstream ss;

        public:
          session (loglvl lvl);
          ~session ();

          std::ostream& operator() ();
      };
      
      logger::session operator() (loglvl lvl);
  };

}