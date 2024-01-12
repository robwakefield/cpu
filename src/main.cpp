#include "gate/gate.h"
#include "adder/adder.h"

#include <iostream>

int main() {
  const bit a = 1;
  const bit b = 1;
  const bit c = 1;

  std::cout << "A: " << a << " B: " << b << std::endl;
  std::cout << "BUF A: " << gate::BUF(a) << std::endl;
  std::cout << "NOT A: " << gate::NOT(a) << std::endl;
  std::cout << "A AND B: " << gate::AND(a, b) << std::endl;
  std::cout << "A OR B: " << gate::OR(a, b) << std::endl;
  std::cout << "A XOR B: " << gate::XOR(a, b) << std::endl;

  sum_carry h_res = adder::half(a, b);
  std::cout << "A H_ADD B = " << h_res.sum << " C: " << h_res.carry << std::endl;
  
  sum_carry f_res = adder::full(a, b, c);
  std::cout << "A F_ADD B, C = " << f_res.sum << " C: " << f_res.carry << std::endl;

  return 0;
}
