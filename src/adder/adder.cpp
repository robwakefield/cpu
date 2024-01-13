#include "adder.h"

using namespace gate;

namespace adder {

  sum_carry half(bit a, bit b) {
    sum_carry res;
    res.sum = XOR(a, b);
    res.carry = AND(a, b);
    return res;
  }

  sum_carry full(bit a, bit b, bit c) {
    sum_carry res;
    bit xor_a_b = XOR(a, b);
    res.sum = XOR(xor_a_b, c);
    res.carry = OR(AND(a, b), AND(c, xor_a_b));
    return res;
  }

  // Equivalent to branching off correct wire in 8bit bus
  bit _get_bit(byte b, int i) {
    return (b >> i) & 1;
  }

  // Equivalent to putting a bit onto the correct wire in 8bit bus
  void _set_bit(byte* b, int i, bit s) {
    if (s) {
      *b |= 1 << i;
    } else {
      *b &= ~(1 << i);
    }
  }

  byte ripple_8(byte a, byte b) {
    byte sum = 0;

    bit c = 0;
    for (int i = 0; i < 8; i++) {
      bit bit_a = _get_bit(a, i);
      bit bit_b = _get_bit(b, i);
      sum_carry res = full(bit_a, bit_b, c);
      _set_bit(&sum, i, res.sum);
      c = res.carry;
    }

    return sum;
  }

  // If control bit D = 1, subtracts A from B
  byte addsub_8(byte a, byte b, bit D) {
    byte sum = 0;

    bit c = D;
    for (int i = 0; i < 8; i++) {
      bit bit_a = _get_bit(a, i);
      bit bit_b = _get_bit(b, i);
      bit bit_m = MUX::bit_2(bit_a, NOT(bit_a), D);

      sum_carry res = full(bit_m, bit_b, c);
      _set_bit(&sum, i, res.sum);
      c = res.carry;
    }

    return sum;
  }
  
}
