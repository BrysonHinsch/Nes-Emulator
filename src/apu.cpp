
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

}
void Apu::clock_length_counters()
{

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
    audio_buffer[audio_buffer_index++] = (static_cast<float>(m.s_triangle) - 8) * 0.1f;
    if (audio_buffer_index == 100)
    {
        audio_buffer_index = 0;
        SDL_PutAudioStreamData(audio_stream, audio_buffer, audio_buffer_length * sizeof(audio_buffer[0]));
    }
}
