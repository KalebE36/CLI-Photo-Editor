#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include "Image.h"


int checkTGA(string& test_string) {

    if (test_string.find(".tga") == -1) {
        cout << "Invalid argument, invalid file name." << endl;
        return 1;
    }

    if (test_string.length() <= 4) {
        cout << "Invalid file name." << endl;
        return 1;
    }

    return 0;
}


int checkInt(int& index, int& argc, char**& argv) {
    if (argc <= (index+1)) {
        cout << "Missing argument." << endl;
        return 1;
    }
    string test_string = (string)argv[index+1];
    try {
        int num = stoi(test_string);
    } catch(...) {
        cout << "Invalid argument, expected number." << endl;
        return 1;
    }

    return 0;
}



int checkCombine(int& index, int& argc, char**& argv) {
    if (argc <= (index+2)) {
        cout << "Missing argument." << endl;
        return 1;
    }

    string test_string = (string)argv[index+1];
    string test_string2 = (string)argv[index+2];

    if(test_string.length() <= 4) {
        cout << "Invalid file name." << endl;

        return 1;
    }

    if (test_string.find(".tga") == -1) {
        cout << "Invalid argument, invalid file name." << endl;
        return 1;
    }

    if(test_string2.length() <= 4) {
        cout << "Invalid file name." << endl;

        return 1;
    }

    if (test_string2.find(".tga") == -1) {
        cout << "Invalid argument, invalid file name." << endl;
        return 1;
    }


    int check_num = 0;
    Image test_image1;
    Image test_image2;

    test_image1.read(argv[index+1], check_num);
    if (check_num == 1){
        cout << "Invalid argument, file does not exist." << endl;
        return 1;
    }

    test_image2.read(argv[index+2], check_num);
    if (check_num == 1) {
        cout << "Invalid argument, file does not exist." << endl;
    }
    return check_num;

}


int checkOneArg(int& index, int& argc, char**& argv) {
    if (argc <= (index+1)) {
        cout << "Missing argument." << endl;
        return 1;
    }

    string test_string = argv[index+1];
    int test_num = checkTGA(test_string);
    if(test_num == 1) {
        return 1;
    }

    Image test_image;
    test_image.read(argv[index+1], test_num);
    if (test_num == 1) {
        cout << "Invalid argument, file does not exist." << endl;
        return 1;
    }
    return test_num;

}


int checkArgs(int& argc, char**&argv) {
    if ((argc == 1) || (strcmp(argv[1], "--help") == 0)) {
        cout << "Project 2: Image Processing, Fall 2023" << endl << endl;
        cout << "Usage:" << endl;
        cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl << endl;

        return 2;

    }

    if(argc > 1) {
        string test_string = (string)argv[1];
        if(test_string.find(".tga") == -1) {
            cout << "Invalid file name." << endl;

            return 1;
        }

        if(test_string.length() <= 4) {
            cout << "Invalid file name." << endl;

            return 1;
        }

    }

    if (argc >= 3) {
        Image test_image;
        string test_string = (string)argv[2];


        if (test_string.find(".tga") == -1) {
            cout << "Invalid file name." << endl;
            return 1;
        }

        if(test_string.length() <= 4) {
            cout << "Invalid file name." << endl;

            return 1;
        }

        int check_num = 0;
        test_image.read(test_string, check_num);
        if(check_num == 1){
            cout << "File does not exist." << endl;
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
                }
                string test_string = argv[i+1];
                int test_num = checkTGA(test_string);
                if(test_num == 1) {
                    return 1;
                } else {
                    i++;
                }

            } else if (strcmp(argv[i], "subtract") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;
                }
                string test_string = argv[i+1];
                int test_num = checkTGA(test_string);
                if(test_num == 1) {
                    return 1;
                } else {
                    i++;
                }
            } else if (strcmp(argv[i], "overlay") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;

                }
                string test_string = argv[i+1];
                int test_num = checkTGA(test_string);
                if(test_num == 1) {
                    return 1;
                } else {
                    i++;
                }
            } else if (strcmp(argv[i], "screen") == 0) {
                int num = checkOneArg(i, argc, argv);
                if (num == 1) {
                    return 1;

                }
                string test_string = argv[i+1];
                int test_num = checkTGA(test_string);
                if(test_num == 1) {
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
                cout << "Invalid method name." << endl;
                return 1;
            }

        }
    }


    return 0;
}


