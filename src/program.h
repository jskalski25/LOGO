/** @file */

#include "common.h"
#include "interpreter.h"

/** Rusza żółwia naprzód, dodaje ścieżke do struktury.
@param prog referencja do ścieżki żółwia
@param r    odległość ruchu żółwia */
void forward(ICode* prog, double r);

/** Rusza żółwia do tyłu, dodaje ścieżke do struktury.
@param prog referencja do ścieżki żółwia
@param r    odległość ruchu żółwia */
void back(ICode* prog, double r);

/** Obraca żółwia w lewo, zmienia parametr nachylenia w strukturze.
@param prog referencja do ścieżki żółwia
@param r    kąt obrotu żółwia w stopniach */
void left(ICode* prog, double r);

/** Obraca żółwia w prawo, zmienia parametr nachylenia w strukturze.
@param prog referencja do ścieżki żółwia
@param r    kąt obrotu żółwia w stopniach */
void right(ICode* prog, double r);

/** Pobiera dane z pliku wejściowego i plotuje trasę żółwia.
@param fname nazwa pliku wejścia
@param prog  referencja do ścieżki żółwia
@return false w wypadku błędu */
bool load_file(const std::string& fname, ICode& prog);

/** Zapisuje gotową ścieżke żółwia do pliku.
@param fname nazwa pliku wyjścia
@param prog  referencja do ścieżki żółwia
@param size  rozmiar wyjściowego obrazu w pixelach
@return false w przypadku błędu */
bool save_to_file(const std::string& fname, const ICode& prog, int size);

// bitmap.h
extern BMP make_bmp(int32_t, int32_t);
extern bool save_bmp(const BMP&, const std::string&);

// draw.h
extern void bresenhams_line(BMP&, double, double, double, double, Color);
extern void line_end(double, double, double, double, double&, double&);
