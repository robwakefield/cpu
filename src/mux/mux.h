#include "../types.h"
#include "../helpers/helpers.h"
#include "../gate/gate.h"

#ifndef MUX_H
#define MUX_H

namespace MUX {
  bit bit_2(bit, bit, bit);
  bit bit_4(bit, bit, bit, bit, bit, bit);

  byte byte_2(byte, byte, bit);
  byte byte_4(byte, byte, byte, byte, bit, bit);
}

#endif