#include <vector>
#include "Structure/Node_Nonlinear.hpp"
#include "Normal_Algorithm/Linear/Legal_Pop.hpp"
#include "Normal_Algorithm/Linear/Select_Sort.hpp"
#include "Structure/Deque_Circle.hpp"


int main() {
    std::cout << Legal_4Stack(std::vector<int>{3, 1, 2,  4, 5}) << std::endl;
    printf("Debug Hook");
}