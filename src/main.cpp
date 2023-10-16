#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include "Image.h"
using namespace std;

int main() {

    Image image1;
    Image image2; 
 
    Image out_image;
    out_image.header = image1.header;


    out_image.write("../output/Test.tga");



}
