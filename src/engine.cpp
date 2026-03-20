#include "../inc/audio/engine.hpp"

// Initialize object
AudioEngine::AudioEngine() 
{ 
    CoInitialize(NULL);

    // Get the default audio endpoint
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

    // Activate volume interface
    pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pEndpointVolume);

    
    // Count of channels in audio stream that enter/leave audio enpoint
    UINT ChannelCount = 0;

    // https://learn.microsoft.com/en-us/windows/win32/api/endpointvolume/nf-endpointvolume-iaudioendpointvolume-getchannelcount
    pEndpointVolume->GetChannelCount(&ChannelCount);

    // https://learn.microsoft.com/en-us/windows/win32/api/endpointvolume/nf-endpointvolume-iaudioendpointvolume-getchannelcount
    HRESULT result = pEndpointVolume->GetChannelCount(&ChannelCount);
}

// Access class statically
AudioEngine& AudioEngine::Get()
{
    static AudioEngine instance;
    return instance;
}

float AudioEngine::GenVolLevel() 
{ 
    return Get().InternalGenVol();
}

std::vector<float> AudioEngine::GetCurrentBuffer()
{
    return Get().InternalBuffer();
}

// Cleanup
AudioEngine::~AudioEngine()
{
    // general volume
    pEndpointVolume->Release();
    pDevice->Release();
    pEnumerator->Release();

    // audio samples
    if (pAudioCaptureClient) pAudioCaptureClient->Release();
    if (pAudioClient) pAudioClient->Release();

    // free COM-allocated memory (windows allocates it manually)
    if (pWAVEFORMATEX) {
        CoTaskMemFree(pWAVEFORMATEX); // [4]
    }

    CoUninitialize();
}

float AudioEngine::InternalGenVol() 
{ 
    float vol = 0;

    // Update volume level for channel 0 (CBR)
    pEndpointVolume->GetChannelVolumeLevelScalar(0, &vol);

    return vol;
}

// capture loop
std::vector<float> AudioEngine::InternalBuffer()
{
    UINT32 packetLength = 0;
    HRESULT hr = pAudioCaptureClient->GetNextPacketSize(&packetLength);

    // clear previous data
    buffer.clear();

    while(packetLength != 0)
    {
        BYTE* pData;
        UINT32 availableFrames;
        DWORD flags;

        // lock windows audio buffer
        hr = pAudioCaptureClient->GetBuffer(&pData, &availableFrames, &flags, NULL, NULL);

        // cast raw bytes into floats
        float* fData = (float*)pData;

        for(UINT32 i = 0; i < availableFrames; ++i)
        {
            // *2 for left and right values of stereo :) ([left][right])
            float left = fData[i * 2];
            float right = fData[i * 2 + 1];
            buffer.push_back((left + right) / 2.0f);
        }

        // release lock
        hr = pAudioCaptureClient->ReleaseBuffer(availableFrames);

        // check if there is another packet waiting
        hr = pAudioCaptureClient->GetNextPacketSize(&packetLength);
    }

    return buffer;
}

void AudioEngine::DisplayMaster() 
{
    // display each float in buffer
}