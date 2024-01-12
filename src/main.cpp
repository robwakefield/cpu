#include "gate/gate.h"
#include "adder/adder.h"

#include <iostream>

int main() {
  const bit a = 0;
  const bit b = 1;

  std::cout << "A: " << a << " B: " << b << std::endl;
  std::cout << "BUF A: " << gate::BUF(a) << std::endl;
  std::cout << "NOT A: " << gate::NOT(a) << std::endl;
  std::cout << "A AND B: " << gate::AND(a, b) << std::endl;
  std::cout << "A OR B: " << gate::OR(a, b) << std::endl;
  std::cout << "A XOR B: " << gate::XOR(a, b) << std::endl;

  sum_carry res = adder::half(a, b);
  std::cout << "A H_ADD B: " << res.sum << " C: " << res.carry << std::endl;

  return 0;
}
