#ifndef SINGLETON_H
#define SINGLETON_H

namespace vega::instance {
  template<typename T>
  static T *instance;

  template<typename T>
  static inline T &get() {
    return *instance<T>;
  }

  template<typename T, typename ... Args>
  static inline T &get(Args &&... arg) {
    instance<T> = new T(std::forward<Args>(arg)...);

    return *instance<T>;
  }
}

#endif