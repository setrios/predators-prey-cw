#include "predator.h"
#include "prey.h"

Predator::Predator(Field* field, int x, int y, int age, int death_age, int speed, int fov, int hunger, int value, int repr_age, int repr_chance, int get_hungry_at) : Animal(x, y, age, death_age, speed, fov, hunger, value, repr_age, repr_chance, get_hungry_at), field(field)
{
    prey_target = nullptr;
    state = std::make_unique<NormalPredatorState>();
}


// too many static casts | better to use int
void NormalPredatorState::move(Predator* predator)
{
    predator->changeAgeBy(1);
    predator->changeHungerby(-1);

    int fieldSizeX = predator->getField()->getSizeX();
    int fieldSizeY = predator->getField()->getSizeY();

    const std::vector<std::pair<int, int>>* directions = predator->getDirections();

    for (int i = 0; i < 10; i++) // try to move in a random direction up to 10 times
    {
        int direction = rand() % directions->size();
        int dx = (*directions)[direction].first;
        int dy = (*directions)[direction].second;
        int newX = predator->getX() + dx;
        int newY = predator->getY() + dy;

        if (newX >= 0 && newX < fieldSizeX && newY >= 0 && newY < fieldSizeY && predator->getField()->findPredatorByCoords(newX, newY) == nullptr)
        {
            predator->setX(newX);
            predator->setY(newY);
            break;
        }
    }
}

void NormalPredatorState::eat(Predator* predator)
{
    // Prey doesn't eat in normal state

    // if (prey->getField()->findPlantByCoords(prey->getX(), prey->getY()) != nullptr)
    // {
    //     prey->getField()->deletePlant(prey->getX(), prey->getY());
    //     prey->setPlantTarget(nullptr);
    //     prey->changeHungerby(5);
    // }
}

void NormalPredatorState::lookForFood(Predator* predator)
{
    // predator doesn't look for food in normal state
}

void NormalPredatorState::updateState(Predator* predator)
{
    std::unique_ptr<PredatorState> newState;

    // no need to check for predators around
        
    if (predator->getHunger() < predator->gethungryAt())
    {
        newState = std::make_unique<HungryPredatorState>();
    }
    else
    {
        predator->setPreyTarget(nullptr);
        newState = std::make_unique<NormalPredatorState>();
    }

    // Check if the new state is different from the current state
    if (predator->getStateId() != typeid(*newState))
        predator->setState(std::move(newState));

    // else, unique_ptr will be deleted automatically
}


void HungryPredatorState::move(Predator* predator)
{
    predator->changeAgeBy(1);
    predator->changeHungerby(-1);

    int fieldSizeX = predator->getField()->getSizeX();
    int fieldSizeY = predator->getField()->getSizeY();

    Prey* prey = predator->getPreyTarget();
    if (prey != nullptr)
    {
        // move towards the prey
        int newX = predator->getX() + (prey->getX() > predator->getX() ? 1 : -1);
        int newY = predator->getY() + (prey->getY() > predator->getY() ? 1 : -1);

        if (newX >= 0 && newX < fieldSizeX && newY >= 0 && newY < fieldSizeY)
        {
            predator->setX(newX);
            predator->setY(newY);
        }
    }
    else // if no food target, move randomly
    {
        const std::vector<std::pair<int, int>>* directions = predator->getDirections();

        for (int i = 0; i < 10; i++) // try to move in a random direction up to 10 times
        {
            int direction = rand() % directions->size();
            int dx = (*directions)[direction].first;
            int dy = (*directions)[direction].second;
            int newX = predator->getX() + dx;
            int newY = predator->getY() + dy;

            if (newX >= 0 && newX < fieldSizeX && newY >= 0 && newY < fieldSizeY && predator->getField()->findPredatorByCoords(newX, newY) == nullptr)
            {
                predator->setX((newX));
                predator->setY((newY));
                break;
            }
        }
    }
}

void HungryPredatorState::eat(Predator* predator)
{
    Prey* prey = predator->getField()->findPreyByCoords(predator->getX(), predator->getY());
    if (prey != nullptr)
    { 
        if (prey->isBig() && predator->isBig()) // only big predators can eat big preys
        {
            predator->getField()->deletePrey(predator->getX(), predator->getY());
            predator->setPreyTarget(nullptr);
            predator->changeHungerby(prey->getValue()); // give hunger value of the prey
        }  
        else 
        { 
            predator->getField()->deletePrey(predator->getX(), predator->getY());
            predator->setPreyTarget(nullptr);
            predator->changeHungerby(prey->getValue()); // give hunger value of the prey
        }
    }
}

void HungryPredatorState::lookForFood(Predator* predator)
{
    std::vector<Prey*> preys_around = predator->getField()->getPreysAround(predator->getX(), predator->getY(), predator->getFov() * 2); // bigger fov


    for (Prey* prey : preys_around)
    {
        if (predator->isBig()) // big predators can eat all preys
        {
            predator->setPreyTarget(prey);
            return;
        }
        else // if predator is small
        {
            if (!prey->isBig()) // small predators can eat only small preys
            {
                predator->setPreyTarget(prey);
                return;
            }
        }
    }

}

void HungryPredatorState::updateState(Predator* predator)
{
    std::unique_ptr<PredatorState> newState;

    // no need to check for predators around
        
    if (predator->getHunger() < predator->gethungryAt())
    {
        newState = std::make_unique<HungryPredatorState>();
    }
    else
    {
        predator->setPreyTarget(nullptr);
        newState = std::make_unique<NormalPredatorState>();
    }

    // Check if the new state is different from the current state
    if (predator->getStateId() != typeid(*newState))
        predator->setState(std::move(newState));

    // else, unique_ptr will be deleted automatically
}


