#pragma once

#include <iostream>
#include <chrono>

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
#define VEGA_ENABLE_ASSERTS
#define VEGA_ENABLE_GUI
#endif

#ifdef VEGA_ENABLE_ASSERTS
#define VEGA_ASSERT(X, MESSAGE) { if (!X) std::cerr << MESSAGE << std::endl; }
#else
#define VEGA_ASSERT(X, MESSAGE)
#endif

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
  static void Del() {                                                 \
    delete sInstance;                                                 \
  }

#define MEASURE_BEGIN(NAME) auto NAME##_measure = std::chrono::high_resolution_clock::now()
#define MEASURE_END(NAME, TYPE) std::chrono::duration_cast<TYPE>(NAME##_measure - std::chrono::high_resolution_clock::now()).count()