#ifndef REF_ERROR_HPP
#define REF_ERROR_HPP

namespace basics {

template<typename T, T Z = T{}>
class RefMem {
  private:
   T zero;
  public:
  RefMem(): zero{Z} {

  }
};

} // basics

#endif