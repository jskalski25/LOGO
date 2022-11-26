/** @file */

#include "common.h"

/** Zamienia listę argumentów programu na vector stringów.
@param argc ilość argumentów
@param argv wartości argumentów
@return argumenty programu w postaci vectora */
std::vector<std::string> args_to_vector(int argc, char** argv);

/** Zamienia vector argumentów programu na strukturę.
@param v referencja vectora argumentów
@param a referencja docelowej struktury
@return false w wypadku błędu */
bool parse_args(const std::vector<std::string>& v, Args& a);
