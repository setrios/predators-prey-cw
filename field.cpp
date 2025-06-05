#include <iostream>
#include <iomanip>
#include "algorithm" // for std::find_if

#include "field.h"

#include "base_classes/plant.h"
#include "type/predator.h"
#include "type/prey.h"


Field::Field(int usr_x, int usr_y, int usr_plants_num_cap, int usr_preys_num_cap, int usr_predators_num_cap)
{
	x = usr_x;
	y = usr_y;
    plants_num_cap = usr_plants_num_cap;
    preys_num_cap = usr_preys_num_cap;
    predators_num_cap = usr_predators_num_cap;
	grid.resize(usr_y, std::vector<Cell>(usr_x, { nullptr, nullptr }));
	ALL_PLANTS_GRID.resize(usr_y, std::vector<Plant*>(usr_x, nullptr));
	ALL_PREYS_GRID.resize(usr_y, std::vector<Prey*>(usr_x, nullptr));
	ALL_PREDATORS_GRID.resize(usr_y, std::vector<Predator*>(usr_x, nullptr));
}

// Field::~Field() {}

// return pointer not to a plant itself, but to the cell in grid
std::vector<Plant*> Field::getPlantsAround(int seeker_x, int seeker_y, int radius)
{
	std::vector<Plant*> search_result;

	int left_bound = (seeker_x > radius) ? seeker_x - radius : 0;
	int right_bound = seeker_x + radius;
	int top_bound = (seeker_y > radius) ? seeker_y - radius : 0;
	int bottom_bound = seeker_y + radius;

	for (int i = 0; i < ALL_PLANTS_GRID.size(); i++)
	{
		for (int j = 0; j < ALL_PLANTS_GRID[i].size(); j++)
		{
			if (ALL_PLANTS_GRID[i][j] != nullptr)
			{
				int plant_x = j;
				int plant_y = i;

				if (plant_x >= left_bound && plant_x <= right_bound &&
					plant_y >= top_bound && plant_y <= bottom_bound)
				{
					search_result.push_back(ALL_PLANTS_GRID[i][j]);
				}
			}
		}
	}
	return search_result;
}

std::vector<Prey*> Field::getPreysAround(int seeker_x, int seeker_y, int radius)
{
	// as map stores data in sorted way 
	std::vector<Prey*> search_result;

	int left_bound = (seeker_x > radius) ? seeker_x - radius : 0;
	int right_bound = seeker_x + radius;
	int top_bound = (seeker_y > radius) ? seeker_y - radius : 0;
	int bottom_bound = seeker_y + radius;

	for (int i = 0; i < ALL_PREYS_GRID.size(); i++)
	{
		for (int j = 0; j < ALL_PREYS_GRID[i].size(); j++)
		{
			if (ALL_PREYS_GRID[i][j] != nullptr)
			{
				int prey_x = j;
				int prey_y = i;

				if (prey_x >= left_bound && prey_x <= right_bound &&
					prey_y >= top_bound && prey_y <= bottom_bound)
				{
					search_result.push_back(ALL_PREYS_GRID[i][j]);
				}
			}
		}
	}
	return search_result;
}

std::vector<Predator*> Field::getPredatorsAround(int seeker_x, int seeker_y, int radius)
{
	// as map stores data in sorted way 
	std::vector<Predator*> search_result;

	int left_bound = (seeker_x > radius) ? seeker_x - radius : 0;
	int right_bound = seeker_x + radius;
	int top_bound = (seeker_y > radius) ? seeker_y - radius : 0;
	int bottom_bound = seeker_y + radius;

	for (int i = 0; i < ALL_PREDATORS_GRID.size(); i++)
	{
		for (int j = 0; j < ALL_PREDATORS_GRID[i].size(); j++)
		{
			if (ALL_PREDATORS_GRID[i][j] != nullptr)
			{
				int predator_x = j;
				int predator_y = i;

				if (predator_x >= left_bound && predator_x <= right_bound &&
					predator_y >= top_bound && predator_y <= bottom_bound)
				{
					search_result.push_back(ALL_PREDATORS_GRID[i][j]);
				}
			}
		}
	}
	return search_result;
}

Plant* Field::findPlantByCoords(int search_x, int search_y)
{
	return ALL_PLANTS_GRID[search_y][search_x];
}

Prey* Field::findPreyByCoords(int search_x, int search_y)
{
	return ALL_PREYS_GRID[search_y][search_x];
}

Predator* Field::findPredatorByCoords(int search_x, int search_y)
{
	return ALL_PREDATORS_GRID[search_y][search_x];
}

