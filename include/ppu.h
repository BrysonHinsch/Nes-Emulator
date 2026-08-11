#pragma once

#include <cstdint>

#include "bus.h"
#include "renderer.h"

class Ppu {
    public:
        Ppu(Renderer& renderer, Bus& bus);

        // V register functions
        uint8_t get_coarse_x(int reg);
        uint8_t get_coarse_y(int reg);
        uint8_t get_nametable(int reg);
        uint8_t get_fine_y(int reg);
        bool get_vram_increment();

        void fetch_background(int local_clock);

        // lets cpu read from registers
        uint8_t register_read(uint16_t address);
        // lets cpu write to registers
        uint8_t register_write(uint16_t address, uint8_t value);
        // lets cpu write to oam
        void oam_dma_write(uint8_t value);
        // executes a read from the ppu
        uint8_t read(uint16_t address);

        // clocks the ppu for one cycle
        void clock_ppu();
        // sets default state for console power on
        void power_on();

        // Rendering Information
        int buffer[256*240] = {0};
        Renderer& renderer;

    private:
        // PPU Registers
        uint8_t PPUCTRL = 0;
        uint8_t PPUMASK = 0;
        uint8_t PPUSTATUS = 0;
        uint8_t OAMADDR = 0;
        uint8_t OAMDATA = 0;
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
        uint8_t oam_dma_counter = 0;

        // Internal Registers
        uint16_t v = 0;
        uint16_t t = 0;
        uint8_t x = 0;
        bool w = false;

        // Ppu internal memory
        uint8_t OAM[256];
        uint8_t palette_ram[0x20];

        // Rendering Latches
        uint8_t nametable_byte = 0;
        uint8_t attribute_byte = 0;
        uint8_t pattern_low = 0;
        uint8_t pattern_high = 0;

        // Shift Registers
        uint16_t pattern_shift_low = 0;
        uint16_t pattern_shift_high = 0;
        uint8_t attribute_shift_one = 0;
        uint8_t attribute_shift_two = 0;

        // Pixel indices
        int scanline = 0;
        int dot = 0;

        // State trackers
        bool address_ready = false;
        uint8_t local_clock = 0;
        bool even_frame = true;

        // Bus for reading and writing to memory
        Bus& bus;
};