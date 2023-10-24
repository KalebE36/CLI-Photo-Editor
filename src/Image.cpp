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
        cout << "File does not exist." << endl;
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

void Image::add(const Image& image, int b, int g, int r) {
    for(int i = 0; i < image.pixels.size(); i++) {
        int b1 = b;
        int g1 = g;
        int r1 = r;
        Pixel new_pixel; 

        b1 = (int)image.pixels.at(i).blue + b1; 
        g1 = (int)image.pixels.at(i).green + g1;
        r1 = (int)image.pixels.at(i).red + r1; 

        Clamp(b1, g1, r1); 

        new_pixel.blue = b1; 
        new_pixel.green = g1; 
        new_pixel.red = r1; 

        pixels.push_back(new_pixel);
    } 
}

void Image::scale(const Image& image, int b, int g, int r) {
    for(int i = 0; i < image.pixels.size(); i++) {
        Pixel new_pixel; 
        int b1 = b;
        int g1 = g;
        int r1 = r;

        b1 = (int)image.pixels.at(i).blue * b1;
        g1 = (int)image.pixels.at(i).green * g1; 
        r1 = (int)image.pixels.at(i).red * r1; 

        Clamp(b1, g1, r1); 

        new_pixel.blue = b1; 
        new_pixel.green = g1; 
        new_pixel.red = r1; 

        pixels.push_back(new_pixel); 
        
    } 
}

void Image::separateChannel(const Image& image, int b, int g, int r){
    pixels.clear(); 
    if (b == 1) {
        for(int i = 0; i < image.pixels.size(); i++) {
            Pixel new_pixel; 

            new_pixel.blue = image.pixels.at(i).blue; 
            new_pixel.green = image.pixels.at(i).blue; 
            new_pixel.red = image.pixels.at(i).blue; 

            pixels.push_back(new_pixel);

        }  
    }

    if (g == 1){
        for(int i = 0; i < image.pixels.size(); i++) {
            Pixel new_pixel; 

            new_pixel.blue = image.pixels.at(i).green; 
            new_pixel.green = image.pixels.at(i).green; 
            new_pixel.red = image.pixels.at(i).green; 

            pixels.push_back(new_pixel);

        }  
    }

    if (r == 1){
        for(int i = 0; i < image.pixels.size(); i++) {
            Pixel new_pixel; 

            new_pixel.blue = image.pixels.at(i).red; 
            new_pixel.green = image.pixels.at(i).red; 
            new_pixel.red = image.pixels.at(i).red; 

            pixels.push_back(new_pixel);

        }  
    }

}

void Image::combChannel(const Image& blue_channel, const Image& green_channel) {
    for (int i = 0; i < pixels.size(); i++) {

        pixels.at(i).blue = blue_channel.pixels.at(i).blue;
        pixels.at(i).green = green_channel.pixels.at(i).green;
        
    }
}

void Image::flipImage(const Image& image1) {
    for (int i = image1.pixels.size()-1; i >= 0; i--) {
        Pixel new_pixel; 

        new_pixel.blue = image1.pixels.at(i).blue;
        new_pixel.green = image1.pixels.at(i).green;
        new_pixel.red = image1.pixels.at(i).red;



        pixels.push_back(new_pixel); 


    }


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





