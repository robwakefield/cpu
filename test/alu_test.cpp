#include <gtest/gtest.h>
#include "../src/alu/alu.h"

TEST(ALUTest, ADD) {
  byte a = 12;
  byte b = 69;
  ASSERT_EQ(ALU::my6502(a, b, 0, OP_ADD).Y, a + b);

  a = -88;
  b = 34;
  ASSERT_EQ(ALU::my6502(a, b, 0, OP_ADD).Y, a + b);
}

TEST(ALUTest, SUB) {
  byte a = 12;
  byte b = 69;
  ASSERT_EQ(ALU::my6502(a, b, 0, OP_SUB).Y, b - a);

  a = -88;
  b = 34;
  ASSERT_EQ(ALU::my6502(a, b, 0, OP_SUB).Y, b - a);
}
