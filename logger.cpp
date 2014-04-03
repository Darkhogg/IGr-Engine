#include "logger.hpp"

dhg::logger::session dhg::logger::operator() (dhg::loglvl lvl) {
  return {lvl};
}

dhg::logger::session::session(dhg::loglvl lvl) {
  ss << " \033[1;3";
  switch (lvl) {
    case dhg::loglvl::debug: ss << "4mdbg"; break;
    case dhg::loglvl::info:  ss << "2minf"; break;
    case dhg::loglvl::warn:  ss << "3mwrn"; break;
    case dhg::loglvl::error: ss << "1merr"; break;
  }
  ss << "\033[m  ";
}

dhg::logger::session::~session() {
  std::cout << ss.str();
}

std::ostream& dhg::logger::session::operator() () {
  return ss;
}