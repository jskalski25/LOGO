#include "args.h"

std::vector<std::string> args_to_vector(int argc, char** argv) {
  std::vector<std::string> v;
  for (int i = 1; i < argc; ++i) {
    v.push_back(argv[i]);
  }
  return v;
}

bool parse_args(const std::vector<std::string>& v, Args& a) {
  for (unsigned i = 1; i < v.size(); ++i) {
    if (v[i-1] == "-i") {
      a.in = v[i++];
    }
    else if (v[i-1] == "-o") {
      a.out = v[i++];
    }
    else if (v[i-1] == "-s") {
      try {
        a.size = std::stoi(v[i++]);
      }
      catch (const std::invalid_argument&) {
        std::cerr << "Error: Size must be an integer.\n";
        return false;
      }
    }
  }
  return !a.in.empty() && !a.out.empty() && a.size != 0;
}
