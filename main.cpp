#include "headers/ImageParser.h"


int main() {
    ImageParser img_parse = ImageParser();

    std::string example = "example1.jpg";

    img_parse.render_ascii(example);
}