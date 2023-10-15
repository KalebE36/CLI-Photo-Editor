#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;




class Image {

public:


    struct Header {

        char id_length;
        char color_mapType;
        char data_typeCode;
        short color_mapOrigin;
        short color_mapLength;
        char color_mapDepth;
        short x_origin;
        short y_origin;
        short width;
        short height;
        char bits_perPixel;
        char image_descriptor;
    };
   

    struct Pixel {

        unsigned char blue;
        unsigned char green;
        unsigned char red;

    };

    
    Header header;
    vector<Pixel> pixels;


    Image();
    void read(const string& in_name);
    void write(const string& out_name); 
    void multiply(const Image& top_layer, const Image& bottom_layer);

};






