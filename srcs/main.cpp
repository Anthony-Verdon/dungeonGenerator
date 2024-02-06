#include "classes/DungeonGenerator/DungeonGenerator.hpp"
#include "classes/SDL/SDL.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

int main(void)
{
    try
    {
        t_map mapGenerated = DungeonGenerator::generate(5, 5, "");
        std::cout << mapGenerated << std::endl;
        SDL instance;

        instance.updateLoop(mapGenerated);
        return (EXIT_SUCCESS);
    }
    catch (std::exception exception)
    {
        std::cerr << exception.what() << std::endl;
        return (EXIT_FAILURE);
    }
}