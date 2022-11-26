/** @file */

#include "common.h"

/** Tworzy pustą bitmapę.
@param width  szerokość bitmapy
@param height wysokość bitmapy
@return stworzoną bitmapę */
BMP make_bmp(int32_t width, int32_t height);

/** Zapisuje bitmapę do pliku.
@param bmp   referencja do bitmapy
@param fname nazwa pliku wyjściowego
@return fałsz w wypadku błędu */
bool save_bmp(const BMP& bmp, const std::string& fname);

/** Tworzy białą bitmapę.
@param width  szerokość bitmapy
@param height wysokość bitmapy
@return stworzoną bitmapę */
BMP plain_white_bmp(int32_t width, int32_t height);
