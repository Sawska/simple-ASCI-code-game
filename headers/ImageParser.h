#ifndef IMAGE_PARSER_H
#define IMAGE_PARSER_H

#include "libs/stb/stb_image.h"
#include <string>
#include <iostream>

const std::string ASCII_CHARS = ".:=+*#%@";

class ImageParser {
public:
    void render_ascii(std::string& path);
private:
    int width;
    int heigh;
    int channels;
    unsigned char* gray_img;
    unsigned char* img;
    int scale_factor = 4;
    void load_image(std::string& path);
    void make_image_gray();
    void render_raw_ascii(int gray_channels);
};

#endif //IMAGE_PARSER_H