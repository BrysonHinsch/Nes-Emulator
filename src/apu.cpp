
#include "apu.h"
#include <iostream>

Apu::Apu(Bus &bus): bus(bus)
{
    spec.format = SDL_AUDIO_F32;
    spec.channels = 1;
    spec.freq = sample_rate;

    id = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK;

    audio_stream = SDL_OpenAudioDeviceStream(
        id,
        &spec,
        nullptr,
        nullptr
    );

    SDL_ResumeAudioStreamDevice(audio_stream);
}

void Apu::clock_triangle()
{
    if (clock_timer(t.timer)) // if timer wraps back to t
    {
        if (t.linear_counter != 0 && t.length_counter != 0)
        {
            sample_triangle();
        }
    }
}

void Apu::sample_triangle()
{
    m.s_triangle = t.sequence[t.sequence_pos];
    t.sequence_pos = (t.sequence_pos + 1) % 32;
}

void Apu::clock_apu()
{
    // clock triangle wave regardless
    clock_triangle();
    if (apu_cycle)
    {
        clock_frame_counter();
        // time to send a sample to SDL
        if (sample_cycle == (sample_cycles - 1))
        {
            mix_audio();
        }
        sample_cycle = (sample_cycle + 1) % sample_cycles;
    }
    /*
    audio_buffer[audio_buffer_index++] = ((audio_buffer_index % 109) < 54) ? 0.1f : -0.1f;
    if (audio_buffer_index == 512)
    {
        audio_buffer_index = 0;
        SDL_PutAudioStreamData(audio_stream, audio_buffer, audio_buffer_length * sizeof(audio_buffer[0]));
    }
    */
    apu_cycle = !apu_cycle;
}

void Apu::clock_linear_counter()
{
    if (t.linear_counter_reload) {t.linear_counter = t.linear_counter_reload_value;}
    else if (t.linear_counter != 0) {t.linear_counter--;}
    if (t.length_counter_halt == 0) {t.linear_counter_reload = false;}
}
void Apu::clock_length_counters()
{
    if (t.length_counter != 0) {t.length_counter--;}
}

bool Apu::clock_timer(Timer& timer)
{
    timer.timer-=1;
    if (timer.timer == -1)
    {
        timer.timer = timer.saved_timer;
        return true;
    }
    return false;
}

void Apu::clock_frame_counter()
{
    frame_counter++;
    if (frame_counter == 3728 || frame_counter == 7456 || frame_counter == 11185) // for both modes
    {
        clock_linear_counter();
    }
    if (frame_counter == 7456)
    {
        clock_length_counters();
    }
    if (sequencer_mode == false) // 4-step sequence
    {
        if (frame_counter == 14914)
        {
            clock_linear_counter();
            clock_length_counters();
            // Set frame interrupt flag if interrupt inhibit is clear
            if (!interrupt_inhibit)
            {
                frame_interrupt = true;
            }
            frame_counter = 0;
        }
    }
    else // 5-step sequence
    {
        if (frame_counter == 18640)
        {
            clock_linear_counter();
            clock_length_counters();
            frame_counter = 0;
        }
    }
}

void Apu::mix_audio()
{
    if (t.linear_counter != 0 && t.length_counter != 0)
        audio_buffer[audio_buffer_index++] = (static_cast<float>(m.s_triangle) - 8) * 0.1f;
        
    if (audio_buffer_index == 100)
    {
        audio_buffer_index = 0;
        SDL_PutAudioStreamData(audio_stream, audio_buffer, audio_buffer_length * sizeof(audio_buffer[0]));
    }
}

void Apu::write(uint16_t address, uint8_t value)
{
    switch (address)
    {
        case 0x4000: // Pulse 1
            break;
        case 0x4001:
            break;
        case 0x4002:
            break;
        case 0x4003:
            break;
        case 0x4004: // Pulse 2
            break;
        case 0x4005:
            break;
        case 0x4006:
            break;
        case 0x4007:
            break;
        case 0x4008: // Triangle
            t.length_counter_halt = ((value & 0x80) == 0x80);
            t.linear_counter_reload_value = (value & 0x7F);
            break;
        case 0x4009:
            // Unused
            break;
        case 0x400A:
            t.timer.saved_timer = (t.timer.saved_timer & 0xFF00) | value;
            break;
        case 0x400B:
            t.timer.saved_timer = (t.timer.saved_timer & 0x00FF) | ((value & 0x07) << 8);
            if (t.enabled) {t.length_counter = length_table[(value & 0xF8) >> 3];}
            t.linear_counter_reload = true;
            break;
        case 0x400C: // Noise
            break;
        case 0x400D:
            break;
        case 0x400E:
            break;
        case 0x400F:
            break;
        case 0x4010: // DMC
            break;
        case 0x4011:
            break;
        case 0x4012:
            break;
        case 0x4013:
            break;
        case 0x4015: // APU Status Register
            break;
        case 0x4017: // Frame Counter
            break;
}
}
