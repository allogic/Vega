#pragma once

#if defined(__WIN64__)
#define VEGA_API
#elif defined(__APPLE__)
#define VEGA_API
#elif defined(__linux__)
#define VEGA_API
#endif

#ifndef VEGA_GL_MAJOR
#define VEGA_GL_MAJOR 4
#endif

#ifndef VEGA_GL_MINOR
#define VEGA_GL_MINOR 3
#endif

#define VEGA_DEBUG

#ifdef VEGA_DEBUG
#define VEGA_ENABLE_GUI
#endif

#define VEGA_RUNTIME_ERROR(X, MESSAGE) if(X) throw std::runtime_error(MESSAGE)

#define MEASURE_BEGIN(NAME) auto NAME##_measure = std::chrono::high_resolution_clock::now()
#define MEASURE_END(NAME, TYPE) std::chrono::duration_cast<TYPE>(NAME##_measure - std::chrono::high_resolution_clock::now()).count()

#define SINGLETON(TYPE)                                               \
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