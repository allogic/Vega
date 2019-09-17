#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

int main(int argc, char **argv) {
  vega::Application *application = vega::make();

  application->run();

  delete application;
}

#endif