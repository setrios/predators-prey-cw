#pragma once
#include "../../base_classes/plant.h"
#include "../../field.h"


class Grass : public Plant
{
private:
	Field* field;
public:
    Grass(Field* field, int x, int y, int value, int repr_chance) : Plant(x, y, value, repr_chance), field(field) { icon = "*"; }; // no need to init here, all inits are in Plant class (char)177

	virtual void spread() override;
};

