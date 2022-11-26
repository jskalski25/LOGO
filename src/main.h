#include "common.h"

// args.h
extern std::vector<std::string> args_to_vector(int, char**);
extern bool parse_args(const std::vector<std::string>&, Args&);

// bitmap.h
extern BMP make_bmp(int32_t, int32_t);
extern BMP plain_white_bmp(int32_t width, int32_t height);
extern bool save_bmp(const BMP&, const std::string&);

// draw.h
extern void paint_pixel(BMP&, int, int, Color);
extern void paint_line(BMP&, double, double, double, double, Color);
extern void bresenhams_line(BMP&, double, double, double, double, Color);
extern void line_end(double, double, double, double, double&, double&);

// program.h
extern bool load_file(const std::string&, ICode&);
extern bool save_to_file(const std::string&, const ICode&, int);
