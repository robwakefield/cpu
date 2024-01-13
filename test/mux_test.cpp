#include <gtest/gtest.h>
#include "../src/mux/mux.h"

using namespace MUX;

TEST(MUXTest, bit_2) {
  for (bit a = 0; a == 0; a = !a) {
    for (bit b = 0; b == 0; b = !b) {
        ASSERT_EQ(bit_2(a, b, 0), a);
        ASSERT_EQ(bit_2(a, b, 1), b);
    }
  }
}

TEST(MUXTest, bit_4) {
  for (bit a = 0; a == 0; a = !a) {
    for (bit b = 0; b == 0; b = !b) {
      for (bit c = 0; c == 0; c = !c) {
        for (bit d = 0; d == 0; d = !d) {
          ASSERT_EQ(bit_4(a, b, c, d, 0, 0), a);
          ASSERT_EQ(bit_4(a, b, c, d, 0, 1), b);
          ASSERT_EQ(bit_4(a, b, c, d, 1, 0), c);
          ASSERT_EQ(bit_4(a, b, c, d, 1, 1), d);
        }
      }
    }
  }
}

TEST(MUXTest, byte_2) {
  for (byte a = -5; a < 5; a++) {
    for (byte b = -5; b < 5; b++) {
        ASSERT_EQ(byte_2(a, b, 0), a);
        ASSERT_EQ(byte_2(a, b, 1), b);
    }
  }
}

TEST(MUXTest, byte_4) {
  for (byte a = -5; a < 5; a++) {
    for (byte b = -5; b < 5; b++) {
      for (byte c = -5; c < 5; c++) {
        for (byte d = -5; d < 5; d++) {
          ASSERT_EQ(byte_4(a, b, c, d, 0, 0), a);
          ASSERT_EQ(byte_4(a, b, c, d, 0, 1), b);
          ASSERT_EQ(byte_4(a, b, c, d, 1, 0), c);
          ASSERT_EQ(byte_4(a, b, c, d, 1, 1), d);
        }
      }
    }
  }
}

TEST(MUXTest, byte_8) {
  for (byte a = -5; a < 5; a++) {
    for (byte b = -5; b < 5; b++) {
      for (byte c = -5; c < 5; c++) {
        for (byte d = -5; d < 5; d++) {
          byte choices[] = {a, b, c, d, a, b, c, d};
          ASSERT_EQ(byte_8(choices, 0, 0, 0), a);
          ASSERT_EQ(byte_8(choices, 0, 0, 1), b);
          ASSERT_EQ(byte_8(choices, 0, 1, 0), c);
          ASSERT_EQ(byte_8(choices, 0, 1, 1), d);
          ASSERT_EQ(byte_8(choices, 1, 0, 0), a);
          ASSERT_EQ(byte_8(choices, 1, 0, 1), b);
          ASSERT_EQ(byte_8(choices, 1, 1, 0), c);
          ASSERT_EQ(byte_8(choices, 1, 1, 1), d);
        }
      }
    }
  }
}
