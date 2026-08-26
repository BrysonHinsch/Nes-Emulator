
#include "ppu.h"

Ppu::Ppu(Bus& bus, Renderer& renderer): renderer(renderer), bus(bus) {}

uint8_t Ppu::get_coarse_x(int reg)
{
    return reg & 0x1F;
}
uint8_t Ppu::get_coarse_y(int reg)
{
    return (reg & 0x3E0) >> 5;
}
uint8_t Ppu::get_nametable(int reg)
{
    return (reg & 0xC00) >> 10;
}
uint8_t Ppu::get_fine_y(int reg)
{
    return (reg & 0x7000) >> 12;
}
bool Ppu::get_vram_increment()
{
    return ((PPUCTRL & 0x04) == 0x04) ? true : false;
}

void Ppu::inc_x()
{
    if ((v & 0x001F) == 31) {
        v &= ~0x001F;
        v ^= 0x0400;
    }
    else {
        v += 1;
    }
}
void Ppu::inc_y()
{
    if ((v & 0x7000) != 0x7000) {v += 0x1000;}
    else
    {
        v &= ~0x7000;
        int y = (v & 0x03E0) >> 5;
        if (y == 29)
        {
            y = 0;
            v ^= 0x0800;
        }
        else if (y == 31) {y = 0;}
        else
        {
            y += 1;
        }
        v = (v & ~0x03E0) | (y << 5);
    }
}
void Ppu::reset_x()
{
    int x = get_coarse_x(t);
    v = (v & 0xFBE0) | x | (t & 0x0400);
}
void Ppu::reset_y()
{
    int cy = get_coarse_y(t);
    int fy = get_fine_y(t);
    v = (v & 0x841F) | (cy << 5) | (fy << 12) | (t & 0x0800);
}

void Ppu::reset_sprite_variables()
{
    // reset counters and indices
    eval_index = 0;
    eval_offset = 0;
    secondary_oam_index = 0;
    oam_index_overflow = false;

    // reset oam address index
    sprite_render_index = 0;

    // set whether sprite 0 is loaded in upcoming scanline
    sprite_zero_loaded = load_sprite_zero_next;
    load_sprite_zero_next = false;
}

uint8_t Ppu::register_read(uint16_t address)
{
    int reg = (address - 0x2000) % 8;
    if (reg == 2) // done
    {
        w = false;
        uint8_t temp = PPUSTATUS;
        PPUSTATUS &= 0x7F;
        return temp;
    }
    else if (reg == 4) // done
    {
        return OAM[OAMADDR];
    }
    else if (reg == 7) // done
    {
        uint8_t temp = ppudata_read_buffer;
        ppudata_read_buffer = read(v);
        v = (get_vram_increment()) ? v+32 : v+1;
        return temp;
    }
    return 0;
}
uint8_t Ppu::register_write(uint16_t address, uint8_t value)
{
    int reg = (address - 0x2000) % 8;
    if (reg == 0) // done
    {
        t = (t & 0xF3FF) | ((value & 0x03) << 10);
        PPUCTRL = value;
        return PPUCTRL;
    }
    else if (reg == 1) // done
    {
        PPUMASK = value;
        return PPUMASK;
    }
    else if (reg == 3) // done
    {
        OAMADDR = value;
        return OAMADDR;
    }
    else if (reg == 4) // done
    {
        if (scanline <= 239) {return 0;}
        write_oam(OAMADDR++, value);
        return value;
    }
    else if (reg == 5) // done
    {
        if (!w) // write 1
        {
            t = (t & 0xFFE0) | (value >> 3);
            x = value & 0x07;
            w = true;
            return 0;
        }
        else // write 2
        {
            t = (t & 0x8C1F) | ((value & 0xF8) << 2) | ((value & 0x07) << 12);
            w = false;
            return 0;
        }
    }
    else if (reg == 6) // done
    {
        if (!w) // write 1
        {
            t = (t & 0x00FF) | ((value & 0x3F) << 8);
            t &= 0x3FFF; // clear bit 15
            w = true;
            return 0;
        }
        else // write 2
        {
            t = (t & 0xFF00) | value;
            w = false;
            vram_address_update = true;
            return 0;
        }
    }
    else if (reg == 7) // done
    {
        if (v > 0x3FFF) {std::cout<<"hit at address: "<<std::hex<<"0x"<<v<<"\n";}
        write(v, value);
        v = (get_vram_increment()) ? v+32 : v+1;
        return 0;
    }
    return 0;
}

void Ppu::write_oam(uint8_t index, uint8_t value)
{
    OAM[index] = value;
}

uint8_t Ppu::read(uint16_t address)
{
    address &= 0x3FFF;
    if (address >= 0x3F00 && address <= 0x3FFF) // Palette Ram
    {
        return palette_ram[(address - 0x3F00) % 0x20];
    }
    else
    {
        return bus.read_ppu(address);
    }
}
uint8_t Ppu::write(uint16_t address, uint8_t value)
{
    address &= 0x3FFF;
    if (address < 0x3000) // vram
    {
        return bus.write_ppu(address, value);
    }
    else if (address >= 0x3F00 && address < 0x4000)
    {
        palette_ram[(address - 0x3F00) % 0x20] = value;
        return 0;
    }
    return 0;
}

