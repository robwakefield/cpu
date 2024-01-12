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
