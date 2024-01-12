#include "adder.h"

namespace adder {

  sum_carry half(bit a, bit b) {
    sum_carry res;
    res.sum = gate::XOR(a, b);
    res.carry = gate::AND(a, b);
    return res;
  }
  
}
