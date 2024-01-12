#include "../types.h"

#ifndef GATE_H
#define GATE_H

namespace gate {
  bit BUF(bit);
  bit NOT(bit);
  bit AND(bit, bit);
  bit NAND(bit, bit);
  bit OR(bit, bit);
  bit NOR(bit, bit);
  bit XOR(bit, bit);
  bit XNOR(bit, bit);

  bit MUX_2(bit, bit, bit);
  bit MUX_4(bit, bit, bit, bit, bit);
}

#endif