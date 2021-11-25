#ifndef INHERIT_OBJECTCOUNTER_HPP
#define INHERIT_OBJECTCOUNTER_HPP

#include <cstddef>

namespace inherit {

/**
 * @brief This class utilizes the CRTP idiom to calculate
 * the number of active objects in the memory.
 */

template<typename CountedType>
class ObjectCounter {
  private:
  inline static std::size_t number_of_existing_objects = 0;

  protected:
    ObjectCounter() {
      ++number_of_existing_objects;
    }

    ~ObjectCounter() {
      --number_of_existing_objects;
    }

    ObjectCounter(ObjectCounter<CountedType> const&) {
      ++number_of_existing_objects;
    }

    ObjectCounter(ObjectCounter<CountedType> const&&) {
      ++number_of_existing_objects;
    }

  public:
  static std::size_t live() {
    return number_of_existing_objects;
  }
};

template<typename NumberT>
class CustomNumber : public ObjectCounter<CustomNumber<NumberT>> {
  private:
  const NumberT number;

  public:
  CustomNumber(NumberT number) : number(number) {}

  NumberT value() {return number;}
};

} // namespace inherit

#endif // INHERIT_OBJECTCOUNTER_HPP