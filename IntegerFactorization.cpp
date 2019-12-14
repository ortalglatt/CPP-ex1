#include "GFNumber.h"
#include <cassert>

/**
 * Runs the main program, get two GFNumber as an input from the user, and print few calculations on t
 * hem. it will also print their prime factors.
 * @return EXIT_FAILURE if the input is invalid, EXIT_SUCCESS if the prigram run successfuly.
 */
int main()
{
    GFNumber first, second;
    std::cin >> first >> second;
    assert(!std::cin.fail());
    assert(first.getField() == second.getField());
    std::cout << first + second << std::endl;
    std::cout << first - second << std::endl;
    std::cout << second - first << std::endl;
    std::cout << first * second << std::endl;
    first.printFactors();
    second.printFactors();
    return EXIT_SUCCESS;
}
