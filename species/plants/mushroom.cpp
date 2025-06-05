#include "mushroom.h"


void Mushroom::spread()
{
    int fieldSizeX = field->getSizeX();
    int fieldSizeY = field->getSizeY();

    if (rand() % 100 < reproduction_chance) // 20% chance to grow
    {

        // gen shift
        int dx = (rand() % 3) - 1;  // -1, 0, 1
        int dy = (rand() % 3) - 1;  // -1, 0, 1

        // new coords
        int newX = x + dx;
        int newY = y + dy;

        // if out of field - growth attempt failed
        if (newX < 0 || newX >= fieldSizeX ||
            newY < 0 || newY >= fieldSizeY)
        {
            return;
        }

        // if occupied - growth attempt failed
        if (field->findPlantByCoords(newX, newY) == nullptr)
        {
            field->addPlant<Mushroom>(field, newX, newY, value, reproduction_chance);
            return;
        }

    }
}