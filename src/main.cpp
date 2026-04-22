#include "../inc/main.h"

std::vector<double> sharedMagnitudes;
std::mutex magMutex;

void audioThread(SignalProcessor& signal, FFTEngine& fft) {
    while(1) 
    {
        signal.Accumulate();

        if(signal.isFull())
        {
            std::cout << "full" << "\n";

            auto pass  = signal.GetFFTBuffer();
            auto magnitudes  = fft.Run(pass);

            std::lock_guard<std::mutex> lock(magMutex);
            sharedMagnitudes = magnitudes;
        }

    }
}

void renderThread(RenderEqualizer& equalizer) {
    while (1) {
        {
            std::lock_guard<std::mutex> lock(magMutex);
            equalizer.EnableVisualizer(sharedMagnitudes);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}


int main() {
    SignalProcessor signal;
    FFTEngine fft;
    RenderEqualizer equalizer;

    std::thread t1(audioThread, std::ref(signal), std::ref(fft));
    std::thread t2(renderThread, std::ref(equalizer));

    t1.join();
    t2.join();

    return 0;
}