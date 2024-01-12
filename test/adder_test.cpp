#include <gtest/gtest.h>
#include "../src/adder/adder.h"

using namespace adder;

bool sc_equal(sum_carry a, sum_carry b) {
  return a.sum == b.sum && a.carry == b.carry;
}

TEST(AdderTest, HalfAdder) {
  bit sums[2][2] = {{0, 1}, {1, 0}};
  bit carrys[2][2] = {{0, 0}, {0, 1}};

  for (bit a = 0; a != 0; a = !a) {
    for (bit b = 0; b != 0; b = !b) {
      sum_carry exp = {
        .sum =  sums[a][b],
        .carry = carrys[a][b]
      };
      sum_carry res = half(a, b);
      ASSERT_TRUE(sc_equal(res, exp)) << "Input: " << a << b << " res: " << res.sum << res.carry;
    }
  }
  
}

TEST(AdderTest, FullAdder) {
  bit sums[2][2][2] = {{{0, 1}, {1, 0}}, {{1, 0}, {0, 1}}};
  bit carrys[2][2][2] = {{{0, 0}, {0, 1}}, {{0, 1}, {1, 1}}};

  for (bit a = 0; a != 0; a = !a) {
    for (bit b = 0; b != 0; b = !b) {
      for (bit c = 0; c != 0; c = !c) {
        sum_carry exp = {
          .sum =  sums[a][b][c],
          .carry = carrys[a][b][c]
        };
        sum_carry res = full(a, b, c);
        ASSERT_TRUE(sc_equal(res, exp)) << "Input: " << a << b << c << " res: " << res.sum << res.carry;
      }
    }
  }
  
}

TEST(AdderTest, Ripple8AdderPositive) {
  for (byte a = -128; a < 127; a++) {
    for (byte b = -128; b < 127; b++) {
      if (a + b >= 0 && a + b < 128) {
        ASSERT_EQ(ripple_8(a, b), a + b);
      }
    }
  }
}

TEST(AdderTest, Ripple8AdderNegative) {
  for (byte a = -128; a < 127; a++) {
    for (byte b = -128; b < 127; b++) {
      if (a + b <= 0 && a + b >= -128) {
        ASSERT_EQ(ripple_8(a, b), a + b);
      }
    }
  }
}

TEST(AdderTest, Ripple8AdderOverflow) {
    byte a = 127;
    byte b = 1;
    ASSERT_EQ(ripple_8(a, b), -128);
}

TEST(AdderTest, Ripple8AdderUnderflow) {
    byte a = -128;
    byte b = -1;
    ASSERT_EQ(ripple_8(a, b), 127);
}