#pragma once
#include "../../type/predator.h"
#include "../../type/prey.h"
#include "../../field.h"

class Fox : public Predator 
{
private:
    Field* field;
public:
    Fox(Field* field, int x, int y, int age, int death_age, int speed, int fov, int hunger, int value, int repr_age, int repr_chance, int get_hungry_at) : Predator(field, x, y, age, death_age, speed, fov, hunger, value, repr_age, repr_chance, get_hungry_at), field(field) 
    {
        icon = "F";
    }
    bool isBig() override { return false; }
    void tryReproduce() override;
};

