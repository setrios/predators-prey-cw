#pragma once
#include "../../type/prey.h"
#include "../../field.h"


class Bunny : public Prey {
private:
    Field* field;
public:
    Bunny(Field* field, int x, int y, int age, int death_age, int speed, int fov, int hunger, int value, int repr_age, int repr_chance, int get_hungry_at) : Prey(field, x, y, age, death_age, speed, fov, hunger, value, repr_age, repr_chance, get_hungry_at), field(field)
    {
        icon = "B";
    }

    bool isBig() override { return false; }

    void tryReproduce() override 
    {
        bool is_in_normal_state = state->getStateName()[0] == 'N';
        if (is_in_normal_state && rand() % 100 < reproduction_chance && age >= reproduction_age) // if in normal state and reproduction chance
        {
            int newX = x + (rand() % 3 - 1);
            int newY = y + (rand() % 3 - 1);

            if (newX >= 0 && newX < field->getSizeX() && newY >= 0 && newY < field->getSizeY() && field->findPreyByCoords(newX, newY) == nullptr) 
            {
                int Age = 0;
                int newSpeed = speed + (rand() % 3 - 1);
                int newFov = fov + (rand() % 3 - 1);
                int newHunger = 30;

                field->addPrey<Bunny>(field, newX, newY, Age, death_age, newSpeed, newFov, newHunger, value, reproduction_age, reproduction_chance, get_hungry_at);
            }
        }
    }
};
