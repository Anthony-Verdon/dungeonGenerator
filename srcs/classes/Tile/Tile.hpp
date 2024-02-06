#pragma once

#include "../Texture/Texture.hpp"
#include <memory>
enum e_Direction
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

class Tile
{
  private:
    std::shared_ptr<Texture> texture;
    int id;
    std::vector<int> possibleNeighbors[4];

  public:
    Tile(const std::shared_ptr<Texture> &texture);
    Tile(const Tile &copy);
    Tile &operator=(const Tile &copy);
    ~Tile();

    std::shared_ptr<Texture> getTexture() const;
    int getID() const;
    std::vector<int> getPossibleNeighbors(int direction) const;

    void setTexture(std::shared_ptr<Texture> instance);
    void setID(int newID);
    void addPossibleNeighbors(int direction, int newNeighbor);
};

std::ostream &operator<<(std::ostream &os, const Tile &instance);