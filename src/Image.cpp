#include "Image.h"
#include <iostream>
#include <vector>




void Clamp(int& b, int& g, int& r) {
    if(b > 255) {
            b = 255;
        } else if (b < 0){
            b = 0; 
        }

        if(g > 255) {
            g = 255;
        } else if (g < 0){
            g = 0; 
        }

        if(r > 255) {
            r = 255;
        } else if (r < 0){
            r = 0; 
        }
}


Image::Image() {}

void Image::read(const string& in_name, int& check_num) {

    ifstream stream(in_name, ios_base::binary);
    if (!stream.is_open()) {
        check_num = 1;
    }


    stream.read(&header.id_length, sizeof(header.id_length));
    stream.read(&header.color_mapType, sizeof(header.color_mapType));
    stream.read(&header.data_typeCode, sizeof(header.data_typeCode));
    stream.read((char*)&header.color_mapOrigin, sizeof(header.color_mapOrigin));
    stream.read((char*)&header.color_mapLength, sizeof(header.color_mapLength));
    stream.read(&header.color_mapDepth, sizeof(header.color_mapDepth));
    stream.read((char*)&header.x_origin, sizeof(header.x_origin));
    stream.read((char*)&header.y_origin, sizeof(header.y_origin));
    stream.read((char*)&header.width, sizeof(header.width));
    stream.read((char*)&header.height, sizeof(header.height));
    stream.read(&header.bits_perPixel, sizeof(header.bits_perPixel));
    stream.read(&header.image_descriptor, sizeof(header.image_descriptor));
    

    int imageSize = (int)(header.width * header.height);

    for (int i = 0; i < imageSize; i++) {
        Pixel pixel;

        stream.read((char*)& pixel.blue, sizeof(pixel.blue));
        stream.read((char*)& pixel.green, sizeof(pixel.green));
        stream.read((char*)& pixel.red, sizeof(pixel.red));

        pixels.push_back(pixel);
    }
  

  
}


void Image::multiply(const Image& bottom_layer) {
    for (int i = 0; i < pixels.size(); i++) {

        pixels.at(i).blue = (char)((((float)pixels.at(i).blue * (float)bottom_layer.pixels.at(i).blue)/255) + 0.5f);
        pixels.at(i).green = (char)((((float)pixels.at(i).green * (float)bottom_layer.pixels.at(i).green) / 255) + 0.5f);
        pixels.at(i).red = (char)((((float)pixels.at(i).red * (float)bottom_layer.pixels.at(i).red) / 255) + 0.5f);

    }

}

void Image::subtract(const Image& bottom_layer){

    int blue, green, red;
    for(int i = 0; i < pixels.size(); i++){

        blue = (int)pixels.at(i).blue - (int)bottom_layer.pixels.at(i).blue;
        green = (int)pixels.at(i).green - (int)bottom_layer.pixels.at(i).green;
        red = (int)pixels.at(i).red - (int)bottom_layer.pixels.at(i).red;

        Clamp(blue, green, red); 

        pixels.at(i).blue = (char)blue;
        pixels.at(i).green = (char)green;
        pixels.at(i).red = (char)red;

    }
}


void Image::screen(const Image& bottom_layer) {

    for (unsigned int i = 0; i < pixels.size(); i++) {
        
        pixels.at(i).blue = (char)(((1 - ((1 - pixels.at(i).blue / 255.0)*(1 - bottom_layer.pixels.at(i).blue / 255.0)))*255.0) + 0.5f);
        pixels.at(i).green = (char)(((1 - ((1 - pixels.at(i).green / 255.0)*(1 - bottom_layer.pixels.at(i).green / 255.0)))*255.0) + 0.5f);
        pixels.at(i).red = (char)(((1 - ((1 - pixels.at(i).red / 255.0)*(1 - bottom_layer.pixels.at(i).red / 255.0)))*255.0) + 0.5f);

        
    } 

}


void Image::overlay(const Image& bottom_layer) {

    for(int i = 0; i <  pixels.size(); i++) {


        if((((float)bottom_layer.pixels.at(i).blue )/ 255) > 0.5) {
            pixels.at(i).blue = (((1 - (2 * (1 - pixels.at(i).blue / 255.0) * (1 - bottom_layer.pixels.at(i).blue / 255.0))) * 255.0) + 0.5f);
        } else  {
            pixels.at(i).blue = (int)(((2 * (pixels.at(i).blue / 255.0) * (bottom_layer.pixels.at(i).blue / 255.0)) * 255.0) + 0.5f);
        }

        if((((float)bottom_layer.pixels.at(i).green ) / 255) > 0.5) {
            pixels.at(i).green = (int)(((1 - (2 * (1 - pixels.at(i).green / 255.0) * (1 - bottom_layer.pixels.at(i).green / 255.0))) * 255.0) + 0.5f);

        } else {
            pixels.at(i).green = (int)(((2 * (pixels.at(i).green / 255.0) * (bottom_layer.pixels.at(i).green / 255.0)) * 255.0) + 0.5f);
        }

        if((((float)bottom_layer.pixels.at(i).red) / 255) > 0.5) {
            pixels.at(i).red = (int)(((1 - (2 * (1 - pixels.at(i).red / 255.0) * (1 - bottom_layer.pixels.at(i).red / 255.0))) * 255.0) + 0.5f);

        } else {
            pixels.at(i).red = (int)(((2 * (pixels.at(i).red / 255.0) * (bottom_layer.pixels.at(i).red / 255.0)) * 255.0) + 0.5f);

        }

    }
}


