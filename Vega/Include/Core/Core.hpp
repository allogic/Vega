#ifndef CORE_HPP
#define CORE_HPP

#ifdef VEGA_ENABLE_DEBUG

#include <spdlog/spdlog.h>

#define VEGA_INFO(FMT, ...) spdlog::info(FMT, __VA_ARGS__);
#define VEGA_WARN(FMT, ...) spdlog::warn(FMT, __VA_ARGS__);
#define VEGA_ERROR(FMT, ...) spdlog::error(FMT, __VA_ARGS__);

#define VEGA_MEASURE_BEGIN(NAME) auto NAME##_measure = std::chrono::high_resolution_clock::now();
#define VEGA_MEASURE_END(NAME, TYPE) std::chrono::duration_cast<std::chrono::TYPE>(NAME##_measure - std::chrono::high_resolution_clock::now()).count())

#else

#define VEGA_INFO(FMT, ...) {}
#define VEGA_WARN(FMT, ...) {}
#define VEGA_ERROR(FMT, ...) {}

#define VEGA_MEASURE_BEGIN(NAME)
#define VEGA_MEASURE_END(NAME, TYPE)

#endif

#define VEGA_SINGLETON(TYPE)                                          \
public:                                                               \
  inline static TYPE *sInstance = nullptr;                            \
                                                                      \
  TYPE(const TYPE &) = delete;                                        \
  TYPE(TYPE &&) noexcept = delete;                                    \
                                                                      \
  TYPE &operator=(const TYPE &) = delete;                             \
                                                                      \
  static TYPE &Instance() {                                           \
    if (!sInstance) sInstance = new TYPE();                           \
    return *sInstance;                                                \
  }                                                                   \
                                                                      \
  template<typename ... Args>                                         \
  static TYPE &Instance(Args &&... arg) {                             \
    if (!sInstance) sInstance = new TYPE(std::forward<Args>(arg)...); \
    return *sInstance;                                                \
  }                                                                   \
                                                                      \
  static void Delete() {                                              \
    delete sInstance;                                                 \
    sInstance = nullptr;                                              \
  }

#endif