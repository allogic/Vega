#include <Vega/Std.hpp>

#include <Vega/Core/Compiler.hpp>

#include <Vega/Vendor/Glad.hpp>

bool Vega::Core::Compiler::Cpp(const boost::filesystem::path &input,
                               const boost::filesystem::path &output,
                               bool verbose) {
  std::stringstream ss;

  ss << CONFIG_GET(std::string, "cpp-compiler") << " "
     << "-std=c++17 "
     << "-shared "
     << "-fPIC "
     << "-I" << CONFIG_GET(std::string, "vega-source-path") << " "
     << "-I" << CONFIG_GET(std::string, "sketch-path") << " "
     << input.string() << " "
     << "-o " << output.string() << ".so "
     << (verbose ? "" : "> /dev/null 2>&1");

  return std::system(ss.str().c_str()) == 0;
}

bool Vega::Core::Compiler::Glsl(const std::vector<boost::filesystem::path> &files,
                                const boost::filesystem::path &outputFile,
                                bool verbose) {
  bool error = false;

  for (const auto &file : files) {
    unsigned int sid = 0;

    if (file.extension() == ".vert") sid = glCreateShader(GL_VERTEX_SHADER);
    else if (file.extension() == ".frag") sid = glCreateShader(GL_FRAGMENT_SHADER);
    else {
      error = true;
      continue;
    };

    std::stringstream ss;

    ss << "#version " << CONFIG_GET(std::string, "glsl-version") << " core\n";

    //if (file.extension() == ".vert") ss << "#vertex\n";
    //else if (file.extension() == ".frag") ss << "#fragment\n";

    std::ifstream stream(file.string(), std::ios_base::in);

    if (!stream.good()) {
      stream.close();

      error = true;
      continue;
    }

    std::string line;

    while (std::getline(stream, line))
      ss << line << '\n';

    std::string shader = ss.str();

    const char *ptr = shader.c_str();

    glShaderSource(sid, 1, &ptr, nullptr);
    glCompileShader(sid);

    int info, size;

    glGetShaderiv(sid, GL_COMPILE_STATUS, &info);
    glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &size);

    if (verbose && size > 0) {
      std::string msg;

      msg.reserve(size);

      glGetShaderInfoLog(sid, size, nullptr, &msg[0]);

      std::cerr << msg;

      error = true;
    }
  }

  return error == 0;
}
