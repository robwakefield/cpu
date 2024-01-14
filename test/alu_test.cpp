#include <gtest/gtest.h>
#include "../src/alu/alu.h"

TEST(ALUTest, ADD) {
  byte a = 12;
  byte b = 69;
  EXPECT_EQ(ALU::my6502(a, b, 0, OP_ADD).Y, a + b);

  a = -88;
  b = 34;
  EXPECT_EQ(ALU::my6502(a, b, 0, OP_ADD).Y, a + b);
}

TEST(ALUTest, SUB) {
  byte a = 12;
  byte b = 69;
  EXPECT_EQ(ALU::my6502(a, b, 0, OP_SUB).Y, b - a);

  a = -88;
  b = 34;
  EXPECT_EQ(ALU::my6502(a, b, 0, OP_SUB).Y, b - a);
}

TEST(ALUTest, AND) {
  byte a = 0xFF;
  byte b = 0xFF;
  byte exp = 0xFF;
  EXPECT_EQ(ALU::my6502(a, b, 0, OP_AND).Y, exp);

  a = 0x0F;
  b = 0xF0;
  exp = 0x00;
  EXPECT_EQ(ALU::my6502(a, b, 0, OP_AND).Y, exp);
}

TEST(ALUTest, OR) {
  byte a = 0xFF;
  byte b = 0xFF;
  byte exp = 0xFF;
  EXPECT_EQ(ALU::my6502(a, b, 0, OP_OR).Y, exp);

  a = 0x0F;
  b = 0xF0;
  exp = 0xFF;
  EXPECT_EQ(ALU::my6502(a, b, 0, OP_OR).Y, exp);
}

TEST(ALUTest, XOR) {
  byte a = 0xFF;
  byte b = 0xFF;
  byte exp = 0x00;
  EXPECT_EQ(ALU::my6502(a, b, 0, OP_XOR).Y, exp);

  a = 0x1F;
  b = 0xF1;
  exp = 0xEE;
  EXPECT_EQ(ALU::my6502(a, b, 0, OP_XOR).Y, exp);
}

TEST(ALUTest, INC) {
  byte a = 0xF3;
  byte exp = 0xF4;
  EXPECT_EQ(ALU::my6502(a, 0x0, 0, OP_INC).Y, exp);

  a = 0xFF;
  exp = 0x00;
  EXPECT_EQ(ALU::my6502(a, 0x0, 0, OP_INC).Y, exp);
}

TEST(ALUTest, DEC) {
  byte a = 0xF3;
  byte exp = 0xF2;
  EXPECT_EQ(ALU::my6502(a, 0x0, 0, OP_DEC).Y, exp);

  a = 0x00;
  exp = 0xFF;
  EXPECT_EQ(ALU::my6502(a, 0x0, 0, OP_DEC).Y, exp);
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
  EXPECT_EQ(ALU::my6502(a, 0x0, 0, OP_ASL).Y, exp);
}

TEST(ALUTest, LSR) {
  byte a =   0b00010111;
  byte exp = 0b00001011;
  EXPECT_EQ(ALU::my6502(a, 0x0, 0, OP_LSR).Y, exp);
}

TEST(ALUTest, ROR) {
  byte a =   0b00010111;
  byte exp = 0b10001011;
  EXPECT_EQ(ALU::my6502(a, 0x0, 0, OP_ROR).Y, exp);
}

TEST(ALUTest, ROL) {
  byte a =   0b10010111;
  byte exp = 0b00101111;
  EXPECT_EQ(ALU::my6502(a, 0x0, 0, OP_ROL).Y, exp);
}

TEST(ALUTest, Z_logic) {
  EXPECT_EQ(ALU::Z_logic(0b00000000), 1);
  EXPECT_EQ(ALU::Z_logic(0b00001000), 0);
  EXPECT_EQ(ALU::Z_logic(0b11111111), 0);
}

TEST(ALUTest, C_logic) {
  EXPECT_EQ(ALU::C_logic(0, 0, 0, OP_ADD), 0);
  EXPECT_EQ(ALU::C_logic(1, 0, 0, OP_AND), 1);
  EXPECT_EQ(ALU::C_logic(0, 1, 0, OP_ADD), 1);
  EXPECT_EQ(ALU::C_logic(0, 0, 1, OP_ADD), 0);
  EXPECT_EQ(ALU::C_logic(0, 0, 1, OP_LSR), 1);
}

TEST(ALUTest, S_logic) {
  alu_op ops[4] = {OP_ADD, OP_OR, OP_XOR, OP_AND};
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(ALU::S_logic(0, 0b00000000, ops[i]), 0);
    EXPECT_EQ(ALU::S_logic(0, 0b11111111, ops[i]), 1);
  }
  EXPECT_EQ(ALU::S_logic(0, 0b11111111, OP_ROR), 0);
  EXPECT_EQ(ALU::S_logic(1, 0b00000000, OP_ROL), 1);
}

TEST(ALUTest, O_logic) {
  EXPECT_EQ(ALU::O_logic(0, 0, 0, 0, OP_ADD), 0);
  EXPECT_EQ(ALU::O_logic(0, 100, 28, -128, OP_ADD), 1);
  EXPECT_EQ(ALU::O_logic(0, -100, -29, 1, OP_ADD), 1);
  EXPECT_EQ(ALU::O_logic(0, 100, 29, -128, OP_ROL), 0);
}

TEST(ALUTest, StatusBits) {
  // Check overflow flag set
  status_reg status = ALU::my6502(100, 100, 0, OP_ADD).status;
  ASSERT_TRUE(status.overflow);
  // Check zero flag set
  status = ALU::my6502(-1, 0, 0, OP_INC).status;
  ASSERT_TRUE(status.zero);
  // Check sign flag set
  status = ALU::my6502(10, 3, 0, OP_SUB).status;
  ASSERT_TRUE(status.sign);
}
