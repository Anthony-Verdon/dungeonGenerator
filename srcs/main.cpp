#include "classes/DungeonGenerator/DungeonGenerator.hpp"
#include "classes/SDL/SDL.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

int main(void)
{
    try
    {
        std::cout << DungeonGenerator::generate(10, 10, "") << std::endl;

        SDL instance;

        // instance.updateLoop();
        return (EXIT_SUCCESS);
    }
    catch (std::exception exception)
    {
        std::cerr << exception.what() << std::endl;
        return (EXIT_FAILURE);
    }
}