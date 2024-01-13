#include "mux.h"

using namespace gate;

namespace MUX {

  bit bit_2(bit a, bit b, bit S) {
    return OR(AND(a, NOT(S)), AND(b, S));
  }

  // S1 S0
  bit bit_4(bit a, bit b, bit c, bit d, bit S1, bit S0) {
    return bit_2(bit_2(a, b, S0), bit_2(c, d, S0), S1);
  }

}
