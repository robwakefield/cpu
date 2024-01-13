#include "../types.h"
#include "../helpers/helpers.h"
#include "../gate/gate.h"
#include "../mux/mux.h"

#ifndef ADDER_H
#define ADDER_H

struct sum_carry {
  bit sum;
  bit carry;
};

namespace adder {
  sum_carry half(bit, bit);
  sum_carry full(bit, bit, bit);
  byte ripple_8(byte, byte);
  byte addsub_8(byte, byte, bit);
}

#endif