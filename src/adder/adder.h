#include "../types.h"
#include "../gate/gate.h"

#ifndef ADDER_H
#define ADDER_H

struct sum_carry {
  bit sum;
  bit carry;
};

namespace adder {
  sum_carry half(bit, bit);
}

#endif