#include <iostream>
/*
Name: George Benyeogor
Assignment 1: 1D Cellular Automata
When given a current generation with values in an array, this 
program produces the next 49 generations by applying a given 
rule to each element of the current array.
*/


/**
 * This function converts the number to binary and fills the array with the binary
 * representation of the number; it also ensures that every element in the array 
 * is assigned a value. 
 *
 * @param num The rule set number.
 * @param array An 8 element int array to store the created rule set array. 
 */
void convertRuleSetNumberToRuleSetArray(int num, int* array){
    //Makes sure all values in the array are assigned a value
    for(int i = 0; i < 8; i++){
        array[i] = 0;
    }
    //Puts the binary representation of num in the array
    for (int i = 0; num > 0; i++)
    {
        array[i] = num % 2;
        num = num / 2;
    }
}

/**
 * This function prints a space for every 0 in the array and a '#' for every 1, 
 * then adds a single end line after outputting all the elements of the array.
 *
 * @param array  An int array holding 1s and 0s.
 * @param array_size An int specifying the length of the array.
 */
void displayGeneration(int* array, int array_size){
    for (int i = 0; i < array_size; i ++) {
        if(array[i] == 1){
            std::cout << "#";
        }
        else if (array[i] == 0){
            std::cout << " ";
        }
    }
std::cout << "\n";
}

/**
 * This function is converts a 3 digit binary number to an integer.
 *
 * @param left The left value being examined in the current generation array.
 * @param current The current value being examined in the current generation array.
 * @param right The right value being examined in the current generation array.
 * @return The int value of a 3 digit binary number.
 */
int convertNeighborhoodToIndex(int& left, int& current, int& right){
    int intVal = 0;
    intVal = (left * 4) + (current * 2) + (right * 1);
    return intVal;
}

/**
 * This function uses the current generation array and the rule set array to compute 
 * and set the values in the next generation array. 
 *
 * @param current_generation An int array of the current generation.
 * @param next_generation An int array of the next generation.
 * @param length_of_generation An int length of the generation array.
 * @param array_of_ruleset An int array of the rule set.
 */
void computeNextGeneration(int* current_generation, int* next_generation, 
int length_of_generation, int* array_of_ruleset){
next_generation[0] = current_generation[0];
next_generation[63] = current_generation[63];
for (int i = 1; i < length_of_generation - 1; i++)
{
        int index = convertNeighborhoodToIndex(current_generation[i - 1], current_generation[i], current_generation[i + 1]);
        next_generation[i] = array_of_ruleset[index];
}
}

int main() {

    int rule;
    std::cout << "Give me a rule from 0 to 255: ";

    //The rule the user gave
    std::cin >> rule;

    if (rule >= 0 && rule <= 255)
    {
        int rule_array[10] = {0};
        //Turns rule set int into binary. 
        convertRuleSetNumberToRuleSetArray(rule, rule_array);
        int current_generation[64] = {0};
        current_generation[32] = 1;
        int next_generation[64] = {0};
        displayGeneration(current_generation, 64);

        // Creates 49 generations
        for (int j = 0; j < 49; j++)
        {
            computeNextGeneration(current_generation, next_generation, 64, rule_array);
            for (int i = 0; i < 64; i++)
            {
                current_generation[i] = next_generation[i];
            }
            displayGeneration(current_generation, 64);
        }
    }
    else
    {
        std::cout << rule << " is not a valid rule.";
        return 0;
    }

  return 0;
}