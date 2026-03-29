#include "../inc/math/fft.hpp"

void FFT()
{
    size_t n = 2400; // input sample (real)
    size_t np = n / 2 + 1; // returning sample size (real + complex)
    size_t align = sizeof(Complex);

    array1<Complex> F(np, align); // returned
    array1<double> f(n, align); // input array of 2400 samples

    rcfft1d Forward(n, f, F);

    for(size_t i = 0; i < n; ++i) f[i] = i;

    std::cout << "Input: " << f << "\n";
    std::cout << "Output: " << F << "\n";


}