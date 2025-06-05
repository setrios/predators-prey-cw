#include "fox.h"

void Fox::tryReproduce() 
{
    bool is_in_normal_state = state->getStateName()[0] == 'N';
    if (is_in_normal_state && rand() % 100 < reproduction_chance && age >= reproduction_age) // if in normal state and 10% chance
    {
        int newX = x + (rand() % 3 - 1);
        int newY = y + (rand() % 3 - 1);

        if (newX >= 0 && newX < field->getSizeX() && newY >= 0 && newY < field->getSizeY() && field->findPredatorByCoords(newX, newY) == nullptr) 
        {
            int Age = 0;
            int newSpeed = speed + (rand() % 3 - 1);
            int newFov = fov + (rand() % 3 - 1);
            int newHunger = 40;

            field->addPredator<Fox>(field, newX, newY, Age, death_age, newSpeed, newFov, newHunger, value, reproduction_age, reproduction_chance, get_hungry_at);
        }
    }
}
