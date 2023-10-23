#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "Check.h"
using namespace std;





int main(int argc, char** argv) {
    int check_num = 0;
       
    int check = checkArgs(argc, argv);

    if (check == 1) {
        return 1;
    }

    Image tracking_image;
    tracking_image.read(argv[2], check_num);


    tracking_image.write(argv[1]);


    return 0;

}

