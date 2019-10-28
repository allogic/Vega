#include <Vega/Core/Compiler.hpp>

#include <Vega/Vendor/Glad.hpp>

bool Vega::Core::Compiler::CompilePlugin(const std::string &name,
                                         const std::vector<fs::path> &files,
                                         const std::string &outputFile,
                                         bool verbose) {
  std::stringstream ss;

  for (const auto &file : files) ss << file.string() << ' ';

  std::string filesFormatted(ss.str());

  ss.clear();
  ss.str("");

  std::string cmd(ss.str());

  int pid;
  int fds[2];

  pid = pipe(fds);

  if (pid < 0) {
    VEGA_ERROR("Process pipe error: %d", pid)

    return false;
  }

  pid = fork();

  if (pid < 0) {
    VEGA_ERROR("Process fork error: %d", pid)

    return false;
  }

  if (pid == 0) {
    dup2(fds[1], STDOUT_FILENO);

    close(fds[0]);
    close(fds[1]);

    std::string compiler = CONFIG_GET(std::string, "cpp-compiler");
    std::string include = CONFIG_GET(std::string, "vega-source-path");

    // TODO create some utility trim functions

    std::cout << include << '@' << std::endl;
    std::cout << filesFormatted << '@' << std::endl;
    std::cout << outputFile << '@' << std::endl;

    execl(
        compiler.c_str(),
        compiler.c_str(),
        "-shared",
        "-fPIC",
        std::string{"-I" + include}.c_str(),
        filesFormatted.c_str(),
        std::string{"-o" + outputFile + ".so"}.c_str(),
        nullptr
    );
  }

  close(fds[1]);

  auto *cmdOutputFd = fdopen(fds[0], "r");

  char line[1024];

  if (verbose) {
    VEGA_INFO("Begin compiling plugin %s", name.c_str())
    VEGA_INFO("===========%s COMPILING===========", "BEGIN")

    while (std::fgets(line, sizeof(line), cmdOutputFd))
      std::cerr << line;

    VEGA_INFO("===========%s COMPILING===========", " END ")
    VEGA_INFO("End compiling plugin %s", name.c_str())
  }

  pclose(cmdOutputFd);

  int result;

  wait(&result);

  if (WIFEXITED(result)) return false;

  return true;
}

bool Vega::Core::Compiler::CompileShader(const std::string &name,
                                         const std::vector<fs::path> &files,
                                         const std::string &outputFile,
                                         bool verbose) {
  std::ofstream stream(std::string{outputFile + ".gl"});

  if (!stream.is_open()) {
    stream.close();

    return false;
  }

  unsigned int pid = glCreateProgram();

  for (const auto &file : files) {
    unsigned int sid;

    if (file.extension() == ".vert") sid = glCreateShader(GL_VERTEX_SHADER);
    else if (file.extension() == ".frag") sid = glCreateShader(GL_FRAGMENT_SHADER);
    else {
      VEGA_ERROR("Shader extension (%s) not supported", file.extension().c_str())

      break;
    }

    std::string shader;

    Utility::Io::Read(shader, file);

    const char *ptr = shader.c_str();

    glShaderSource(sid, 1, &ptr, nullptr);
    glCompileShader(sid);

    int info, size;

    glGetShaderiv(sid, GL_COMPILE_STATUS, &info);
    glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &size);

    if (verbose && size > 0) {
      char msg[size];

      glGetShaderInfoLog(sid, size, nullptr, msg);


    }

    std::string shaderName = "#name " + file.filename().string() + '\n';
    std::string glslVersion = CONFIG_GET(std::string, "glsl-version") + '\n';

    stream.write(&shaderName[0], shaderName.size());
    stream.write(&glslVersion[0], glslVersion.size());
    stream.write(&shader[0], shader.size());
  }

  glDeleteProgram(pid);

  stream.close();

  return true;
}
