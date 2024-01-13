  #include "helpers.h"
  
  // Equivalent to branching off correct wire in 8bit bus
  bit _get_bit(byte b, int i) {
    return (b >> i) & 1;
  }

  // Equivalent to putting a bit onto the correct wire in 8bit bus
  void _set_bit(byte* b, int i, bit s) {
    if (s) {
      *b |= 1 << i;
    } else {
      *b &= ~(1 << i);
    }
  }
