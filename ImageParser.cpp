#define STB_IMAGE_IMPLEMENTATION
#include "headers/ImageParser.h"

void ImageParser::render_ascii(std::string& path)
{
    load_image(path);
}

void ImageParser::load_image(std::string& path)
{
    img = stbi_load(path.c_str(),&width,&heigh,&channels,0);

    if(img == NULL) {
        std::cout << "Error in loading the image" << std::endl;
    }

    make_image_gray();


}

void ImageParser::make_image_gray()
{
    size_t img_size = width*heigh*channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width*heigh*gray_channels;

    gray_img =  new unsigned char[gray_img_size];



    if(gray_img == NULL) {
        std::cout << "Unable to allocate memory for the gray image." << std::endl;
    }

    for(unsigned char *p = img,*pg = gray_img;p!= img+img_size;p+=channels,pg+=gray_channels ) {
        *pg = (uint8_t)((*p+*(p+1)+*(p+2))/3.0);
        if(channels == 4) {
            *(pg+1) = *(p+3);
        }
    }
    stbi_image_free(img);
    render_raw_ascii(gray_channels);
}

void ImageParser::render_raw_ascii(int gray_channels)
{

    int step_x = scale_factor;
    int step_y = scale_factor * 2;


    for(int y=0;y<heigh;y+=step_y) {
        for(int x =0;x<width;x+=step_x) {
            int index = (y*width+x) * gray_channels;

            if(gray_channels == 2) {
               unsigned char alpha = gray_img[index + 1];
                if (alpha < 50) { 
                    std::cout << " "; 
                    continue; 
                }
            }
            unsigned char brightness = gray_img[index];
            int char_index = (brightness * (ASCII_CHARS.length() - 1)) / 255;
            std::cout << ASCII_CHARS[char_index];
        }
        std::cout << "\n";
    }
}

