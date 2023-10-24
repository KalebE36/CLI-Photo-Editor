#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "Check.h"
using namespace std;





int main(int argc, char** argv) {
       
    int check = checkArgs(argc, argv);

    if (check == 1) {
        return 1;
    }
    /*
    implementArgs(argc, argv);
    */

    return 0;

}

