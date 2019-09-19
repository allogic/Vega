#ifndef SINGLETON_H
#define SINGLETON_H

namespace vega {
  template<typename T>
  static T *instance;

  template<typename T>
  static inline T &Get() {
    return *instance<T>;
  }

  template<typename T, typename ... Args>
  static inline T &Get(Args &&... arg) {
    instance<T> = new T(std::forward<Args>(arg)...);

    return *instance<T>;
  }
}

#endif