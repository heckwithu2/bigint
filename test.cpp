#include <iostream>
#include "bigint.hpp"

int main(int argc, char* argv[]) {

    int x = 000;
    int x1 = 111;
    long long x4 = 222;

    bigint Jeremiah(x);
    std::cout << Jeremiah;
    Jeremiah = x1;
    std::cout << Jeremiah;
    Jeremiah = x4;
    std::cout << Jeremiah;
}