void Ppu::set_nmi_flag()
{
    bus.set_nmi_flag();
}

void Ppu::fetch_background()
{
    // shift registers to the left once per cycle
    pattern_shift_low <<= 1;
    pattern_shift_high <<= 1;
    attribute_shift_low <<= 1;
    attribute_shift_high <<= 1;
    switch (local_clock)
    {
        case 0: // read nametable byte
            nametable_addr = 0x2000 | (v & 0x0FFF);
            break;
        case 1: // read nametable byte
            nametable_byte = read(nametable_addr);
            break;
        case 2: // read attribute table byte
            attribute_addr = 0x23C0 | (v & 0x0C00) | ((v >> 4) & 0x38) | ((v >> 2) & 0x07);
            break;
        case 3: { // read attribute table byte
            int temp = read(attribute_addr);
            int shift = ((v >> 4) & 4) | (v & 2);
            attribute_byte = (temp >> shift) & 0x03;
            break; }
        case 4: // read pattern table low byte
            break;
        case 5: { // read pattern table low byte
            int half = (PPUCTRL & 0x10) << 8;
            int fy = get_fine_y(v);
            pattern_low = read(half | (nametable_byte << 4) | fy);
            break; }
        case 6: // read pattern table high byte
            break;
        case 7: { // read pattern table high byte
            int half = (PPUCTRL & 0x10) << 8;
            int fy = get_fine_y(v);
            pattern_high = read(half | (nametable_byte << 4) | fy + 8);

            // load shift registers
            pattern_shift_low |= pattern_low;
            pattern_shift_high |= pattern_high;

            uint8_t al = ((attribute_byte & 0b01) == 0b01) ? 0xFF : 0x00;
            uint8_t ah = ((attribute_byte & 0b10) == 0b10) ? 0xFF : 0x00;

            attribute_shift_low |= al;
            attribute_shift_high |= ah;

            // increment x offset
            inc_x();
            break; }
    }
}
void Ppu::fetch_sprite() // TODO implement 8x16 sprites
{
    switch (local_clock)
    {
        case 0: {// unused nametable byte
            nametable_addr = 0x2000 | (v & 0x0FFF);
            // Fetch tile index to sprite latch
            int i = sprite_render_index;
            sprite_registers[i].tile_index = secondary_OAM[(i*4)+1]; // for convenience
            break; }
        case 1: // unused nametable byte
            read(nametable_addr);
            break;
        case 2: {// ignored nametable byte
            nametable_addr = 0x2000 | (v & 0x0FFF);
            // Fetch attribute byte to sprite latch
            int i = sprite_render_index;
            sprite_registers[i].attributes = secondary_OAM[(i*4)+2];
            break; }
        case 3: {// ignored nametable byte
            read(nametable_addr);
            // Fetch x-position to sprite latch
            int i = sprite_render_index;
            sprite_registers[i].x_pos = secondary_OAM[(i*4)+3];
            break; }
        case 4: // sprite lsbits
            break;
        case 5: {// sprite lsbits
            int i = sprite_render_index;
            int tile = sprite_registers[i].tile_index << 4;
            int fy = get_fine_y(v);
            int index = fy | tile | ((PPUCTRL & 0x08) << 9);
            sprite_registers[i].pattern_low = read(index);
            break; }
        case 6: // sprite msbits
            break;
        case 7: // sprite msbits
            int i = sprite_render_index;
            int tile = sprite_registers[i].tile_index << 4;
            int fy = get_fine_y(v);
            int index = fy | 0x08 | tile | ((PPUCTRL & 0x08) << 9);
            sprite_registers[i].pattern_high = read(index);
            // increment oam fetching address
            sprite_render_index++;
            break;
    }
}

void Ppu::clear_secondary_oam()
{
    if ((dot % 2) == 2) 
    {
        secondary_OAM[dot/2] = 0xFF;
    }
}
void Ppu::sprite_eval() // TODO
{
    if ((dot % 2) != 0) // odd cycle
    {
        int index = eval_index * 4 + eval_offset;
        eval_value = OAM[index];
        return;
    }
    else // even cycle
    {
        if (oam_index_overflow) // check for overflow flag hits
        {
            // TODO overflow flag hit detection
            return;
        }
        if (secondary_oam_full) // read instead if full
        {
            // TODO DUMMY READ
            return;
        }
        else
        {
            if (eval_offset == 0)
            {
                // 1 if 8x8, 2 if 8x16
                int sprite_height = 8 * (((PPUCTRL & 0x20) >> 5) + 1) - 1;
                int diff = scanline - eval_value;
                if (diff < 0 || diff > sprite_height) // miss
                {
                    eval_index++;
                    return;
                }
            }
        }
        secondary_OAM[secondary_oam_index++] = eval_value;
        if (secondary_oam_index == 32) {secondary_oam_full = true;}

        // set new offsets
        eval_offset = (eval_offset + 1) % 4;
        if (eval_offset == 0) 
        {
            eval_index = (eval_index + 1) % 64;
            if (eval_index == 0) {oam_index_overflow = true;}
        } 
    }
}

