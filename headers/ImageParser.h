#ifndef IMAGE_PARSER_H
#define IMAGE_PARSER_H

#include "../libs/stb/stb_image.h"
#include <string>
#include <iostream>

const std::string ASCII_CHARS = ".:=+*#%@";

class ImageParser {
public:
    void load_image(const std::string& path);
    void render_ascii();
    ImageParser();
    ~ImageParser();
private:
    int width;
    int heigh;
    int channels;
    unsigned char* gray_img;
    unsigned char* img;
    int scale_factor = 4;
    void make_image_gray();
};

#endif //IMAGE_PARSER_H