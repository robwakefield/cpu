#include "alu.h"

using namespace gate;

namespace ALU {
  ALU_state my6502(byte a, byte b, bit carry_in, alu_op opcode) {
    ALU_state state = {
      .opcode = opcode,
      .carry_in = carry_in,
      .A = a,
      .B = b,
      .Y = 0
    };
    return perform(state);
  }

  ALU_state perform(ALU_state state) {
    // Decode opcode into instruction signals
    control_bits bits = {
      .A0 = _get_bit(state.opcode, 6),
      .B1 = _get_bit(state.opcode, 5),
      .B0 = _get_bit(state.opcode, 4),
      .C0 = _get_bit(state.opcode, 4),
      .D0 = _get_bit(state.opcode, 3),
      .E1 = _get_bit(state.opcode, 4),
      .E0 = _get_bit(state.opcode, 3),
      .F2 = _get_bit(state.opcode, 2),
      .F1 = _get_bit(state.opcode, 1),
      .F0 = _get_bit(state.opcode, 0)
    };

    // Connect inputs to each block using MUXs
    byte adder_A = MUX::byte_2(state.A, 0x1, bits.A0);
    byte adder_B = MUX::byte_4(state.B, state.A, state.Y, DISCONNECTED, bits.B1, bits.B0);
    byte addsub_res = adder::addsub_8(adder_A, adder_B, bits.D0);

    byte or_res = block_OR(state.A, state.B);
    byte xor_res = block_XOR(state.A, state.B);

    byte and_B = MUX::byte_2(state.B, state.Y, bits.C0);
    byte and_res = block_AND(state.A, and_B);

    byte sr_res = block_SR(state.A, bits.E1, bits.E0);

    // Connect outputs from each block to MUX
    byte choices[8] = {
      DISCONNECTED,
      or_res,
      xor_res,
      and_res,
      sr_res,
      DISCONNECTED,
      DISCONNECTED,
      addsub_res
    };
    state.Y = MUX::byte_8(choices, bits.F2, bits.F1, bits.F0);

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

  byte block_SR(byte a, bit E1, bit E0) {
    byte lsr_res = 0;
    for (int i = 0; i < 7; i++) {
      _set_bit(&lsr_res, i, _get_bit(a, i + 1));
    }
     _set_bit(&lsr_res, 7, MUX::bit_2(0x0, _get_bit(a, 0), E0));

    byte rol_res = 0;
    for (int i = 0; i < 7; i++) {
      _set_bit(&rol_res, i + 1, _get_bit(a, i));
    }
     _set_bit(&rol_res, 0, _get_bit(a, 7));
    return MUX::byte_2(lsr_res, rol_res, E1);
  }
}