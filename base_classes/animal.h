#pragma once
#include <vector>

class Animal
{
protected: // to get access from heirs
	int x, y;
	int age;
	int death_age;
	int speed;
	int fov;
	int hunger;
	int value; // how much hunger it gives to predator
	int reproduction_age;
	int reproduction_chance; // 0 - 100 
	int get_hungry_at;
	const char* icon;
	const std::vector<std::pair<int, int>> directions = {
		{-1,  0},  // Up
		{ 1,  0},  // Down
		{ 0, -1},  // Left
		{ 0,  1},  // Right
		{-1, -1},  // Up-left
		{-1,  1},  // Up-right
		{ 1, -1},  // Down-left
		{ 1,  1}   // Down-right
	};

public:
	Animal(int usr_x, int usr_y, int usr_age, int usr_death_age, int usr_speed, int usr_fov, int usr_hunger, int usr_value, int usr_repr_age, int usr_repr_chance, int usr_get_hungry_at)
	{
		x = usr_x;
		y = usr_y;
		age = usr_age;
		death_age = usr_death_age;
		speed = usr_speed;
		fov = usr_fov;
		hunger = usr_hunger;
		value = usr_value;
		reproduction_age = usr_repr_age;
		reproduction_chance = usr_repr_chance;
		get_hungry_at = usr_get_hungry_at;
	};

	// virtual to indicate that these functions can be overridden in the derived classes
	virtual void move() = 0; // = 0 to make overridde obligatorily in next clsasses
	virtual void eat() = 0;
	virtual void lookForFood() = 0;
	virtual void tryReproduce() = 0;

	int getX() { return x; }
	int getY() { return y; }
	int getAge() { return age; }
	int getDeathAge() { return death_age; }
	int getFov() const { return fov; }
	int getHunger() { return hunger; }
	int gethungryAt() { return get_hungry_at; }
	int getValue() { return value; }
	int getReprAge() { return reproduction_age; }
	int getReprChance() { return reproduction_chance; }
	const char* getIcon() { return icon; }
	virtual bool isPrey() { return false; }
};




