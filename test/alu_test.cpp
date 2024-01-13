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

TEST(ALUTest, INC) {
  byte a = 0xF3;
  byte exp = 0xF4;
  ASSERT_EQ(ALU::my6502(a, 0x0, 0, OP_INC).Y, exp);

  a = 0xFF;
  exp = 0x00;
  ASSERT_EQ(ALU::my6502(a, 0x0, 0, OP_INC).Y, exp);
}

TEST(ALUTest, DEC) {
  byte a = 0xF3;
  byte exp = 0xF2;
  ASSERT_EQ(ALU::my6502(a, 0x0, 0, OP_DEC).Y, exp);

  a = 0x00;
  exp = 0xFF;
  ASSERT_EQ(ALU::my6502(a, 0x0, 0, OP_DEC).Y, exp);
}

TEST(ALUTest, CMP) {

}

TEST(ALUTest, CPX) {

}

TEST(ALUTest, CPY) {

}

TEST(ALUTest, BIT) {

}

TEST(ALUTest, ASL) {
  byte a =   0b00010111;
  byte exp = 0b00101110;
  ASSERT_EQ(ALU::my6502(a, 0x0, 0, OP_ASL).Y, exp);
}

TEST(ALUTest, LSR) {
  byte a =   0b00010111;
  byte exp = 0b00001011;
  ASSERT_EQ(ALU::my6502(a, 0x0, 0, OP_LSR).Y, exp);
}

TEST(ALUTest, ROR) {
  byte a =   0b00010111;
  byte exp = 0b10001011;
  ASSERT_EQ(ALU::my6502(a, 0x0, 0, OP_ROR).Y, exp);
}

TEST(ALUTest, ROL) {
  byte a =   0b10010111;
  byte exp = 0b00101111;
  ASSERT_EQ(ALU::my6502(a, 0x0, 0, OP_ROL).Y, exp);
}
