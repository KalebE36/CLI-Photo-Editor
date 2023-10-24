#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include "Image.h"




void implementArgs(Image& tracking_image, int& argc, char**& argv, int& check_num) {
    for(int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "multiply") == 0) {
            Image bottom_layer;
            bottom_layer.read(argv[i+1], check_num);
            tracking_image.multiply(bottom_layer);
            i++;
        } else if (strcmp(argv[i], "subtract") == 0) {
            Image bottom_layer;
            bottom_layer.read(argv[i+1], check_num);
            tracking_image.subtract(bottom_layer);
            i++;
        } else if (strcmp(argv[i], "overlay") == 0) {
            Image bottom_layer;
            bottom_layer.read(argv[i+1], check_num);
            tracking_image.overlay(bottom_layer);
            i++;

        } else if (strcmp(argv[i], "screen") == 0) {
            Image bottom_layer;
            bottom_layer.read(argv[i+1], check_num);
            tracking_image.screen(bottom_layer);
            i++;

        } else if (strcmp(argv[i], "combine") == 0) {
            Image blue_channel;
            Image green_channel;
            green_channel.read(argv[i+1], check_num);
            blue_channel.read(argv[i+2], check_num);
            tracking_image.combChannel(blue_channel, green_channel);
            i++;
            i++;

        } else if (strcmp(argv[i], "flip") == 0) {

        } else if((strcmp(argv[i], "onlyred") == 0) || (strcmp(argv[i], "onlygreen") == 0) || (strcmp(argv[i], "onlyblue") == 0)) {

        } else if ((strcmp(argv[i], "addred") == 0) || (strcmp(argv[i], "addgreen") == 0) || (strcmp(argv[i], "addblue") == 0)) {


        } else if ((strcmp(argv[i], "scalered") == 0) || (strcmp(argv[i], "scalegreen") == 0) || (strcmp(argv[i], "scaleblue") == 0)){

        }  else {

        }

    }

    tracking_image.write(argv[1]);




}






