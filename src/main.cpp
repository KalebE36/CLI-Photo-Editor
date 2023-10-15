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
    
    image1.read("../input/layer1.tga");
    image2.read("../input/pattern1.tga");   
    out_image.header = image1.header;
    out_image.multiply(image1, image2);

    out_image.write("../output/Test1.tga");



}
