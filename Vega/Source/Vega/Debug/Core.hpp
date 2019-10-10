#pragma once

#ifdef VEGA_ENABLE_DEBUG

#define VEGA_ENABLE_GUI
#define VEGA_GUI_VERSION "430"

#define VEGA_INFO(FMT, ...) std::fprintf(stdout, "[LINE:%d] [FILE:%s] " FMT "\n", __LINE__, __FILE__, __VA_ARGS__);
#define VEGA_ERROR(FMT, ...) std::fprintf(stderr, "[LINE:%d] [FILE:%s] " FMT "\n", __LINE__, __FILE__, __VA_ARGS__);

#define VEGA_MEASURE_BEGIN(NAME) auto NAME##_measure = std::chrono::high_resolution_clock::now();
#define VEGA_MEASURE_END(NAME, TYPE) VEGA_INFO("[%d]", std::chrono::duration_cast<std::chrono::TYPE>(NAME##_measure - std::chrono::high_resolution_clock::now()).count());

#define VEGA_DRAW_CONSOLE()       \
public:                           \
  inline void DrawConsole() {     \
    ImGui::Text("Console");       \
  }

#define VEGA_DRAW_SHADER_EDITOR()   \
public:                             \
  inline void DrawShaderEditor() {  \
                                    \
  }

#else

#define VEGA_INFO(FMT, ...)
#define VEGA_ERROR(FMT, ...)

#define VEGA_MEASURE_BEGIN(NAME)
#define VEGA_MEASURE_END(NAME, TYPE)

#endif