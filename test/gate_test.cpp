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
