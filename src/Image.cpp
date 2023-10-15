#include "Image.h"
#include <iostream>
#include <vector>







Image::Image() {}

void Image::read(const string& in_name) {

    ifstream stream(in_name, ios_base::binary);

    if (!stream.is_open()) {
        cout << "file is not open :(" << endl;
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


void Image::multiply(const Image& top_layer, const Image& bottom_layer) {
    for (unsigned int i = 0; i < top_layer.pixels.size(); i++) {
        Pixel new_pixel; 

        new_pixel.blue = (char)((((float)top_layer.pixels.at(i).blue * (float)bottom_layer.pixels.at(i).blue)/255) + 0.5f);
        new_pixel.green = (char)((((float)top_layer.pixels.at(i).green * (float)bottom_layer.pixels.at(i).green) / 255) + 0.5f);
        new_pixel.red = (char)((((float)top_layer.pixels.at(i).red * (float)bottom_layer.pixels.at(i).red) / 255) + 0.5f);
        
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





