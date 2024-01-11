#include <iostream>

namespace gate {

  bool BUF(bool in) {
    return in;
  }

  bool NOT(bool in) {
    return !in;
  }

  bool AND(bool a, bool b) {
    return a & b;
  }

  bool NAND(bool a, bool b) {
    return NOT(AND(a, b));
  }

  bool OR(bool a, bool b) {
    return a | b;
  }

  bool NOR(bool a, bool b) {
    return NOT(OR(a, b));
  }

  bool XOR(bool a, bool b) {
    return a != b;
  }

  bool XNOR(bool a, bool b) {
    return NOT(XOR(a, b));
  }
}

int main() {
  const bool a = 0;
  const bool b = 1;

  std::cout << "A: " << a << " B: " << b << std::endl;
  std::cout << "BUF A: " << gate::BUF(a) << std::endl;
  std::cout << "NOT A: " << gate::NOT(a) << std::endl;
  std::cout << "A AND B: " << gate::AND(a, b) << std::endl;
  std::cout << "A OR B: " << gate::OR(a, b) << std::endl;
  std::cout << "A XOR B: " << gate::XOR(a, b) << std::endl;

  return 0;
}
