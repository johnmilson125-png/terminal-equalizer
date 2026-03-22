#include "../inc/processing/signal_processor.hpp"

SignalProcessor::SignalProcessor()
{
    // reserve space for 5 sample packets of 480
    samples.reserve(2400);
}

void SignalProcessor::Accumulate()
{
    auto currentAudio = AudioEngine::Get().GetCurrentBuffer();

    if(currentAudio.size() == 0) return;
    
    samples.insert(samples.end(), currentAudio.begin(), currentAudio.end());    
}

// if the vector somehow contains more than 2400 items don't remove them
std::vector<float> SignalProcessor::GetFFTBuffer()
{   
    std::vector<float> FFTBuffer;

    if(isFull()) {
        // assign 0 - 2400
        FFTBuffer.assign(samples.begin(), samples.begin() + 2400);

        // remove only the values added to FFTBuffer
        samples.erase(samples.begin(), samples.begin() + 2400);
    }

    return FFTBuffer;
}

bool SignalProcessor::isFull()
{
    if(samples.size() >= 2400) return true;
    return false;
}