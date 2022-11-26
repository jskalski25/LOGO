/** @file */

#ifndef PROCEDURES_H
#define PROCEDURES_H

/** Wrapper dla vectora procedur. */
class Procedures {
private:
  std::vector<std::pair<std::string, AbstractNode*>> vec; ///< wewnętrzny vector
public:
/** Constructor. */
  Procedures() {}
/** Copy Constructor. */
  Procedures(const Procedures& p)
    : vec(p.vec) {}
/** Dodaje nową procedure do vectora
@param name id procedury
@param node komórka definicji procedury */
  void add_proc(std::string name, AbstractNode* node) {
    vec.push_back({name, node});
  }

/** Zwraca procedure o podanej nazwie
@param name id procedury
@return komórka definicji procedury, lub nullptr jeżeli nie istnieje */
  AbstractNode* get_proc(std::string name) {
    for (auto& p : vec) {
      if (p.first == name) {
        return p.second;
      }
    }
    return nullptr;
  }

/** Wypisuje nazwy procedur do std::cout. */
  void read_names() {
    for (auto& p : vec) {
      std::cout << p.first << " ";
    }
    std::cout << "\n";
  }
};

#endif
