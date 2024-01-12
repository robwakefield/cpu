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

  bit MUX_2(bit a, bit b, bit S) {
    return OR(AND(a, NOT(S)), AND(b, S));
  }

  // S1 S0
  bit MUX_4(bit a, bit b, bit c, bit d, bit S1, bit S0) {
    return MUX_2(MUX_2(a, b, S0), MUX_2(c, d, S0), S1);
  }
}
