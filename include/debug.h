#pragma once

#include <cstdint>

#include "opcodes.h"

struct LogEntry
{
    uint16_t pc;
    uint8_t opcode;
    uint8_t operand1, operand2;
    uint8_t numBytes;
    uint8_t A, X, Y, P, SP;
    uint32_t cyc;
};

class Debug
{
    
};