#include "prey.h"
#include "predator.h"

Prey::Prey(Field* field, int x, int y, int age, int death_age, int speed, int fov, int hunger, int value, int repr_age, int repr_chance, int get_hungry_at) : Animal(x, y, age, death_age, speed, fov, hunger, value, repr_age, repr_chance, get_hungry_at), field(field)
{
    plant_target = nullptr;
    predator_target = nullptr;
    state = std::make_unique<NormalPreyState>();
}

void NormalPreyState::move(Prey* prey)
{
    prey->changeAgeBy(1);
    prey->changeHungerby(-1);

    int fieldSizeX = prey->getField()->getSizeX();
    int fieldSizeY = prey->getField()->getSizeY();

    const std::vector<std::pair<int, int>>* directions = prey->getDirections();

    // random movement
    for (int i = 0; i < 10; i++) // try to move in a random direction up to 10 times
    {
        int direction = rand() % directions->size();
        int dx = (*directions)[direction].first;
        int dy = (*directions)[direction].second;
        int newX = prey->getX() + dx;
        int newY = prey->getY() + dy;

        if (newX >= 0 && newX < fieldSizeX && newY >= 0 && newY < fieldSizeY && prey->getField()->findPreyByCoords(newX, newY) == nullptr)
        {
            prey->setX(newX);
            prey->setY(newY);
            break;
        }
    }
}

void NormalPreyState::eat(Prey* prey)
{
    // Prey doesn't eat in normal state

    // if (prey->getField()->findPlantByCoords(prey->getX(), prey->getY()) != nullptr)
    // {
    //     prey->getField()->deletePlant(prey->getX(), prey->getY());
    //     prey->setPlantTarget(nullptr);
    //     prey->changeHungerby(5);
    // }
}

void NormalPreyState::lookForFood(Prey* prey)
{
    // prey->setPlantTarget(nullptr);
    // prey->setPredatorTarget(nullptr);
}

void NormalPreyState::updateState(Prey* prey)
{
    std::unique_ptr<PreyState> newState;

    // ! May be better to separate this logic into a separate function
    // check for predators around 
    std::vector<Predator*> predators_around = prey->getField()->getPredatorsAround(prey->getX(), prey->getY(), prey->getFov());
    if (!predators_around.empty())
        prey->setPredatorTarget(predators_around[0]);
    else
        prey->setPredatorTarget(nullptr);
    // ! May be better to separate this logic into a separate function

    // change state based on conditions
    if (prey->getPredatorTarget() != nullptr)
    {
        prey->setPlantTarget(nullptr);
        newState = std::make_unique<ScaredPreyState>();
    }
    else if (prey->getHunger() < prey->gethungryAt())
    {
        newState = std::make_unique<HungryPreyState>();
    }
    else
    {
        prey->setPlantTarget(nullptr);
        newState = std::make_unique<NormalPreyState>();
    }

    // Check if the new state is different from the current state
    if (prey->getStateId() != typeid(*newState))
        prey->setState(std::move(newState));

    // else, unique_ptr will be deleted automatically
}


void ScaredPreyState::move(Prey* prey)
{
    prey->changeAgeBy(1);
    prey->changeHungerby(-1);

    int fieldSizeX = prey->getField()->getSizeX();
    int fieldSizeY = prey->getField()->getSizeY();

    Animal* predator = prey->getPredatorTarget();
    if (predator != nullptr)
    {
        // move away from the predator | loop the world
        int dx = (predator->getX() < prey->getX() ? 1 : -1);
        int dy = (predator->getY() < prey->getY() ? 1 : -1);

        int newX = prey->getX() + dx;
        int newY = prey->getY() + dy;

        if (newX >= 0 && newX < fieldSizeX && newY >= 0 && newY < fieldSizeY && prey->getField()->findPreyByCoords(newX, newY) == nullptr)
        {
            prey->setX(newX);
            prey->setY(newY);
        }
        else // if the target cell is occupied, try to move in a random direction
        {
            const std::vector<std::pair<int, int>>* directions = prey->getDirections();

            // random movement
            for (int i = 0; i < 10; i++) // try to move in a random direction up to 10 times
            {
                int direction = rand() % directions->size();
                int dx = (*directions)[direction].first;
                int dy = (*directions)[direction].second;
                int newX = prey->getX() + dx;
                int newY = prey->getY() + dy;

                if (newX >= 0 && newX < fieldSizeX && newY >= 0 && newY < fieldSizeY && prey->getField()->findPreyByCoords(newX, newY) == nullptr)
                {
                    prey->setX(newX);
                    prey->setY(newY);
                    break;
                }
            }
        }
    }
    // no situation where prey has no predator target
}

void ScaredPreyState::eat(Prey* prey)
{
    // doesn't eat if scared
}

void ScaredPreyState::lookForFood(Prey* prey)
{
    // Scared prey doesn't look for food, it just runs away from predators
}

