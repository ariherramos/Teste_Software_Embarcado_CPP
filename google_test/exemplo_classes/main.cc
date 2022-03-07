#include "addition.h"
#include "multiply.h"

#include <iostream>

int main()
{
    int x = 4;
    int y = 5;

    int z1 = Addition::twoValues(x,y);
    std::cout << "\nAddition Result: " << z1 << std::endl;

    int z2 = Multiply::twoValues(x,y);
    std::cout << "Multiply Result: " << z2 << std::endl;

    return 0;
}

