#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

  
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



class Image {

public:


    Header header;
    vector<Pixel> pixels;


    Image();
    void read(const string& in_name, int& check_num);
    void write(const string& out_name); 
    void multiply( const Image& bottom_layer);
    void subtract(const Image& bottom_layer);
    void screen(const Image& bottom_layer);
    void overlay(const Image& bottom_layer);
    void addRed(int& add_num);
    void addBlue(int& add_num);
    void addGreen(int& add_num);
    void scaleRed(int& scale_num);
    void scaleGreen(int& scale_num);
    void scaleBlue(int& scale_num);
    void onlyRed();
    void onlyGreen();
    void onlyBlue();
    void combChannel(const Image& blue_channel, const Image& green_channel);
    void flipImage();


};