void ScaredPreyState::updateState(Prey* prey)
{
    std::unique_ptr<PreyState> newState;

    // ! May be better to separate this logic into a separate function
    // Check for predators around
    std::vector<Predator*> predators_around = prey->getField()->getPredatorsAround(prey->getX(), prey->getY(), prey->getFov());
    if (!predators_around.empty())
        prey->setPredatorTarget(predators_around[0]);
    else
        prey->setPredatorTarget(nullptr);
    // ! May be better to separate this logic into a separate function

    // change state based on conditions
    if (prey->getPredatorTarget() != nullptr)
    {
        prey->setPlantTarget(nullptr);
        newState = std::make_unique<ScaredPreyState>();
    }
    else if (prey->getHunger() < prey->gethungryAt())
    {
        newState = std::make_unique<HungryPreyState>();
    }
    else
    {
        prey->setPlantTarget(nullptr);
        newState = std::make_unique<NormalPreyState>();
    }

    // Check if the new state is different from the current state
    if (prey->getStateId() != typeid(*newState))
        prey->setState(std::move(newState));

    // else, unique_ptr will be deleted automatically
}


void HungryPreyState::move(Prey* prey)
{
    prey->changeAgeBy(1);
    prey->changeHungerby(-1);

    int fieldSizeX = prey->getField()->getSizeX();
    int fieldSizeY = prey->getField()->getSizeY();

    Plant* plant = prey->getPlantTarget();
    if (plant != nullptr)
    {
        int newX = prey->getX() + (plant->getX() > prey->getX() ? 1 : -1);
        int newY = prey->getY() + (plant->getY() > prey->getY() ? 1 : -1);

        if (newX >= 0 && newX < fieldSizeX && newY >= 0 && newY < fieldSizeY && prey->getField()->findPreyByCoords(newX, newY) == nullptr)
        {
            prey->setX(newX);
            prey->setY(newY);
        }
        else // if the target cell is occupied, try to move in a random direction
        {
            const std::vector<std::pair<int, int>>* directions = prey->getDirections();

            // random movement
            for (int i = 0; i < 10; i++) // try to move in a random direction up to 10 times
            {
                int direction = rand() % directions->size();
                int dx = (*directions)[direction].first;
                int dy = (*directions)[direction].second;
                int newX = (prey->getX()) + dx;
                int newY = (prey->getY()) + dy;

                if (newX >= 0 && newX < fieldSizeX && newY >= 0 && newY < fieldSizeY && prey->getField()->findPreyByCoords(newX, newY) == nullptr)
                {
                    prey->setX(newX);
                    prey->setY(newY);
                    break;
                }
            }
        }
    }
    else // if no food target, move randomly
    {
        const std::vector<std::pair<int, int>>* directions = prey->getDirections();

        // random movement
        for (int i = 0; i < 10; i++) // try to move in a random direction up to 10 times
        {
            int direction = rand() % directions->size();
            int dx = (*directions)[direction].first;
            int dy = (*directions)[direction].second;
            int newX = (prey->getX()) + dx;
            int newY = (prey->getY()) + dy;

            if (newX >= 0 && newX < fieldSizeX && newY >= 0 && newY < fieldSizeY && prey->getField()->findPreyByCoords(newX, newY) == nullptr)
            {
                prey->setX(newX);
                prey->setY(newY);
                break;
            }
        }
    }

}

void HungryPreyState::eat(Prey* prey)
{
    Plant* plant = prey->getField()->findPlantByCoords(prey->getX(), prey->getY());
    if (plant != nullptr)
    {
        prey->getField()->deletePlant(prey->getX(), prey->getY());
        prey->setPlantTarget(nullptr);
        prey->changeHungerby(plant->getValue());
    }
}

void HungryPreyState::lookForFood(Prey* prey)
{
    std::vector<Plant*> plants_around = prey->getField()->getPlantsAround(prey->getX(), prey->getY(), prey->getFov() * 2); // bigger fov

    if (!plants_around.empty())
    {
        prey->setPlantTarget(plants_around[0]);
    }
}

void HungryPreyState::updateState(Prey* prey)
{
    std::unique_ptr<PreyState> newState;

    // ! May be better to separate this logic into a separate function
    // Check for predators around
    std::vector<Predator*> predators_around = prey->getField()->getPredatorsAround(prey->getX(), prey->getY(), prey->getFov());
    if (!predators_around.empty())
        prey->setPredatorTarget(predators_around[0]);
    else
        prey->setPredatorTarget(nullptr);
    // ! May be better to separate this logic into a separate function

    // change state based on conditions
    if (prey->getPredatorTarget() != nullptr)
    {
        prey->setPlantTarget(nullptr);
        newState = std::make_unique<ScaredPreyState>();
    }
    else if (prey->getHunger() < prey->gethungryAt())
    {
        newState = std::make_unique<HungryPreyState>();
    }
    else
    {
        prey->setPlantTarget(nullptr);
        newState = std::make_unique<NormalPreyState>();
    }

    // Check if the new state is different from the current state
    if (prey->getStateId() != typeid(*newState))
        prey->setState(std::move(newState));

    // else, unique_ptr will be deleted automatically
}

