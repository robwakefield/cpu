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

  // Not implemented using logic gates to save time
  bit MUX_4(bit a, bit b, bit c, bit d, bit S0, bit S1) {
    switch ((S0 << 1) + S1) {
      case 0x00:
        return a;
      case 0x01:
        return b;
      case 0x10:
        return c;
      case 0x11:
        return d;
      default:
        return 0;
    }
  }
}
