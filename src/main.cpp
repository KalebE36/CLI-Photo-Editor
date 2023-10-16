#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include "Image.h"
using namespace std;

int main() {

    Image image1;
    Image out_image; 

    image1.read("../input/car.tga");

    out_image.header = image1.header;
    out_image.scale(image1, 0, 1, 4);



    out_image.write("../output/Test.tga");



}
