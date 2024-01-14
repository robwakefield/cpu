#include "../types.h"
#include "../helpers/helpers.h"

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

  bit AND_bits(bit[], int);
  bit OR_bits(bit[], int);
}

#endif