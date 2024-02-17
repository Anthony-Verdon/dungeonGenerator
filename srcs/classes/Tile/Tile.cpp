#include "Tile.hpp"
#include <iostream>
#include <map>
#include <memory>
#include "../../globals.hpp"
Tile::Tile(const std::shared_ptr<Texture> &newTexture)
{
    texture = newTexture;
}

Tile::~Tile()
{
}

Tile::Tile(const Tile &copy) : texture(copy.getTexture())
{
    *this = copy;
}
Tile &Tile::operator=(const Tile &copy)
{
    if (&copy != this)
    {
        texture = copy.getTexture();
        id = copy.getID();
        for (int i = 0; i < 4; i++)
            possibleNeighbors[i] = copy.getPossibleNeighbors(i);
    }
    return (*this);
}

std::shared_ptr<Texture> Tile::getTexture() const
{
    return texture;
}

int Tile::getID() const
{
    return id;
}

std::vector<int> Tile::getPossibleNeighbors(int direction) const
{
    return (possibleNeighbors[direction]);
}

void Tile::setTexture(std::shared_ptr<Texture> instance)
{
    texture = instance;
}

void Tile::setID(int newID)
{
    id = newID;
}

void Tile::addPossibleNeighbors(int direction, int newNeighbor)
{
    possibleNeighbors[direction].push_back(newNeighbor);
}

std::ostream &operator<<(std::ostream &os, const Tile &instance)
{
    os << "Texture path: " + instance.getTexture()->getPath() << std::endl;
    os << "Tile ID:" << instance.getID() << std::endl;
    for (int i = 0; i < 4; i++)
    {
        os << directionsPossibilityArray[i] << ": ";
        std::vector<int> possibleNeighbors = instance.getPossibleNeighbors(i);
        for (auto it = possibleNeighbors.begin(); it != possibleNeighbors.end(); it++)
            os << *it << " ";
        os << std::endl;
    }
    return os;
}