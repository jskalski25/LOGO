#include "bitmap.h"

BMP make_bmp(int32_t width, int32_t height) {
  BMP bmp;

  int32_t padded_width = width*3 + ((width) % 4);

  bmp.file_header.file_size = 14 + 40 + padded_width*height*3;
  bmp.file_header.data_offset = 14 + 40;

  bmp.info_header.width = width;
  bmp.info_header.height = height;
  bmp.info_header.image_size = padded_width*height*3;

  bmp.data.resize(width*height);

  return bmp;
}

bool save_bmp(const BMP& bmp, const std::string& fname) {
  std::ofstream out(fname, std::ios_base::binary);
  if (!out) {
    std::cerr << "Failed to save file to disk.\n";
    return false;
  }
  out.write((char*)(&bmp.file_header.file_type), 2);
  out.write((char*)(&bmp.file_header.file_size), 12);
  out.write((char*)(&bmp.info_header), 40);
  for (unsigned i = 0; i < bmp.data.size(); ++i) {
    out.write((char*)(&bmp.data[i]), 3);
    if (!((i+1) % bmp.info_header.width)) {
      char nil = 0;
      for (int j = 0; j < ((bmp.info_header.width) % 4); ++j) {
        out.write(&nil, 1);
      }
    }
  }
  out.close();
  return true;
}

BMP plain_white_bmp(int32_t width, int32_t height) {
  BMP bmp = make_bmp(width, height);
  for (auto& pixel : bmp.data) {
    pixel.red = 255;
    pixel.green = 255;
    pixel.blue = 255;
  }
  return bmp;
}
