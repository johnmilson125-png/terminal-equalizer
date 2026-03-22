#include "../inc/processing/signal_processor.hpp"

SignalProcessor::SignalProcessor()
{
    // reserve space for 5 sample packets of 480
    samples.reserve(2400);
}

void SignalProcessor::Accumulate()
{

}

std::vector<float> GetFFTBuffer()
{
    
}