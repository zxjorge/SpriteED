#include <iostream>

int* getIntPtr() {
    int number = 5;
    int* ptr = &number;
    return ptr;
}

int main()
{
    int *val = new int[4];
    int *same_mem = val;

    std::cout << val << " " << same_mem << std::endl;
    delete[] val;

    int *ptr = getIntPtr();
    std::cout << ptr << " " << *ptr << std::endl;
}