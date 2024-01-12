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
}
