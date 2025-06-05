#pragma once
#include "../../base_classes/plant.h"
#include "../../field.h"

class Mushroom : public Plant
{
private:
	Field* field;
public:
    Mushroom(Field* field, int x, int y, int value, int repr_chance) : Plant(x, y, value, repr_chance), field(field) { icon = "o"; }; // no need to init here, all inits are in Plant class (char)177
	virtual void spread() override;
};

