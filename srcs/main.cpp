#include "classes/SDL/SDL.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
int main(void)
{
    try
    {
        SDL instance;
        return (EXIT_SUCCESS);
    }
    catch (const std::exception &exception)
    {
        std::cerr << exception.what() << std::endl;
        return (EXIT_FAILURE);
    }
}