#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

extern vega::Application *Make();

int main(int argc, char **argv) {
  vega::Application *application = vega::Make();

  application->Run();

  delete application;
}

#endif