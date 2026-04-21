#pragma once

#include "../audio/engine.hpp"
#include "windows.h"

#include <vector>
#include <string>

class RenderEqualizer {
public:
    void Display(); // general volume level
    void DisplayBuffer(); // print float values of buffer
    void EnableVisualizer(); 

private:
    int x = 0;

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