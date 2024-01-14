#include "../types.h"
#include "../helpers/helpers.h"
#include "../gate/gate.h"
#include "../adder/adder.h"

#ifndef ALU_H
#define ALU_H

#define OP_ADD 0x07
#define OP_ASL 0x17
#define OP_CMP 0x2F
#define OP_CPX 0x4F
#define OP_CPY 0x6F
#define OP_DEC 0x5F
#define OP_INC 0x57
#define OP_SUB 0x0F
#define OP_AND 0x43
#define OP_BIT 0x53
#define OP_OR 0x79
#define OP_LSR 0x64
#define OP_ROL 0x7C
#define OP_ROR 0x0C
#define OP_XOR 0x02

typedef unsigned char alu_op;

const byte DISCONNECTED = 0xAA;

struct control_bits {
  bit A0;
  bit B1;
  bit B0;
  bit C0;
  bit D0;
  bit E1;
  bit E0;
  bit F2;
  bit F1;
  bit F0;
};

struct status_reg {
  bit zero;
  bit carry;
  bit sign;
  bit overflow;
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
  ALU_state perform(ALU_state);
  byte block_AND(byte, byte);
  byte block_OR(byte, byte);
  byte block_XOR(byte, byte);
  byte block_SR(byte, bit, bit);
  bit Z_logic(byte);
  bit C_logic(bit, bit, bit, alu_op);
  bit S_logic(bit, byte, alu_op);
  bit O_logic(bit, byte, byte, byte, alu_op);
}

#endif