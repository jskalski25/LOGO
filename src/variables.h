/** @file */

#ifndef VARIABLES_H
#define VARIABLES_H

using InputValues = std::vector<double>;
using VarNames = std::vector<std::string>;

/** Wrapper dla vectora zmiennych. */
class Variables {
private:
  std::vector<std::pair<std::string, double>> vec; ///< wewnętrzny vector
public:
/** Powiązuje vectory nazw i wartości argumentów.
@param vars vector wartości
@param names vector nazw */
  Variables(InputValues* vars, VarNames* names) {
    for (size_t i = 0; i < names->size(); ++i) {
      vec.push_back({names->at(i), vars->at(i)});
    }
  }
/** Zwraca wartość zmiennej.
@param n id zmiennej
@return wartość zmiennej */
  double get(std::string n) {
    for (auto& p : vec) {
      if (p.first == n) {
        return p.second;
      }
    }
    return 0;
  }
/** Wypisuje nazwy i wartości zmiennych do std::cout. */
  void read_vars() {
    for (auto& p : vec) {
      std::cout << p.first << "=" << p.second << " ";
    }
    std::cout << "\n";
  }
};

#endif
