#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "Check.h"
#include "Implement.h"
using namespace std;





int main(int argc, char** argv) {
       
    int check = checkArgs(argc, argv);

    if (check == 1) {
        return 1;
    }

    Image tracking_image;
    tracking_image.read(argv[2], check);
    if(check == 1) {
        return 1;
    }

    implementArgs(tracking_image, argc, argv, check);
    if(check == 1) {
        return 1;
    }
    tracking_image.write(argv[1]);


    return 0;

}

