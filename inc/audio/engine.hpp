#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>
#include <mmeapi.h>
#include <vector>

class AudioEngine {
public:
    AudioEngine(const AudioEngine&) = delete; // remove copy constructor
    AudioEngine(AudioEngine&&) = delete; // remove move constructor

    // Access class statically
    static AudioEngine& Get();

    float GenVolLevel();

    // todo: get audio which is passable via an array of floats/doubles
    float FloatVolume();

private:
    // Initialize object
    AudioEngine();

    ~AudioEngine();

    // Initialize member variables (volume level)
    IMMDeviceEnumerator* pEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    IAudioEndpointVolume* pEndpointVolume = NULL;

    // Initialize member variables (audio samples)
    IAudioClient* pAudioClient = nullptr; // manage audio client
    IAudioCaptureClient* pAudioCaptureClient = nullptr; // capture buffer
    WAVEFORMATEX* pWAVEFORMATEX = nullptr; // https://learn.microsoft.com/en-us/windows/win32/api/audioclient/nf-audioclient-iaudioclient-initialize

    // temp
    float InternalGenVol();
    void DisplayMaster(); // display all audio samples

    std::vector<float> buffer;

};

#endif