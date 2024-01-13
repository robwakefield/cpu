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

TEST(ALUTest, AND) {
  byte a = 0xFF;
  byte b = 0xFF;
  byte exp = 0xFF;
  ASSERT_EQ(ALU::my6502(a, b, 0, OP_AND).Y, exp);

  a = 0x0F;
  b = 0xF0;
  exp = 0x00;
  ASSERT_EQ(ALU::my6502(a, b, 0, OP_AND).Y, exp);
}

TEST(ALUTest, OR) {
  byte a = 0xFF;
  byte b = 0xFF;
  byte exp = 0xFF;
  ASSERT_EQ(ALU::my6502(a, b, 0, OP_OR).Y, exp);

  a = 0x0F;
  b = 0xF0;
  exp = 0xFF;
  ASSERT_EQ(ALU::my6502(a, b, 0, OP_OR).Y, exp);
}

TEST(ALUTest, XOR) {
  byte a = 0xFF;
  byte b = 0xFF;
  byte exp = 0x00;
  ASSERT_EQ(ALU::my6502(a, b, 0, OP_XOR).Y, exp);

  a = 0x1F;
  b = 0xF1;
  exp = 0xEE;
  ASSERT_EQ(ALU::my6502(a, b, 0, OP_XOR).Y, exp);
}
