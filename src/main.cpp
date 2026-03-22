#include <iostream>
#include <cstddef>
#include "fftw++.h"
#include "../inc/ui/visualizer.hpp"
#include "../inc/processing/signal_processor.hpp"

// FFTW++ global variables
namespace parallel { void Threshold(size_t threads) {} }
size_t threshold = 1024; 
namespace utils { size_t ALIGNMENT = 32; }

int main() {
    
    RenderEqualizer o;
    SignalProcessor s;
    // o.Display();
    while(true) {
        // o.DisplayBuffer();
        s.Accumulate();

        if(s.isFull()) {
            auto buff = s.GetFFTBuffer();
            std::cout << "Size of buffer: " << buff.size() << "\n";
        }
    }

    return 0;
}