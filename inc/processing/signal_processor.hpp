#ifndef SIGNAL_PROCESSOR_HPP
#define SIGNAL_PROCESSOR_HPP

#include "../audio/engine.hpp"
#include <vector>

class SignalProcessor {
public:
    SignalProcessor();
    void Accumulate();
    std::vector<float> GetFFTBuffer();
    bool isFull();

private:
    std::vector<float> samples;

};


#endif