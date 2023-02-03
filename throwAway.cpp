#include <iostream>

/**
 * This function converts the number to binary and fills the array with the binary
 * representation of the number; it also ensures that every element in the array
 * is assigned a value.
 *
 * @param num The rule set number.
 * @param array An 8 element int array to store the created rule set array.
 */
void convertRuleSetNumberToRuleSetArray(int num, int array[8])
{
    for (int i = 0; i < 8; i++)
    {
        array[i] = 0;
    }
    for (int i = 0; num > 0; i++)
    {
        array[i] = num % 2;
        num = num / 2;
    }
}

int main(int argc, char **argv)
{
    bool f = "hello" == "hello";
    if (f)
        std::cout << "yes" << "\n";
    else
        std::cout << "no" << "\n";
}