void Field::deletePlant(int del_x, int del_y)
{
	auto it = std::find_if(ALL_PLANTS_LIST.begin(), ALL_PLANTS_LIST.end(),
		[del_x, del_y](const std::unique_ptr<Plant>& plant) 
		{
			return plant->getX() == del_x && plant->getY() == del_y;
		});

	if (it != ALL_PLANTS_LIST.end()) 
	{
		// clearing plant target for all the preys
		// for (int i = 0; i < ALL_PREYS_LIST.size(); i++)
		// {
		// 	if (ALL_PREYS_LIST[i]->getPlantTarget() == (*it).get())
		// 	{
		// 		ALL_PREYS_LIST[i]->setPlantTarget(nullptr); // clearing plant target for preys
		// 	}
		// }

		// deleting plant from grid and list
		ALL_PLANTS_GRID[del_y][del_x] = nullptr;
		ALL_PLANTS_LIST.erase(it);
	}
}

void Field::deletePrey(int del_x, int del_y)
{
	auto it = std::find_if(ALL_PREYS_LIST.begin(), ALL_PREYS_LIST.end(),
		[del_x, del_y](const std::unique_ptr<Prey>& prey)
		{
			return prey->getX() == del_x && prey->getY() == del_y;
		});

	if (it != ALL_PREYS_LIST.end()) 
	{
		ALL_PREYS_GRID[del_y][del_x] = nullptr;
		ALL_PREYS_LIST.erase(it);
	}
}

void Field::deletePredator(int del_x, int del_y)
{
	auto it = std::find_if(ALL_PREDATORS_LIST.begin(), ALL_PREDATORS_LIST.end(),
		[del_x, del_y](const std::unique_ptr<Predator>& predator) 
		{
			return predator->getX() == del_x && predator->getY() == del_y;
		});

	if (it != ALL_PREDATORS_LIST.end()) 
	{
		ALL_PREDATORS_GRID[del_y][del_x] = nullptr;
		ALL_PREDATORS_LIST.erase(it);
	}
}

void Field::clearAll()
{

    grid.clear();
    grid.resize(y, std::vector<Cell>(x));

    // clear the grid vectors
    ALL_PLANTS_GRID.clear();
    ALL_PREYS_GRID.clear();
    ALL_PREDATORS_GRID.clear();

    // reinitialize the grids to their original size:
    ALL_PLANTS_GRID.resize(y, std::vector<Plant*>(x));
    ALL_PREYS_GRID.resize(y, std::vector<Prey*>(x));
    ALL_PREDATORS_GRID.resize(y, std::vector<Predator*>(x));

    // clear the main lists (this will automatically delete the objects due to unique_ptr)
    ALL_PLANTS_LIST.clear();
    ALL_PREYS_LIST.clear();
    ALL_PREDATORS_LIST.clear();

    // reset step number
    step_num = 0;
}


void Field::runSimulation()
{
	std::vector<std::pair<int, int>> creaturesToRemove;

	// updating predators
	for (int i = 0; i < ALL_PREDATORS_LIST.size(); i++)
	{
		ALL_PREDATORS_LIST[i]->move();
		ALL_PREDATORS_LIST[i]->eat();
		ALL_PREDATORS_LIST[i]->lookForFood();
		ALL_PREDATORS_LIST[i]->tryReproduce();

		if (ALL_PREDATORS_LIST[i]->getHunger() <= 0 || ALL_PREDATORS_LIST[i]->getAge() > ALL_PREDATORS_LIST[i]->getDeathAge())
			creaturesToRemove.push_back({ ALL_PREDATORS_LIST[i]->getX(), ALL_PREDATORS_LIST[i]->getY() });
	}

	// updating predators grid
	ALL_PREDATORS_GRID.clear();
	ALL_PREDATORS_GRID.resize(y, std::vector<Predator*>(x, nullptr));

	for (int i = 0; i < ALL_PREDATORS_LIST.size(); i++) 
	{
		ALL_PREDATORS_GRID[ALL_PREDATORS_LIST[i]->getY()][ALL_PREDATORS_LIST[i]->getX()] = ALL_PREDATORS_LIST[i].get();
	}

	for (auto item : creaturesToRemove)
	{
		deletePredator(item.first, item.second);
	}

	creaturesToRemove.clear();

	// updating preys
	for (int i = 0; i < ALL_PREYS_LIST.size(); i++)
	{
		ALL_PREYS_LIST[i]->move();
		ALL_PREYS_LIST[i]->eat();
		ALL_PREYS_LIST[i]->lookForFood();
		ALL_PREYS_LIST[i]->tryReproduce();

		if (ALL_PREYS_LIST[i]->getHunger() <= 0 || ALL_PREYS_LIST[i]->getAge() > ALL_PREYS_LIST[i]->getDeathAge())
			creaturesToRemove.push_back({ ALL_PREYS_LIST[i]->getX(), ALL_PREYS_LIST[i]->getY() });
	}

	// updating preys grid
	ALL_PREYS_GRID.clear();
	ALL_PREYS_GRID.resize(y, std::vector<Prey*>(x, nullptr));
	
	for (int i = 0; i < ALL_PREYS_LIST.size(); i++) {
		ALL_PREYS_GRID[ALL_PREYS_LIST[i]->getY()][ALL_PREYS_LIST[i]->getX()] = ALL_PREYS_LIST[i].get();
	}

	for (auto item : creaturesToRemove)
	{
		deletePrey(item.first, item.second);
	}

	creaturesToRemove.clear();

	// updating plants
	for (int i = 0; i < ALL_PLANTS_LIST.size(); i++)
	{
		ALL_PLANTS_LIST[i]->spread();
	}

	// updating plants grid
	ALL_PLANTS_GRID.clear();
	ALL_PLANTS_GRID.resize(y, std::vector<Plant*>(x, nullptr));

	for (int i = 0; i < ALL_PLANTS_LIST.size(); i++) 
	{
		ALL_PLANTS_GRID[ALL_PLANTS_LIST[i]->getY()][ALL_PLANTS_LIST[i]->getX()] = ALL_PLANTS_LIST[i].get();
	}

    // no need to use grid if displaying not in a console
    // putOnGrid();

    step_num++;
}

