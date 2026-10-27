#pragma once

#include "bus.h"
#include "SDL.h"

constexpr int audio_buffer_length = 512;
constexpr int sample_rate = 49716;
constexpr int sample_cycles = 18;

inline constexpr int length_table[32] = {
    10, 254, 20, 2, 40, 4, 80, 6, 
    160, 8, 60, 10, 14, 12, 26, 14, 
    12, 16, 24, 18, 48, 20, 96, 22, 
    192, 24, 72, 26, 16, 28, 32, 30
};

inline constexpr int duty_sequences[4][8] = {
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 0, 0, 0,
    1, 0, 0, 1, 1, 1, 1, 1
};

struct Timer
{
    int timer {};
    int saved_timer {};
};

struct Envelope
{
    
    int output_volume {}; // output volume used to calculate audio samples
    int envelope_divider {}; // controls speed which the envelope lowers and value for constant volume
    // flags
    bool constant_volume_flag {}; // If set, volume is constantly set to divider value
    bool start_flag {}; // set when length counter loaded, cleared on frame counter clock
    bool loop_flag {}; // same as LC halt flag, keeps decay level set to 15
    // internal counters
    int divider {}; // current position for envelope divider
    int decay_level {}; // set to 15, decrements when divider is 0
};

struct Sweep
{
    int shift_count {}; // number of bits the period is shifted to the right
    // flags
    bool negate_flag {}; // if set, shift to the left instead
    bool reload_flag {}; // set on write to $4001 or $4005
    bool enable_flag {}; // enables the sweep unit
    bool overflow_flag {}; // not in hardware, just for simplicity
    // target period for calculating overflow silencing
    int target_period {}; // what the period will be after adding the change
    // sweep unit clock
    int clock_rate {}; // saved sweep clock rate
    int clock_current {}; // current clock rate position
};

struct Mixer
{
    float s_triangle {};
    float s_pulse1 {};
    float s_pulse2 {};
    float s_noise {};
};

struct PulseChannel
{    
    // timer
    Timer timer {};
    // envelope unit
    Envelope envelope {};
    // sweep unit
    Sweep sweep {};
    // pulse variables
    int duty {}; // set to 0, 1, 2, 3 : 12.5%, 25%, 50%, 75% active
    int pulse_cycle {}; // position in duty cycle array
    // enabled bit
    bool enabled {};
    // length counter
    int length_counter {};
    bool length_counter_halt {};
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
    // enabled bit
    bool enabled {};
    // counter flags
    bool length_counter_halt {};
    bool linear_counter_reload {};
    int linear_counter_reload_value {};
};

class Apu
{
    public:
        Apu(Bus &bus);

        // clock channels
        void clock_triangle();
        void clock_pulse(int channel);

        // sample channels
        void sample_triangle();
        void sample_pulse(int channel);

        // clock apu once
        void clock_apu();

        // clock channel counters and registers
        void clock_linear_counter();
        void clock_length_counters();

        bool clock_timer(Timer& timer);
        void clock_envelope(Envelope& envelope);
        void clock_pulse_sweep(PulseChannel& pulse, int channel);

        void clock_frame_counter();

        void calculate_target_period(PulseChannel& p, int channel);

        void mix_audio();

        void write(uint16_t address, uint8_t value);

    private:

        // Distinguish between cpu cycle and apu cycle (mainly for triangle wave)
        bool apu_cycle {};

        // Cycles since audio was last sampled
        int sample_cycle {};

        // NES audio channels
        TriangleChannel t {};
        PulseChannel p1 {};
        PulseChannel p2 {};

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
        float audio_buffer[audio_buffer_length] {};
        int audio_buffer_index {};

        // audio stream
        SDL_AudioStream* audio_stream = nullptr;

        Bus& bus;
};