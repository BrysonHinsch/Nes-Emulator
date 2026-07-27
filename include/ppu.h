#pragma once

#include <cstdint>

#include "bus.h"
#include "renderer.h"

class Ppu {
    public:
        Ppu();

        // Clocks the ppu for one cycle
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
        uint8_t w;

        // OAM
        uint8_t OAM[256];

        // Rendering Latches
        uint8_t nametable_byte;
        uint8_t attribute_byte;
        uint8_t pattern_low;
        uint8_t pattern_high;

        // Shift Registers


        // Pixel indices
        int scanline;
        int dot;

        // State trackers
        bool address_ready;
        uint8_t local_clock;

        // PPU sends pixel data here to be rendered
        Renderer& renderer;
};