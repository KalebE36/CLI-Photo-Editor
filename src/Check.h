#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include "Image.h"



int checkOneArg(int& index, int& argc, char**& argv) {
    if (argc <= (index+1)) {
        cout << "Missing argument." << endl;
        return 1;
    }
    int test_num = 0;
    Image test_image;
    test_image.read(argv[index+1], test_num);
    return test_num;

}





int checkArgs(int& argc, char**&argv) {
    if ((argc == 1) || (strcmp(argv[1], "--help") == 0)) {
        cout << "Project 2: Image Processing, Fall 2023" << endl << endl;
        cout << "Usage" << endl;
        cout << "\t ./project2.out [output] [firstimage] [method] [...]" << endl << endl;

        return 1;

    }

    if ((strcmp(argv[1], "output/output.tga") != 0) || (argc <= 2)) {
        cout << "Invalid file name." << endl;

        return 1;
    }

    if (argc >= 3) {
        Image test_image;
        string test_string = (string)argv[2];


        if (test_string.find(".tga") == -1) {
            cout << "Invalid file name." << endl;
            return 1;
        }
        int check_num = 0;
        test_image.read(test_string, check_num);
        if(check_num == 1){
            return 1;
        }
    }

    if(argc <= 4) {
        cout << "Invalid method name." << endl;

        return 1;
    }

    if(argc >= 4) {
        for(int i = 3; i == argc; i++) {
            if (strcmp(argv[i], "multiply") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;
                } else {
                    i = i + 2;
                }
            } else if (strcmp(argv[i], "subtract") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;

                } else {
                    i = i + 2;
                }
            } else if (strcmp(argv[i], "overlay") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;

                } else {
                    i = i + 2;
                }
            } else if (strcmp(argv[i], "screen") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;

                } else {
                    i = i + 2;
                }
            }

        }
    }


    return 0;
}


