#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "headers/ImageParser.h"

ImageParser::ImageParser() {
    img = nullptr;
    gray_img = nullptr;
    width = 0;
    heigh = 0;
    channels = 0;
    scale_factor = 4; 
}

ImageParser::~ImageParser() {
    if (gray_img != nullptr) {
        delete[] gray_img;
    }
        gray_img = nullptr;
}

void ImageParser::load_image(const std::string& path)
{
    if (gray_img != nullptr) {
        delete[] gray_img;
        gray_img = nullptr;
    }

    img = stbi_load(path.c_str(), &width, &heigh, &channels, 0);

    if(img == NULL) {
        std::cout << "Error: Could not load image at " << path << std::endl;
        return;
    }

    make_image_gray();
    
    stbi_image_free(img);
    img = nullptr; 
}

void ImageParser::make_image_gray()
{
    size_t img_size = width * heigh * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * heigh * gray_channels;

    gray_img = new unsigned char[gray_img_size];

    if(gray_img == NULL) {
        std::cout << "Memory allocation failed." << std::endl;
        return;
    }

    for(unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels) {
        *pg = (uint8_t)((*p + *(p+1) + *(p+2)) / 3.0);
        
        if(channels == 4) {
            *(pg+1) = *(p+3);
        }
    }
}

void ImageParser::render_ascii()
{
    if (gray_img == nullptr) return;

    int gray_channels = (channels == 4) ? 2 : 1;
    int step_x = scale_factor;
    int step_y = scale_factor * 2; 

    std::string buffer = "";

    for(int y = 0; y < heigh; y += step_y) {
        for(int x = 0; x < width; x += step_x) {
            
            int index = (y * width + x) * gray_channels;

            // Transparency Check
            if(gray_channels == 2) {
               unsigned char alpha = gray_img[index + 1];
                if (alpha < 50) { 
                    buffer += " "; 
                    continue; 
                }
            }

            
            unsigned char brightness = gray_img[index];
            int char_index = (brightness * (ASCII_CHARS.length() - 1)) / 255;
            
            buffer += ASCII_CHARS[char_index];
        }
        buffer += "\n";
    }
    
    std::cout << buffer;
}