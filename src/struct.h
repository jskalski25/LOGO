/** @file */

/** Przeparsowana lista argumentów z którą program został wywołany. */
struct Args {
  std::string in,       ///< ścieżka pliku wejścia
              out;      ///< ścieżka pliku wyjścia
  int32_t size;         ///< rozmiar bitmapy w pixelach
};

/** Turtle's path. */
struct ICode {
  CmdVec cmds;        ///< ścieżka źółwia jako vector nachyleń i odległości
  double ort{M_PI/2}; ///< ostatnie nachylenie żółwia
};

/** BMP File Header. */
struct BMPFileHeader {
  uint16_t file_type{0x4d42};
  uint32_t file_size{0};
  uint16_t reserved1{0};
  uint16_t reserved2{0};
  uint32_t data_offset{0};
};

/** BMP Info Header. */
struct BMPInfoHeader {
  uint32_t size{40};
  int32_t width{0};
  int32_t height{0};
  uint16_t planes{1};
  uint16_t bit_count{24};
  uint32_t compression{0};
  uint32_t image_size{0};
  int32_t x_pixels_per_meter{0};
  int32_t y_pixels_per_meter{0};
  uint32_t colors_used{0};
  uint32_t colors_important{0};
};

/** 24 bitowa reprezentacja koloru. */
struct Color {
  uint8_t red;    ///< czerwony
  uint8_t green;  ///< zielony
  uint8_t blue;   ///< niebieski
};

/** Reprezentacja bitmapy w strukturze. */
struct BMP {
  BMPFileHeader file_header;  ///< BMP file header
  BMPInfoHeader info_header;  ///< BMP info header
  std::vector<Color> data;    ///< vector pixeli
};
