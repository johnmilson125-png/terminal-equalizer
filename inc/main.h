#pragma once

#include <iostream>
#include <cstddef>

#include "../inc/ui/visualizer.hpp"
#include "../inc/processing/signal_processor.hpp"
#include "../inc/math/fft.hpp"

extern std::mutex magMutex;
extern std::vector<double> sharedMagnitudes;