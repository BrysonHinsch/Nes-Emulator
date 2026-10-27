
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

void Apu::clock_pulse(int channel)
{

}

void Apu::sample_triangle()
{
    m.s_triangle = t.sequence[t.sequence_pos];
    t.sequence_pos = (t.sequence_pos + 1) % 32;
}

void Apu::sample_pulse(int channel)
{

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
    apu_cycle = !apu_cycle;
}

void Apu::clock_linear_counter()
{
    if (t.linear_counter_reload) {t.linear_counter = t.linear_counter_reload_value;}
    else if (t.linear_counter != 0) {t.linear_counter--;}
    if (t.length_counter_halt == false) {t.linear_counter_reload = false;}
}
void Apu::clock_length_counters()
{
    if (!t.length_counter_halt && t.length_counter != 0) {t.length_counter--;}
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

bool Apu::clock_envelope(Envelope& envelope)
{
    return true;
}

bool Apu::clock_sweep(Sweep& sweep)
{
    return true;
}

void Apu::clock_frame_counter()
{
    frame_counter++;
    if (frame_counter == 3728 || frame_counter == 7456 || frame_counter == 11185) // for both modes
    {
        clock_linear_counter();
        clock_envelope(p1.envelope);
        clock_envelope(p2.envelope);
    }
    if (frame_counter == 7456)
    {
        clock_length_counters();
        clock_sweep(p1.sweep);
        clock_sweep(p2.sweep);
    }
    if (sequencer_mode == false) // 4-step sequence
    {
        if (frame_counter == 14914)
        {
            clock_linear_counter();
            clock_envelope(p1.envelope);
            clock_envelope(p2.envelope);
            clock_length_counters();
            clock_sweep(p1.sweep);
            clock_sweep(p2.sweep);
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
            clock_envelope(p1.envelope);
            clock_envelope(p2.envelope);
            clock_length_counters();
            clock_sweep(p1.sweep);
            clock_sweep(p2.sweep);
            frame_counter = 0;
        }
    }
}

void Apu::calculate_target_period(PulseChannel& p, int channel)
{
    int change_amount = p.timer.saved_timer >> p.sweep.shift_count;

    p.sweep.target_period = (p.sweep.negate_flag) ?
    p.timer.saved_timer - change_amount :
    p.timer.saved_timer + change_amount;

    if (channel == 1 && p.sweep.negate_flag) p.sweep.target_period -= 1;
    if (p.sweep.target_period < 0) p.sweep.target_period = 0;
}

void Apu::mix_audio()
{
    float out = 0.0f;
    if (t.linear_counter != 0 && t.length_counter != 0)
        out = (static_cast<float>(m.s_triangle) - 8) * 0.1f; 
        
    audio_buffer[audio_buffer_index++] = out;
        
    if (audio_buffer_index == audio_buffer_length)
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
            p1.duty = (value & 0xC0) >> 6;
            p1.length_counter_halt = ((value & 0x20) == 0x20);
            p1.envelope.constant_volume_flag = ((value & 0x10) == 0x10);
            p1.envelope.envelope_divider = value & 0x0F;
            break;
        case 0x4001:
            p1.sweep.shift_count = (value & 0x07);
            p1.sweep.negate_flag = ((value & 0x08) == 0x08);
            p1.sweep.clock_rate = (value & 0x70) >> 4;
            p1.sweep.enable_flag = ((value & 0x80) == 0x80);
            calculate_target_period(p1, 1);
            break;
        case 0x4002:
            p1.timer.saved_timer = (p1.timer.saved_timer & 0xFF00) | value;
            calculate_target_period(p1, 1);
            break;
        case 0x4003:
            p1.timer.saved_timer = (p1.timer.saved_timer & 0x00FF) | ((value & 0x07) << 8);
            if (p1.enabled) {p1.length_counter = length_table[(value & 0xF8) >> 3];}
            p1.envelope.start_flag = true;
            p1.pulse_cycle = 0;
            p1.timer.timer = p1.timer.saved_timer;
            calculate_target_period(p1, 1);
            break;
        case 0x4004: // Pulse 2
            p2.duty = (value & 0xC0) >> 6;
            p2.length_counter_halt = ((value & 0x20) == 0x20);
            p2.envelope.constant_volume_flag = ((value & 0x10) == 0x10);
            p2.envelope.envelope_divider = value & 0x0F;
            break;
        case 0x4005:
            p2.sweep.shift_count = (value & 0x07);
            p2.sweep.negate_flag = ((value & 0x08) == 0x08);
            p2.sweep.clock_rate = (value & 0x70) >> 4;
            p2.sweep.enable_flag = ((value & 0x80) == 0x80);
            calculate_target_period(p2, 2);
            break;
        case 0x4006:
            p2.timer.saved_timer = (p2.timer.saved_timer & 0xFF00) | value;
            calculate_target_period(p2, 2);
            break;
        case 0x4007:
            p2.timer.saved_timer = (p2.timer.saved_timer & 0x00FF) | ((value & 0x07) << 8);
            if (p2.enabled) {p2.length_counter = length_table[(value & 0xF8) >> 3];}
            p2.envelope.start_flag = true;
            p2.pulse_cycle = 0;
            p2.timer.timer = p2.timer.saved_timer;
            calculate_target_period(p2, 2);
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
            t.timer.timer = t.timer.saved_timer;
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
            // TODO: Add pulse, noise, and dmc parts
            if ((value & 0x01) == 0x01) { // Pulse 1
                p1.enabled = true;
            }
            else {
                p1.enabled = false;
                p1.length_counter = 0;
            }
            if ((value & 0x02) == 0x02) { // Pulse 2
                p2.enabled = true;
            }
            else {
                p2.enabled = false;
                p2.length_counter = 0;
            }
            if ((value & 0x04) == 0x04) { // Triangle
                t.enabled = true;
            }
            else {
                t.enabled = false;
                t.length_counter = 0;
            }
            break;
        case 0x4017: // Frame Counter
            frame_counter = 0;
            sequencer_mode = ((value & 0x80) == 0x80);
            interrupt_inhibit = ((value & 0x40) == 0x40);
            break;
    }
}
