#include "gate.h"

namespace gate {

  bit BUF(bit in) {
    return in;
  }

  bit NOT(bit in) {
    return !in;
  }

  bit AND(bit a, bit b) {
    return a & b;
  }

  bit NAND(bit a, bit b) {
    return NOT(AND(a, b));
  }

  bit OR(bit a, bit b) {
    return a | b;
  }

  bit NOR(bit a, bit b) {
    return NOT(OR(a, b));
  }

  bit XOR(bit a, bit b) {
    return a != b;
  }

  bit XNOR(bit a, bit b) {
    return NOT(XOR(a, b));
  }

  // Chain (n_bits - 1) AND gates together
  bit AND_bits(bit bits[], int n_bits) {
    bit partial = 1;
    for (int i = 0; i < n_bits; i++) {
      partial = AND(partial, bits[i]);
    }
    return partial;
  }

  // Chain (n_bits - 1) OR gates together
  bit OR_bits(bit bits[], int n_bits) {
    bit partial = 0;
    for (int i = 0; i < n_bits; i++) {
      partial = OR(partial, bits[i]);
    }
    return partial;
  }
}
