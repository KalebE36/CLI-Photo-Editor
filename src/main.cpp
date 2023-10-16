#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include "Image.h"
using namespace std;

int main() {

    Image image1;
    Image out_image; 

    image1.read("../input/text2.tga");

    out_image.header = image1.header;
    out_image.flipImage(image1);


    out_image.write("../output/Test.tga");



}