void Field::putOnGrid()
{
	grid.clear();
	grid.resize(y, std::vector<Cell>(x, { nullptr, nullptr })); // clearing grid

	for (int i = 0; i < ALL_PLANTS_LIST.size(); i++)
	{
		grid[ALL_PLANTS_LIST[i]->getY()][ALL_PLANTS_LIST[i]->getX()].plant_here = ALL_PLANTS_LIST[i].get();
	}
	for (int i = 0; i < ALL_PREYS_LIST.size(); i++)
	{
		grid[ALL_PREYS_LIST[i]->getY()][ALL_PREYS_LIST[i]->getX()].prey_here = ALL_PREYS_LIST[i].get();
	}
	for (int i = 0; i < ALL_PREDATORS_LIST.size(); i++)
	{
		grid[ALL_PREDATORS_LIST[i]->getY()][ALL_PREDATORS_LIST[i]->getX()].predator_here = ALL_PREDATORS_LIST[i].get();
	}
}

void Field::printGrid()
{
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j].predator_here != nullptr)
			{
				std::cout << grid[i][j].predator_here->getIcon();
			}
			else if (grid[i][j].prey_here != nullptr)
			{
				std::cout << grid[i][j].prey_here->getIcon();
			}
			else if (grid[i][j].plant_here != nullptr)
			{
				std::cout << grid[i][j].plant_here->getIcon();
			}
			else if (grid[i][j].plant_here == nullptr && grid[i][j].prey_here == nullptr && grid[i][j].predator_here == nullptr)
			{
				std::cout << '.';
			}
		}
		std::cout << ' ' << i << std::endl;
	}
	grid.clear();
	grid.resize(y, std::vector<Cell>(x, { nullptr, nullptr })); // clearing grid
}

std::vector<Plant*> Field::getAllPlantsRaw()
{
    std::vector<Plant*> result;
    for (const auto& plant : ALL_PLANTS_LIST)
    {
        result.push_back(plant.get());
    }
    return result;
}

std::vector<Prey*> Field::getAllPreysRaw()
{
    std::vector<Prey*> result;
    for (const auto& prey : ALL_PREYS_LIST)
    {
        result.push_back(prey.get());
    }
    return result;
}

std::vector<Predator*> Field::getAllPredatorsRaw()
{
    std::vector<Predator*> result;
    for (const auto& predator : ALL_PREDATORS_LIST)
    {
        result.push_back(predator.get());
    }
    return result;
}

void Field::showPreyInfo()
{
	for (int i = 0; i < ALL_PREYS_LIST.size(); i++)
	{
		Prey* curr_prey = ALL_PREYS_LIST[i].get();
		std::cout << curr_prey->getIcon();
		std::cout << " x: " << std::setw(2) << curr_prey->getX() << " y: " << std::setw(2) << curr_prey->getY();
		std::cout << " hunger: " << std::setw(2) << curr_prey->getHunger() << " age: " << std::setw(2) << curr_prey->getAge();
		std::cout << " state: " << curr_prey->getStateName() << std::endl;
	}
	std::cout << std::endl;
}

void Field::showPredatorInfo()
{
	for (int i = 0; i < ALL_PREDATORS_LIST.size(); i++)
	{
		Predator* curr_pred = ALL_PREDATORS_LIST[i].get();
		std::cout << curr_pred->getIcon();
		std::cout << " x: " << std::setw(2) << curr_pred->getX() << " y: " << std::setw(2) << curr_pred->getY();
		std::cout << " hunger: " << std::setw(2) << curr_pred->getHunger() << " age: " << std::setw(2) << curr_pred->getAge();
		std::cout << " state: " << curr_pred->getStateName() << std::endl;
	}
	std::cout << std::endl;
}

void Field::showPlantInfo()
{
	for (int i = 0; i < ALL_PLANTS_LIST.size(); i++)
	{
		Plant* curr_plant = ALL_PLANTS_LIST[i].get();
		std::cout << curr_plant->getIcon();
		std::cout << " x: " << std::setw(2) << curr_plant->getX() << " y: " << std::setw(2) << curr_plant->getY() << std::endl;
	}
	std::cout << std::endl;
}
