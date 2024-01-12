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
  
}
