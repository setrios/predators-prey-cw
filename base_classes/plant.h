#pragma once
class Plant
{
protected:
	int x, y;
	int health;
	int value; // how much hunger it gives to prey
	int reproduction_chance; // 0 - 100 
	const char* icon;

public:
	Plant(int x, int y, int value, int repr_chance) : x(x), y(y), health(1), value(value),reproduction_chance(repr_chance){};
	~Plant() = default;
	
	virtual void spread() = 0;

	int getX() { return x; }
	int getY() { return y; }
	int getValue() { return value; }
	const char* getIcon() { return icon; }
};

