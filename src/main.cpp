#include "main.h"

int main(int argc, char** argv) {
  Args a{};
  ICode prog{};
  if (!parse_args(args_to_vector(argc, argv), a)) {
    std::cerr << "Invalid arguments.\n";
    std::cerr << "Usage: logo -i <input> -o <output> -s <size>\n";
    return 1;
  }
  if (!load_file(a.in, prog)) {
    std::cerr << "Error loading file.\n";
    return 1;
  }
  if (!save_to_file(a.out, prog, a.size)) {
    std::cerr << "Error saving to file.\n";
    return 1;
  }
  return 0;
}
