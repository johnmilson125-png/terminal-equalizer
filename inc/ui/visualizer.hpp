#pragma once

#include "../audio/engine.hpp"
#include "windows.h"

#include <vector>
#include <string>
#include <thread>
#include <chrono>

class RenderEqualizer {
public:
    void Display(); // general volume level
    void DisplayBuffer(); // print float values of buffer

    void EnableVisualizer(std::vector<double>& freq);

private:
    CONSOLE_SCREEN_BUFFER_INFO csbi;        
    int termWidth;
    int termHeight;

    std::vector<std::string> levels = 
    {   "#", 
        "##",
        "###",
        "####", 
        "#####", 
        "######", 
        "#######", 
        "########", 
        "#########", 
        "##########"
    };
};