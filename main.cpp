#include "vector/include/vector.h"
#include <iostream>

int main()
{
    std::cout << "creating vector vec_1" << std::endl;
    Vector<int> vec_1;

    std::cout << "vec_1.push_back()" << std::endl;
    vec_1.push_back(1);

    
    return 0;
}