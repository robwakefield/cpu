#include "alu.h"

using namespace gate;

namespace ALU {
  ALU_state my6502(byte a, byte b, bit carry_in, alu_op op) {
    ALU_state state = {
      .A = a,
      .B = b,
      .carry_in = carry_in,
      .opcode = op
    };

    // Connect outputs from each block to the MUX
    byte addsub_res = adder::addsub_8(a, b, _get_bit(op, 1));
    byte xor_res = block_XOR(a, b);
    byte and_res = block_AND(a, b);
    byte or_res = block_OR(a, b);
    byte sr_res = 0; // block_SR(a, b);

    byte choices[8] = {0};
    choices[OP_ADD] = addsub_res;
    choices[OP_SUB] = addsub_res;
    choices[OP_XOR] = xor_res;
    choices[OP_AND] = and_res;
    choices[OP_OR] = or_res;
    choices[OP_SR] = 0;

    state.Y = MUX::byte_8(choices, 
      _get_bit(op, 2), _get_bit(op, 1), _get_bit(op, 0));

    return state;
  }

  byte block_AND(byte a, byte b) {
    byte out = 0;
    for (int i = 0; i < 8; i++) {
      bit bit_a = _get_bit(a, i);
      bit bit_b = _get_bit(b, i);
      _set_bit(&out, i, AND(bit_a, bit_b));
    }
    return out;
  }

  byte block_OR(byte a, byte b) {
    byte out = 0;
    for (int i = 0; i < 8; i++) {
      bit bit_a = _get_bit(a, i);
      bit bit_b = _get_bit(b, i);
      _set_bit(&out, i, OR(bit_a, bit_b));
    }
    return out;
  }

  byte block_XOR(byte a, byte b) {
    byte out = 0;
    for (int i = 0; i < 8; i++) {
      bit bit_a = _get_bit(a, i);
      bit bit_b = _get_bit(b, i);
      _set_bit(&out, i, XOR(bit_a, bit_b));
    }
    return out;
  }
}