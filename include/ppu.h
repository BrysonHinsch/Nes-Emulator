#pragma once

#include <cstdint>

#include "bus.h"
#include "renderer.h"

static const uint8_t palette[64][4] = {
    {84,84,84,255}, {0,30,116,255}, {8,16,144,255}, {48,0,136,255},
    {68,0,100,255}, {92,0,48,255}, {84,4,0,255}, {60,24,0,255},
    {32,42,0,255}, {8,58,0,255}, {0,64,0,255}, {0,60,0,255},
    {0,50,60,255}, {0,0,0,255}, {0,0,0,255}, {0,0,0,255},

    {152,150,152,255}, {8,76,196,255}, {48,50,236,255}, {92,30,228,255},
    {136,20,176,255}, {160,20,100,255}, {152,34,32,255}, {120,60,0,255},
    {84,90,0,255}, {40,114,0,255}, {8,124,0,255}, {0,118,40,255},
    {0,102,120,255}, {0,0,0,255}, {0,0,0,255}, {0,0,0,255},

    {236,238,236,255}, {76,154,236,255}, {120,124,236,255}, {176,98,236,255},
    {228,84,236,255}, {236,88,180,255}, {236,106,100,255}, {212,136,32,255},
    {160,170,0,255}, {116,196,0,255}, {76,208,32,255}, {56,204,108,255},
    {56,180,204,255}, {60,60,60,255}, {0,0,0,255}, {0,0,0,255},
    
    {236,238,236,255}, {168,204,236,255}, {188,188,236,255}, {212,178,236,255},
    {236,174,236,255}, {236,174,212,255}, {236,180,176,255}, {228,196,144,255},
    {204,210,120,255}, {180,222,120,255}, {168,226,144,255}, {152,226,180,255},
    {160,214,228,255}, {160,162,160,255}, {0,0,0,255}, {0,0,0,255},
};

struct sprite_data
{
    uint8_t pattern_low;
    uint8_t pattern_high;
    
    uint8_t attributes;
    uint8_t x_pos;
};

class Ppu {
    public:
        Ppu(Bus& bus, Renderer& renderer);

        // V register functions
        uint8_t get_coarse_x(int reg);
        uint8_t get_coarse_y(int reg);
        uint8_t get_nametable(int reg);
        uint8_t get_fine_y(int reg);
        bool get_vram_increment();

        // updates x and y indices
        void inc_x();
        void inc_y();
        void reset_x();
        void reset_y();

        // shift register loading functions
        void fetch_background();
        void fetch_sprite();

        // sprite functions
        void clear_secondary_oam();
        void sprite_eval();

        // fills buffer with pixel data using shift registers
        int generate_color(int index);
        void draw_pixel();

        // lets cpu read from registers
        uint8_t register_read(uint16_t address);
        // lets cpu write to registers
        uint8_t register_write(uint16_t address, uint8_t value);
        // lets cpu write to oam
        void write_oam(uint8_t index, uint8_t value);
        // executes a read from the ppu
        uint8_t read(uint16_t address);
        // executes a write for ppu data
        uint8_t write(uint16_t address, uint8_t value);
        // sets nmi flag in cpu
        void set_nmi_flag();

        // clocks the ppu for one cycle
        void clock_ppu();
        // sets default state for console power on
        void power_on();

        // checks if rendering is enabled
        bool rendering_enabled();

        // Rendering Information
        int buffer[256*240] = {0};
        Renderer& renderer;

        // PPU Registers
        uint8_t PPUCTRL = 0;
        uint8_t PPUMASK = 0;
        uint8_t PPUSTATUS = 0;
        uint8_t OAMADDR = 0;
        uint8_t OAMDATA = 0;
        uint16_t PPUSCROLL = 0;
        uint16_t PPUADDR = 0;
        uint8_t PPUDATA = 0;
        uint8_t OAMDMA = 0;

        // PPU register temporary values
        uint8_t ppudata_read_buffer = 0;

        bool v_scroll_update = false;
        uint8_t pending_v_scroll = 0;

        bool vram_address_update = false;
        uint16_t pending_vram_address = 0;
        bool vram_update_ready = false;

        bool oam_dma_exec = false;

        // Internal Registers
        uint16_t v = 0;
        uint16_t t = 0;
        uint8_t x = 0;
        bool w = false;

        // Ppu internal memory
        uint8_t OAM[256] = {0};
        uint8_t secondary_OAM[32] = {0};
        uint8_t palette_ram[0x20] = {0};

        // Rendering Addresses
        uint16_t nametable_addr = 0;
        uint16_t attribute_addr = 0;

        // Rendering Latches
        uint8_t nametable_byte = 0;
        uint8_t attribute_byte = 0;
        uint8_t pattern_low = 0;
        uint8_t pattern_high = 0;

        // Shift Registers
        uint16_t pattern_shift_low = 0;
        uint16_t pattern_shift_high = 0;
        uint16_t attribute_shift_low = 0;
        uint16_t attribute_shift_high = 0;

        // Sprite Evaluation
        sprite_data sprite_registers[8] = {0};
        uint8_t value = 0; // value read from OAM to be processed
        int eval_index = 0; // equivalent to n on nesdev wiki
        int eval_offset = 0;  // equivalent to m on nesdev wiki
        bool load_sprite_zero_next = false; // set sprite 0 loaded next scanline
        bool sprite_zero_loaded = false; // is sprite 0 in S-OAM this scanline

        // Pixel indices
        int scanline = 0;
        int dot = 0;

        // State trackers
        bool address_ready = false;
        uint8_t local_clock = 0;
        bool odd_frame = false;
        bool nmi_called = false;

        // Bus for reading and writing to memory
        Bus& bus;
};