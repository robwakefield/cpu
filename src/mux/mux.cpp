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

  byte byte_2(byte a, byte b, bit S) {
    byte out = 0;
    for (int i = 0; i < 8; i++) {
      bit y = bit_2(_get_bit(a, i), _get_bit(b, i), S);
      _set_bit(&out, i, y);
    }
    return out;
  }

  // S1 S0
  byte byte_4(byte a, byte b, byte c, byte d, bit S1, bit S0) {
    return byte_2(byte_2(a, b, S0), byte_2(c, d, S0), S1);
  }

  // S2 S1 S0
  byte byte_8(byte choices[], bit S2, bit S1, bit S0) {
    return byte_2(
        byte_4(choices[0], choices[1], choices[2], choices[3], S1, S0),
        byte_4(choices[4], choices[5], choices[6], choices[7], S1, S0), S2);
  }

}
