#pragma once

#ifndef VEGA_GL_MAJOR
#define VEGA_GL_MAJOR 4
#endif

#ifndef VEGA_GL_MINOR
#define VEGA_GL_MINOR 3
#endif

#define VEGA_RUNTIME_ERROR(X, MESSAGE) if(X) throw std::runtime_error(MESSAGE)

#define VEGA_SINGLETON(TYPE)                                          \
public:                                                               \
  inline static TYPE *sInstance = nullptr;                            \
                                                                      \
  explicit TYPE(const TYPE &) = delete;                               \
  TYPE &operator=(const TYPE &) = delete;                             \
                                                                      \
  static TYPE &Get() {                                                \
    if (!sInstance) sInstance = new TYPE();                           \
    return *sInstance;                                                \
  }                                                                   \
                                                                      \
  template<typename ... Args>                                         \
  static TYPE &Get(Args &&... arg) {                                  \
    if (!sInstance) sInstance = new TYPE(std::forward<Args>(arg)...); \
    return *sInstance;                                                \
  }                                                                   \
                                                                      \
  static void Delete() {                                              \
    delete sInstance;                                                 \
  }

#define VEGA_INSTANCE(TYPE, ...) TYPE::Get(__VA_ARGS__)