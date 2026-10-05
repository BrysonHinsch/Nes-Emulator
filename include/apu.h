#pragma once

#include "bus.h"
#include "SDL.h"

constexpr int audio_buffer_length = 512;
constexpr int sample_rate = 9927;
constexpr int sample_cycles = 1786860 / sample_rate;

struct Timer
{
    int timer {};
    int saved_timer {};
};

struct Mixer
{
    float s_triangle {};
    float s_pulse1 {};
    float s_pulse2 {};
    float s_noise {};
};

struct TriangleChannel
{
    // amplitude sequence
    int sequence_pos {};
    static constexpr uint8_t sequence[32] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    // timer
    Timer timer {};
    // counters
    int length_counter {};
    int linear_counter {};
};

class Apu
{
    public:
        Apu(Bus &bus);

        // clock channels
        void clock_triangle();

        // sample channels
        void sample_triangle();

        // clock apu once
        void clock_apu();

        // clock channel counters and registers
        void clock_linear_counter();
        void clock_length_counters();

        bool clock_timer(Timer& timer);

        void clock_frame_counter();

        void mix_audio();

    private:

        // Distinguish between cpu cycle and apu cycle (mainly for triangle wave)
        bool apu_cycle {};

        // Cycles since audio was last sampled
        int sample_cycle {};

        // NES audio channels
        TriangleChannel t {};

        // Mixer
        Mixer m {};

        // data required for audio stream
        SDL_AudioDeviceID id {};
        SDL_AudioSpec spec {}; 

        // frame counter
        uint16_t frame_counter {};
        bool sequencer_mode {};
        bool interrupt_inhibit {};

        // misc registers
        bool frame_interrupt {};

        // audio stream data buffer
        float audio_buffer[audio_buffer_length] = {0};
        int audio_buffer_index {};

        // audio stream
        SDL_AudioStream* audio_stream = nullptr;

        Bus& bus;
};