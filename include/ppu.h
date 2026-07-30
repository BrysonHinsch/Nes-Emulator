#pragma once

#include <cstdint>

#include "bus.h"
#include "renderer.h"

class Ppu {
    public:
        Ppu();

        // V register functions
        uint8_t get_coarse_x(int reg);
        uint8_t get_coarse_y(int reg);
        uint8_t get_nametable(int reg);
        uint8_t get_fine_y(int reg);

        // lets cpu read from registers
        uint8_t register_read(uint16_t address);
        // lets cpu write to registers
        uint8_t register_write(uint16_t address, uint8_t value);
        // executes a read from the ppu
        uint8_t read(uint16_t address);

        // clocks the ppu for one cycle
        void clock_ppu();
        // sets default state for console power on
        void power_on();

    private:
        // PPU Registers
        uint8_t PPUCTRL;
        uint8_t PPUMASK;
        uint8_t PPUSTATUS;
        uint8_t OAMADDR;
        uint8_t OAMDATA;
        uint16_t PPUSCROLL;
        uint16_t PPUADDR;
        uint8_t PPUDATA;
        uint8_t OAMDMA;

        // Internal Registers
        uint16_t v;
        uint16_t t;
        uint8_t x;
        bool w;

        // Ppu internal memory
        uint8_t OAM[256];
        uint8_t palette_ram[0x20];

        // Rendering Latches
        uint8_t nametable_byte;
        uint8_t attribute_byte;
        uint8_t pattern_low;
        uint8_t pattern_high;

        // Shift Registers
        uint16_t pattern_shift_low;
        uint16_t pattern_shift_high;
        uint8_t attribute_shift_one;
        uint8_t attribute_shift_two;

        // Pixel indices
        int scanline;
        int dot;

        // State trackers
        bool address_ready;
        uint8_t local_clock;
        bool even_frame;

        // Rendering Information
        int buffer[256*240];
        Renderer& renderer;

        // Bus for reading and writing to memory
        Bus& bus;
};