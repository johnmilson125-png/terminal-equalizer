#include "../inc/processing/signal_processor.hpp"

SignalProcessor::SignalProcessor()
{
    // reserve space for 5 sample packets of 480
    samples.reserve(2400);
}

void SignalProcessor::Accumulate()
{
    std::vector<float> currentAudio = AudioEngine::Get().GetCurrentBuffer();

    if(isFull()) {
        samples.clear();
    } else {
        samples.insert(samples.end(), currentAudio.begin(), currentAudio.end());
    }
}

std::vector<float> SignalProcessor::GetFFTBuffer()
{   
    return samples;
}

bool SignalProcessor::isFull()
{
    if(samples.size() >= 2400) return true;
    return false;
}