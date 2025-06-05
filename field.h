#pragma once
#include <cstdlib> // for rand()
#include <vector>
#include <memory> // for std::unique_ptr but also incleded in entityFactory.h

class Plant;
class Predator;
class Prey;

struct Cell
{
	Predator* predator_here = nullptr;
	Prey* prey_here = nullptr;
	Plant* plant_here = nullptr;
};

class Field
{
	int x, y; // size
	std::vector<std::vector<Cell>> grid;

	std::vector<std::unique_ptr<Plant>> ALL_PLANTS_LIST;
	std::vector<std::unique_ptr<Prey>> ALL_PREYS_LIST;
    std::vector<std::unique_ptr<Predator>> ALL_PREDATORS_LIST;

    int plants_num_cap;
    int preys_num_cap;
    int predators_num_cap;

	std::vector<std::vector<Plant*>> ALL_PLANTS_GRID;
	std::vector<std::vector<Prey*>> ALL_PREYS_GRID;
	std::vector<std::vector<Predator*>> ALL_PREDATORS_GRID;

    int step_num = 0;

public:
    Field(int usr_x, int usr_y, int plants_num_cap, int preys_num_cap, int predators_num_cap);
	~Field() = default;

	template <typename T>
	void createAnyPlants(int value, int repr_chance, int count)
	{
		int created = 0;
        while (created < count && created < plants_num_cap)
		{
			int x, y;
            int attempts = 0;
			do
			{
				x = rand() % getSizeX();
				y = rand() % getSizeY();
                attempts++;
                if (attempts > 10)
                    return;
            } while (ALL_PLANTS_GRID[y][x] != nullptr);

			auto plant = std::make_unique<T>(this, x, y, value, repr_chance);
			ALL_PLANTS_GRID[y][x] = plant.get();
			ALL_PLANTS_LIST.push_back(std::move(plant));
			
			created++;
		}
	}

	template <typename T>
	void createAnyPreys(int age, int death_age, int speed, int fov, int hunger, int value, int repr_age, int repr_chance, int get_hungry_at, int count)
	{
		int created = 0;
        while (created < count && created < preys_num_cap)
		{
			int x, y;
            int attempts = 0;
			do
			{
				x = rand() % getSizeX();
				y = rand() % getSizeY();
                attempts++;
                if (attempts > 10)
                    return;
			} while (ALL_PREYS_GRID[y][x] != nullptr);

			auto prey = std::make_unique<T>(this, x, y, age, death_age, speed, fov, hunger, value, repr_age, repr_chance, get_hungry_at);
			ALL_PREYS_GRID[y][x] = prey.get();
			ALL_PREYS_LIST.push_back(std::move(prey));
			
			created++;
		}
	}

	template <typename T>
	void createAnyPredators(int age, int death_age, int speed, int fov, int hunger, int value, int repr_age, int repr_chance, int get_hungry_at, int count)
	{
		int created = 0;
        while (created < count && created < predators_num_cap)
		{
			int x, y;
            int attempts = 0;
			do
			{
				x = rand() % getSizeX();
				y = rand() % getSizeY();
                attempts++;
                if (attempts > 10)
                    return;
			} while (ALL_PREDATORS_GRID[y][x] != nullptr);

			auto predator = std::make_unique<T>(this, x, y, age, death_age, speed, fov, hunger, value, repr_age, repr_chance, get_hungry_at);
			ALL_PREDATORS_GRID[y][x] = predator.get();
			ALL_PREDATORS_LIST.push_back(std::move(predator));
			
			created++;
		}
	}

	std::vector<Plant*> getPlantsAround(int seeker_x, int seeker_y, int radius);
	std::vector<Prey*> getPreysAround(int seeker_x, int seeker_y, int radius);
	std::vector<Predator*> getPredatorsAround(int seeker_x, int seeker_y, int radius);

	Plant* findPlantByCoords(int search_x, int search_y);
	Prey* findPreyByCoords(int search_x, int search_y);
	Predator* findPredatorByCoords(int search_x, int search_y);

	template <typename T>
	void addPlant(Field* field, int put_x, int put_y, int value, int repr_chance)
	{
        if (plants_num_cap && ALL_PLANTS_LIST.size() >= plants_num_cap)
            return;

		auto plant = std::make_unique<T>(this, put_x, put_y, value, repr_chance);
		ALL_PLANTS_GRID[put_y][put_x] = plant.get();
		ALL_PLANTS_LIST.push_back(std::move(plant));
	}

	template <typename T>
	void addPrey(Field* field, int put_x, int put_y, int age, int death_age, int speed, int fov, int hunger, int value, int repr_age,  int repr_chance, int get_hungry_at)
	{
        if (preys_num_cap && ALL_PREYS_LIST.size() >= preys_num_cap)
            return;

		auto prey = std::make_unique<T>(this, put_x, put_y, age, death_age, speed, fov, hunger, value, repr_age, repr_chance, get_hungry_at);
		ALL_PREYS_GRID[put_y][put_x] = prey.get();
		ALL_PREYS_LIST.push_back(std::move(prey));
		
	}

	template <typename T>
	void addPredator(Field* field, int put_x, int put_y, int age, int death_age, int speed, int fov, int hunger, int value, int repr_age, int repr_chance, int get_hungry_at)
	{
        if (predators_num_cap && ALL_PREDATORS_LIST.size() >= predators_num_cap)
            return;

		auto predator = std::make_unique<T>(this, put_x, put_y, age, death_age, speed, fov, hunger, value, repr_age, repr_chance, get_hungry_at);
		ALL_PREDATORS_GRID[put_y][put_x] = predator.get();
		ALL_PREDATORS_LIST.push_back(std::move(predator));
		
	}

	void deletePlant(int del_x, int del_y);
	void deletePrey(int del_x, int del_y);
	void deletePredator(int del_x, int del_y);

    void clearAll();

	void runSimulation();

	void putOnGrid();
	void printGrid();

	void showPredatorInfo();
	void showPreyInfo();
	void showPlantInfo();

    int getPlantNum() { return ALL_PLANTS_LIST.size(); };
	int getPreyNum() { return ALL_PREYS_LIST.size(); };
	int getPredatorNum() { return ALL_PREDATORS_LIST.size(); };

    std::vector<Plant*> getAllPlantsRaw();
    std::vector<Prey*> getAllPreysRaw();
    std::vector<Predator*> getAllPredatorsRaw();

	int getSizeX() { return x; };
	int getSizeY() { return y; };

    int getStepNum() {return step_num; };
};
