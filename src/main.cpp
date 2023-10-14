#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "Image.cpp"
using namespace std;

int main() {
    Image image;
    image.read("../input/car.tga");
    image.write("../output/out.tga");
}
