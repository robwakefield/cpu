#include "../types.h"
#include "../helpers/helpers.h"
#include "../gate/gate.h"
#include "../adder/adder.h"

#ifndef ALU_H
#define ALU_H

#define OP_ADD 0x0
#define OP_SUB 0x2
#define OP_XOR 0x4
#define OP_AND 0x5
#define OP_OR 0x6
#define OP_SR 0x7

typedef unsigned char alu_op;

struct status_reg {
  bit carry_out;
  bit zero;
  bit negative;
  bit overflow;
  bit parity;
};

// https://lateblt.livejournal.com/87418.html
struct ALU_state {
  alu_op opcode;
  bit carry_in;
  // Input operand registers
  byte A;
  byte B;
  // Output result register
  byte Y;
  status_reg status;
};

namespace ALU {
  ALU_state my6502(byte, byte, bit, alu_op);
  byte block_AND(byte, byte);
  byte block_OR(byte, byte);
  byte block_XOR(byte, byte);
}

#endif