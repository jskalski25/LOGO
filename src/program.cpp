#include "program.h"

void forward(ICode* prog, double r) {
  prog->cmds.push_back({prog->ort, r});
}

void back(ICode* prog, double r) {
  prog->cmds.push_back({prog->ort, -r});
}

void left(ICode* prog, double r) {
  prog->ort += r * M_PI / 180;
}

void right(ICode* prog, double r) {
  prog->ort -= r * M_PI / 180;
}

bool load_file(const std::string& fname, ICode& prog) {
  std::ifstream file(fname);
  if (!file) {
    std::cerr << "Failed to open input file.\n";
    return false;
  }
  Interpreter interpreter;
  interpreter.interpret(&file, &prog);
  file.close();
  return true;
}

bool save_to_file(const std::string& fname, const ICode& prog, int size) {
  BMP bmp = make_bmp(size, size);
  Color white = {255, 255, 255};
  double x0, y0, x1, y1;
  x0 = size / 2;
  y0 = size / 2;
  for (auto cmd : prog.cmds) {
    line_end(x0, y0, cmd.first, cmd.second, x1, y1);
    bresenhams_line(bmp, x0, y0, x1, y1, white);
    x0 = x1;
    y0 = y1;
  }
  save_bmp(bmp, fname);
  return true;
}