void Image::addRed(int& add_num) {
    for(int i = 0; i < pixels.size(); i++) {
        int b1 = 1;
        int g1 = 1;
        int r1 = add_num;

        r1 = (int)pixels.at(i).red + r1;
        Clamp(b1, g1, r1);

        pixels.at(i).red = r1;

    }
}

void Image::addBlue(int& add_num) {
    for(int i = 0; i < pixels.size(); i++) {
        int b1 = add_num;
        int g1 = 1;
        int r1 = 1;

        b1 = (int)pixels.at(i).blue + b1;
        Clamp(b1, g1, r1);

        pixels.at(i).blue = b1;

    }
}

void Image::addGreen(int& add_num) {
    for(int i = 0; i < pixels.size(); i++) {
        int b1 = 1;
        int g1 = add_num;
        int r1 = 1;

        g1 = (int)pixels.at(i).green + g1;
        Clamp(b1, g1, r1);

        pixels.at(i).green = g1;

    }
}


void Image::scaleRed(int& scale_num) {
    for(int i = 0; i < pixels.size(); i++) {
        int b1 = 1;
        int g1 = 1;
        int r1 = scale_num;


        r1 = (int)pixels.at(i).red * r1;
        Clamp(b1, g1, r1);

        pixels.at(i).red = r1;

    }
}

void Image::scaleGreen(int& scale_num) {
    for(int i = 0; i < pixels.size(); i++) {
        int b1 = 1;
        int g1 = scale_num;
        int r1 = 1;

        g1 = (int)pixels.at(i).green * g1;
        Clamp(b1, g1, r1);

        pixels.at(i).green = g1;

    }
}

void Image::scaleBlue(int& scale_num) {
    for(int i = 0; i < pixels.size(); i++) {
        int b1 = scale_num;
        int g1 = 1;
        int r1 = 1;

        b1 = (int)pixels.at(i).blue * b1;
        Clamp(b1, g1, r1);

        pixels.at(i).blue = b1;

    }
}





void Image::onlyRed() {
    for(int i = 0; i < pixels.size(); i++) {

        pixels.at(i).blue = pixels.at(i).red;
        pixels.at(i).green = pixels.at(i).red;


    }
}

void Image::onlyGreen() {
    for(int i = 0; i < pixels.size(); i++) {

        pixels.at(i).blue = pixels.at(i).green;
        pixels.at(i).red = pixels.at(i).green;


    }
}

void Image::onlyBlue() {
    for(int i = 0; i < pixels.size(); i++) {

        pixels.at(i).red = pixels.at(i).blue;
        pixels.at(i).green = pixels.at(i).blue;


    }
}

void Image::combChannel(const Image& blue_channel, const Image& green_channel) {
    for (int i = 0; i < pixels.size(); i++) {

        pixels.at(i).blue = blue_channel.pixels.at(i).blue;
        pixels.at(i).green = green_channel.pixels.at(i).green;
        
    }
}

void Image::flipImage() {
    Image temp_image;
    temp_image.header = header;
    for (int i = pixels.size()-1; i >= 0; i--) {
        Pixel new_pixel;
        new_pixel.blue = pixels.at(i).blue;
        new_pixel.green = pixels.at(i).green;
        new_pixel.red = pixels.at(i).red;

        temp_image.pixels.push_back(new_pixel);

    }
    pixels.clear();
    pixels = temp_image.pixels;


}






void Image::write(const string& out_name) {
    ofstream stream(out_name, ios_base::binary);

    stream.write(&header.id_length, sizeof(header.id_length));
    stream.write(&header.color_mapType, sizeof(header.color_mapType));
    stream.write(&header.data_typeCode,sizeof(header.data_typeCode));
    stream.write((char*)&header.color_mapOrigin,sizeof(header.color_mapOrigin));
    stream.write((char*)&header.color_mapLength,sizeof(header.color_mapLength));
    stream.write(&header.color_mapDepth, sizeof(header.color_mapDepth));
    stream.write((char*)&header.x_origin, sizeof(header.x_origin));
    stream.write((char*)&header.y_origin, sizeof(header.y_origin));
    stream.write((char*)&header.width, sizeof(header.width));
    stream.write((char*)&header.height, sizeof(header.height));
    stream.write(&header.bits_perPixel, sizeof(header.bits_perPixel) );
    stream.write(&header.image_descriptor, sizeof(header.image_descriptor));

    for (int i = 0; i < pixels.size(); i++) {
        Pixel pixel = pixels[i];

        stream.write((char*)& pixel.blue, sizeof(pixel.blue));
        stream.write((char*)& pixel.green, sizeof(pixel.green));
        stream.write((char*)& pixel.red, sizeof(pixel.red));
    }
        


}





