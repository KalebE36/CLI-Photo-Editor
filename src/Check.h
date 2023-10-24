#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include "Image.h"


int checkInt(int& index, int& argc, char**& argv) {
    if (argc <= (index+1)) {
        cout << "Missing argument." << endl;
        return 1;
    }
    string test_string = (string)argv[index+1];
    try {
        int num = stoi(test_string);
    } catch(...) {
        cout << "Invalid integer" << endl;
        return 1;
    }

    return 0;
}






int checkCombine(int& index, int& argc, char**& argv) {
    if (argc <= (index+2)) {
        cout << "Missing argument." << endl;
        return 1;
    }

    if((strcmp(argv[index + 1], "input") == 0) || (strcmp(argv[index + 1], "output") == 0) || (strcmp(argv[index + 1], "src") == 0) || (strcmp(argv[index + 1], "input/") == 0) || (strcmp(argv[index + 1], "output/") == 0) || (strcmp(argv[index + 1], "src/") == 0)){
        cout << "Invalid file name" << endl;
        return 1;
    }

    if((strcmp(argv[index + 2], "input") == 0) || (strcmp(argv[index + 2], "output") == 0) || (strcmp(argv[index + 2], "src") == 0) || (strcmp(argv[index + 2], "input/") == 0) || (strcmp(argv[index + 2], "output/") == 0) || (strcmp(argv[index + 2], "src/") == 0)){
        cout << "Invalid file name" << endl;
        return 1;
    }
    int check_num = 0;
    Image test_image1;
    Image test_image2;

    test_image1.read(argv[index+1], check_num);
    if (check_num == 1){
        return 1;
    }

    test_image2.read(argv[index+2], check_num);
    return check_num;

}


int checkOneArg(int& index, int& argc, char**& argv) {
    if (argc <= (index+1)) {
        cout << "Missing argument." << endl;
        return 1;
    }

    if((strcmp(argv[index + 1], "input") == 0) || (strcmp(argv[index + 1], "output") == 0) || (strcmp(argv[index + 1], "src") == 0) || (strcmp(argv[index + 1], "input/") == 0) || (strcmp(argv[index + 1], "output/") == 0) || (strcmp(argv[index + 1], "src/") == 0)){
        cout << "Invalid file name" << endl;
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

    if(argc < 4) {
        cout << "Invalid method name." << endl;

        return 1;
    }

    if(argc >= 4) {
        for(int i = 3; i < argc; i++) {
            //cout << argv[i] << endl;
            if (strcmp(argv[i], "multiply") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;
                } else {
                    i++;
                }
            } else if (strcmp(argv[i], "subtract") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;
                } else {
                    i++;
                }
            } else if (strcmp(argv[i], "overlay") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;

                } else {
                    i++;
                }
            } else if (strcmp(argv[i], "screen") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;

                } else {
                    i++;
                }
            } else if (strcmp(argv[i], "combine") == 0) {
                int num = checkCombine(i, argc, argv);
                if (num == 1) {
                    return 1;
                } else {
                    i++;
                    i++;
                }

            } else if (strcmp(argv[i], "flip") == 0) {

            } else if((strcmp(argv[i], "onlyred") == 0) || (strcmp(argv[i], "onlygreen") == 0) || (strcmp(argv[i], "onlyblue") == 0)) {

            } else if ((strcmp(argv[i], "addred") == 0) || (strcmp(argv[i], "addgreen") == 0) || (strcmp(argv[i], "addblue") == 0)) {
                int num = checkInt(i, argc, argv);
                if (num == 1) {
                    return 1;
                } else {
                    i++;
                }

            } else if ((strcmp(argv[i], "scalered") == 0) || (strcmp(argv[i], "scalegreen") == 0) || (strcmp(argv[i], "scaleblue") == 0)){
                int num = checkInt(i, argc, argv);
                if (num == 1) {
                    return 1;
                } else {
                    i++;
                }
            }  else {
                cout << "Invalid method." << endl;
                return 1;
            }

        }
    }


    return 0;
}

