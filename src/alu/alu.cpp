#include "alu.h"

using namespace gate;

namespace ALU {
  ALU_state my6502(byte a, byte b, bit carry_in, alu_op opcode) {
    ALU_state state = {
      .opcode = opcode,
      .carry_in = carry_in,
      .A = a,
      .B = b,
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

    // Set status register flags

    state.status.zero = Z_logic(state.Y);
    // TODO: Get carry from ADD and SR blocks
    //state.status.carry = C_logic(state.status.carry, add_c, sr_c, state.opcode);
    state.status.sign = S_logic(state.status.sign, state.Y, state.opcode);
    state.status.overflow = O_logic(state.status.overflow, state.A, state.B, state.Y, state.opcode);

    return state;
  }

  byte block_AND(byte a, byte b) {
    byte out;
    for (int i = 0; i < 8; i++) {
      bit bit_a = _get_bit(a, i);
      bit bit_b = _get_bit(b, i);
      _set_bit(&out, i, AND(bit_a, bit_b));
    }
    return out;
  }

  byte block_OR(byte a, byte b) {
    byte out;
    for (int i = 0; i < 8; i++) {
      bit bit_a = _get_bit(a, i);
      bit bit_b = _get_bit(b, i);
      _set_bit(&out, i, OR(bit_a, bit_b));
    }
    return out;
  }

  byte block_XOR(byte a, byte b) {
    byte out;
    for (int i = 0; i < 8; i++) {
      bit bit_a = _get_bit(a, i);
      bit bit_b = _get_bit(b, i);
      _set_bit(&out, i, XOR(bit_a, bit_b));
    }
    return out;
  }

  byte block_SR(byte a, bit E1, bit E0) {
    byte lsr_res;
    for (int i = 0; i < 7; i++) {
      _set_bit(&lsr_res, i, _get_bit(a, i + 1));
    }
     _set_bit(&lsr_res, 7, MUX::bit_2(0x0, _get_bit(a, 0), E0));

    byte rol_res;
    for (int i = 0; i < 7; i++) {
      _set_bit(&rol_res, i + 1, _get_bit(a, i));
    }
     _set_bit(&rol_res, 0, _get_bit(a, 7));
    return MUX::byte_2(lsr_res, rol_res, E1);
  }

  bit is_ADD(alu_op op) {
    // Get MUX bits that code for BLOCK type
    bit block_bits[3];
    for (int i = 0; i < 3; i++) {
      block_bits[i] = _get_bit(op, i);
    }
    // ADD = 0b111
    return gate::AND_bits(block_bits, 3);
  }

  bit is_SR(alu_op op) {
    // Get MUX bits that code for BLOCK type
    bit block_bits[3];
    for (int i = 0; i < 3; i++) {
      block_bits[i] = _get_bit(op, i);
    }
    // SR = 0b100
    bit inverted[3] = {
      gate::NOT(block_bits[0]),
      gate::NOT(block_bits[1]),
      block_bits[2]
    };
   return gate::AND_bits(inverted, 3);
  }

  bit is_AND(alu_op op) {
    // Get MUX bits that code for BLOCK type
    bit block_bits[3];
    for (int i = 0; i < 3; i++) {
      block_bits[i] = _get_bit(op, i);
    }
    // AND = 0b011
    bit inverted[3] = {
      block_bits[0],
      block_bits[1],
      gate::NOT(block_bits[2])
    };
   return gate::AND_bits(inverted, 3);
  }

  bit is_OR(alu_op op) {
    // Get MUX bits that code for BLOCK type
    bit block_bits[3];
    for (int i = 0; i < 3; i++) {
      block_bits[i] = _get_bit(op, i);
    }
    // OR = 0b001
    bit inverted[3] = {
      block_bits[0],
      gate::NOT(block_bits[1]),
      gate::NOT(block_bits[2])
    };
   return gate::AND_bits(inverted, 3);
  }

  bit is_XOR(alu_op op) {
    // Get MUX bits that code for BLOCK type
    bit block_bits[3];
    for (int i = 0; i < 3; i++) {
      block_bits[i] = _get_bit(op, i);
    }
    // XOR = 0b010
    bit inverted[3] = {
      gate::NOT(block_bits[0]),
      block_bits[1],
      gate::NOT(block_bits[2])
    };
   return gate::AND_bits(inverted, 3);
  }

  // Set on every operation
  bit Z_logic(byte Y) {
    // Split 8 bit bus into individual wires
    bit bits[8];
    for (int i = 0; i < 8; i++)
    {
      bits[i] = _get_bit(Y, i);
    }
    // NOT(OR(All bits of Y))
    return gate::NOT(gate::OR_bits(bits, 8));
  }

  // Set on ADD, SR operations
  bit C_logic(bit c, bit add_c, bit sr_c, alu_op op) {
    bit is_SR_bit = is_SR(op);
    bit is_ADD_or_SR = gate::OR(is_ADD(op), is_SR_bit);
    // Choose which carry to set
    bit new_c = MUX::bit_2(add_c, sr_c, is_SR_bit);
    // Only set new value if ADD or SR
    return MUX::bit_2(c, new_c, is_ADD_or_SR);
  }

  // Set on ADD, XOR, OR, AND operations
  bit S_logic(bit s, byte Y, alu_op op) {
    bit blocks[] = {is_ADD(op), is_XOR(op), is_OR(op), is_AND(op)};
    bit is_valid_block = gate::OR_bits(blocks, 4);
    bit is_neg = _get_bit(Y, 7);
    return MUX::bit_2(s, is_neg, is_valid_block);
  }

  // Set on ADD operations
  bit O_logic(bit o, byte A, byte B, byte Y, alu_op op) {
    bit sign_y = _get_bit(Y, 7);
    // Case 1: Pos A, B -> Neg Y
    bit both_pos = gate::NOR(_get_bit(A, 7), _get_bit(B, 7));
    bit o_pos = gate::AND(both_pos, sign_y);
    // Case 2: Neg A, B -> Pos Y
    bit both_neg = gate::AND(_get_bit(A, 7), _get_bit(B, 7));
    bit o_neg = gate::AND(both_neg, gate::NOT(sign_y));
    // Set o bit if either case is true
    bit o_new = gate::OR(o_pos, o_neg);
    // Only set if as a result of an ADD
    return MUX::bit_2(o, o_new, is_ADD(op));
  }
}