#include "draw.h"

void paint_pixel(BMP& bmp, int x, int y, Color c) {
  if (x >= 0 && x < bmp.info_header.width &&
      y >= 0 && y < bmp.info_header.height) {
    bmp.data[x+y*bmp.info_header.width] = c;
  }
}

void paint_line(BMP& bmp, double x, double y, double d, double l, Color c) {
  double x0, y0;
  line_end(x, y, d, l, x0, y0);
  bresenhams_line(bmp, x, y, x0, y0, c);
}

void line_end(double x0, double y0, double d, double l,
  double& x1, double& y1) {
  x1 = x0 + std::cos(d) * l;
  y1 = y0 + std::sin(d) * l;
}

void bresenhams_line(BMP& bmp, double x0, double y0,
  double x1, double y1, Color c) {
  double d, dx, dy, ai, bi;
  int xi, yi;
  int x = std::nearbyint(x0), y = std::nearbyint(y0);

  if (x0 < x1) {
    xi = 1;
    dx = x1 - x0;
  }
  else {
    xi = -1;
    dx = x0 - x1;
  }

  if (y0 < y1) {
    yi = 1;
    dy = y1 - y0;
  }
  else {
    yi = -1;
    dy = y0 - y1;
  }

  paint_pixel(bmp, x, y, c);

  if (dx > dy) {
    ai = (dy - dx) * 2;
    bi = dy * 2;
    d = bi - dx;
    while (x != (int)std::nearbyint(x1)) {
      if (d >= 0) {
        x += xi;
        y += yi;
        d += ai;
      }
      else {
        d += bi;
        x += xi;
      }
      paint_pixel(bmp, x, y, c);
    }
  }
  else {
    ai = (dx - dy) * 2;
    bi = dx * 2;
    d = bi - dy;
    while (y != (int)std::nearbyint(y1)) {
      if (d >= 0) {
        x += xi;
        y += yi;
        d += ai;
      }
      else {
        d += bi;
        y += yi;
      }
      paint_pixel(bmp, x, y, c);
    }
  }
}
