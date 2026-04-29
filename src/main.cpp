#include "../inc/main.h"
#include <csignal>
#include <atomic>

std::atomic<bool> keepRunning(true);

void signalHandler(int signum) {
    keepRunning = false;
    AudioEngine::Get().Stop();
}

int main() {
    // register signal handler for clean exit
    signal(SIGINT, signalHandler);

    SignalProcessor signal;
    FFTEngine fft;
    RenderEqualizer equalizer;

    std::mutex magMutex;
    std::vector<double> sharedMagnitudes;

    std::thread t1([&]() {
        CoInitialize(NULL);
        while (keepRunning) {
            signal.Accumulate();
            if (signal.isFull()) {
                auto pass = signal.GetFFTBuffer();
                auto magnitudes = fft.Run(pass);
                std::lock_guard<std::mutex> lock(magMutex);
                sharedMagnitudes = magnitudes;
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
        }
        CoUninitialize();
    });

    std::thread t2([&]() {
        CoInitialize(NULL);
        int sampleRate = AudioEngine::Get().GetSampleRate();
        equalizer.EnableVisualizer(sharedMagnitudes, magMutex, sampleRate);
        CoUninitialize();
    });

    t1.join();
    t2.join();

    return 0;
}