int Ppu::generate_color(int index, bool sprite)
{
    const uint8_t* value = palette[index & 0x3F];
    return (value[0] << 24) | (value[1] << 16) | (value[2] << 8) | value[3];
}
void Ppu::draw_pixel() // TODO
{   
    // TODO CURRENTLY MISSING SPRITES!!!

    int pattern_offset = ((pattern_shift_low >> (15-x)) & 0x0001) | (((pattern_shift_high >> (15-x)) & 0x0001) << 1);
    int attribute_offset = ((attribute_shift_low >> (15-x)) & 0x0001) | (((attribute_shift_high >> (15-x)) & 0x0001) << 1);
    // get index from palette ram
    int index = read(0x3F00 + (attribute_offset * 4) + pattern_offset);
    // send pixel data to buffer
    int color = generate_color(index, false);
    int buffer_index = (dot - 1) + (scanline * 256);
    buffer[buffer_index] = color;
}

void Ppu::clock_ppu() {
    if (scanline < 240) // ########## rendering ##########
    {
        if (dot == 0) // idle cycle, fetch BG lsbit on odd frames only
        {
            // TODO
        }
        else if (dot <= 256) // background tiles
        {
            if (rendering_enabled())
            {
                fetch_background();
                draw_pixel();
                if (dot == 256) {inc_y();}
            }
            if (dot <= 64)
            {
                clear_secondary_oam();
            }
            if (dot > 64)
            {
                sprite_eval();
            }
        }
        else if (dot <= 320) // sprites
        {
            if (rendering_enabled())
            {
                if (dot == 257) // set coarse_x V to coarse_x T
                {
                    reset_x();
                }

                fetch_sprite();
            }
            if (dot == 320)
            {
                reset_sprite_variables();
            }
        }
        else if (dot <= 336) // next scanline background tiles
        {
            if (rendering_enabled())
            {
                fetch_background();
            }
        }
        else // unused nametable fetches
        {
            // TODO
        }
    }
    else if (scanline == 240) // ########## idle ##########
    {
        if (dot == 0) // idle cycle, fetch BG lsbit on odd frames only
        {
            // TODO
        }
    }
    else if (scanline <= 260) // ########## v-blank ##########
    {
        if (dot == 1)
        {
            PPUSTATUS |= 0x80; // set v-blank flag
            renderer.update_texture(buffer); // draw completed frame
        }
        
        // call nmi handler
        if (((PPUCTRL & 0x80) == 0x80) && ((PPUSTATUS & 0x80) == 0x80) && nmi_called == false)
        {
            set_nmi_flag();
            nmi_called = true;
        }
    }
    else if (scanline == 261) // ########## pre-render ##########
    {
        if (dot == 1) // clear v-blank, sprite 0, and overflow flags
        {
            PPUSTATUS &= 0x1F;
            nmi_called = false;
        }

        if (dot == 0) {} // idle cycle. do nothing for pre-render line
        
        else if (dot <= 256) // background tiles
        {
            if (rendering_enabled())
            {
                fetch_background();
                if (dot == 256) {inc_y();}
            }
        }
        else if (dot <= 320) // sprites
        {
            if (rendering_enabled())
            {
                if (dot == 257) // set coarse_x V to coarse_x T
                {
                    reset_x();
                }
                if (dot >= 280 && dot <= 304) // vert(v) = vert(t)
                {
                    reset_y();
                }

                fetch_sprite();
            }
            if (dot == 320)
            {
                reset_sprite_variables();
            }
        }
        else if (dot <= 336) // next scanline background tiles
        {
            if (rendering_enabled())
            {
                fetch_background();
            }
        }
        else // unused nametable fetches
        {
            // TODO garbage nametable fetches

            if (dot == 339 && odd_frame && (((PPUMASK & 0x08) == 0x08) || ((PPUMASK & 0x10) == 0x10)))
            {
                // dot already increments every cycle
                // this effectively skips the last pre-render cycle
                dot++;
            }
        }
    }
    // increments dot counter after every ppu cycle
    // scanline increments once dot wraps back to 0
    dot = (dot+1) % 341;
    if (dot == 0)
    {
        scanline = (scanline+1) % 262;
        if (scanline == 0)
        {
            odd_frame = !odd_frame;
        }
    }
    // Increment local_clock
    local_clock = (dot - 1) & 0x07;

    // Check for finished writes to PPUADDR
    // Adds 1 dot delay to update v from t
    if (vram_address_update == true) 
    {
        vram_address_update = false;
        vram_update_ready = true;
    }
    else if (vram_update_ready)
    {
        vram_update_ready = false;
        v = t;
    }
}

void Ppu::power_on()
{
    PPUCTRL = 0;
    PPUMASK = 0;
    PPUSTATUS = 0b10100000;
    OAMADDR = 0;
    w = 0;
    PPUSCROLL = 0;
    PPUADDR = 0;
    PPUDATA = 0;
    odd_frame = false;
}

bool Ppu::rendering_enabled()
{
    if ((PPUMASK & 0b00011000) == 0) {return false;}
    return true;
}