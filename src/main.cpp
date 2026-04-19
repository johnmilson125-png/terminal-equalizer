#include "../inc/main.h"

// FFTW++ global variables
namespace parallel { void Threshold(size_t threads) {} }
size_t threshold = 1024; 
namespace utils { size_t ALIGNMENT = 32; }

int main() {
    
    RenderEqualizer o;
    SignalProcessor s;
    FFTEngine f;
    // o.Display();

    /* signal_processor test
    while(true) {
        // o.DisplayBuffer();
        s.Accumulate();

        if(s.isFull()) {
            buff = s.GetFFTBuffer();
            std::cout << "Size of buffer: " << buff.size() << "\n";
        }
    }
    */

    // FFT Test
    while(1) 
    {
        s.Accumulate();

        // 2400
        if(s.isFull())
        {
            std::cout << "full" << "\n";

            auto pass  = s.GetFFTBuffer();
            auto magnitudes  = f.Run(pass);

            std::cout << magnitudes.size() << "\n";

            for (int16_t i = 0; i < magnitudes.size(); ++i)
            {
                std::cout << i << ". " << magnitudes[i] << "\n";
            }
        }

    }

    return 0;
}