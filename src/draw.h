/** @file */

#include "common.h"

/** Ustawia pixel na wybrany kolor.
@param bmp referencja do bitmapy
@param x   współrzędna x
@param y   współrzędna y
@param c   nowy kolor pixela */
void paint_pixel(BMP& bmp, int x, int y, Color c);

/** Rysuje linie o podanym początku, kącie nachylenia i długości.
@param bmp referencja do bitmapy
@param x   współrzędna x początku linii
@param y   współrzędna y początku linii
@param d   kąt nachylenia linii w radianach
@param l   długość linii w pixelach
@param c   kolor linii */
void paint_line(BMP& bmp, double x, double y, double d, double l, Color c);

/** Rysuje linie o podanym początku i końcu używając algorytmu bresenhama.
@param bmp referencja do bitmapy
@param x0  współrzędna x początku linii
@param y0  współrzędna y początku linii
@param x1  współrzędna x końca linii
@param y2  współrzędna y końca linii
@param c   kolor linii */
void bresenhams_line(BMP& bmp, double x0, double y0,
  double x1, double y1, Color c);

/** Określa współrzędne końca linii.
@param x0 współrzędna x początku linii
@param y0 współrzędna y początku linii
@param d  kąt nachylenia linii w radianach
@param l  długość linii w pixelach
@param x1 referencja do współrzędnej x końca linii
@param y2 referencja do współrzędnej y końca linii */
void line_end(double x0, double y0, double d, double l,
  double& x1, double& y1);
