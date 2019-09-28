#ifndef VEGA_ENTRYPOINT_HPP
#define VEGA_ENTRYPOINT_HPP

int main(int argc, char **argv) {
  auto app = Vega::Make();

  app->Run();

  delete app;
}

#endif