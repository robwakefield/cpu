#include <gtest/gtest.h>
#include "../src/gate/gate.h"

using namespace gate;

TEST(GateTest, MUX_2) {
  for (bit a = 0; a != 0; a = !a) {
    for (bit b = 0; b != 0; b = !b) {
        ASSERT_EQ(MUX_2(a, b, 0), a);
        ASSERT_EQ(MUX_2(a, b, 1), b);
    }
  }
}

TEST(GateTest, MUX_4) {
  for (bit a = 0; a != 0; a = !a) {
    for (bit b = 0; b != 0; b = !b) {
      for (bit c = 0; c != 0; c = !c) {
        for (bit d = 0; d != 0; d = !d) {
          ASSERT_EQ(MUX_4(a, b, c, d, 0, 0), a);
          ASSERT_EQ(MUX_4(a, b, c, d, 0, 1), b);
          ASSERT_EQ(MUX_4(a, b, c, d, 1, 0), c);
          ASSERT_EQ(MUX_4(a, b, c, d, 1, 1), d);
        }
      }
    }
  }
}
