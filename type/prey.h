#pragma once
#include "../base_classes/animal.h"
#include "../base_classes/plant.h"
#include "../field.h"
#include <memory>
#include <typeinfo>

class Prey;
class Predator;

class PreyState
{
public:
    virtual void move(Prey* prey) = 0;
    virtual void eat(Prey* prey) = 0;
    virtual void lookForFood(Prey* prey) = 0;
    virtual void updateState(Prey* prey) = 0;
    virtual const char* getStateName() const = 0;
};

class Prey : public Animal
{
protected:
    Field* field;
    Plant* plant_target; // points not to a plant itself, but to the cell in grid
    Predator* predator_target;
    std::unique_ptr<PreyState> state;

public:

    Prey(Field* field, int x, int y, int age, int death_age, int speed, int fov, int hunger, int value, int repr_age, int repr_chance, int get_hungry_at);
    virtual ~Prey() = default;

    void move()
    {
        state->move(this);
        state->updateState(this);
    }

    void eat()
    {
        state->eat(this);
        state->updateState(this);
    }

    void lookForFood()
    {
        state->lookForFood(this);
        state->updateState(this);
    }

    virtual void tryReproduce() = 0;

    bool isPrey() override { return true; }
    virtual bool isBig() { return false; }

    // Getters and setters for states to use
    Field* getField() const { return field; }
    Plant* getPlantTarget() const { return plant_target; }
    Predator* getPredatorTarget() const { return predator_target; }
    const std::vector<std::pair<int, int>>*  getDirections() { return &directions; }
    const std::type_info& getStateId() const { return typeid(*state); }
    const char* getStateName() const { return state->getStateName(); }

    void setX(size_t new_x) { x = new_x; }
    void setY(size_t new_y) { y = new_y; }
    void setPlantTarget(Plant* target) { plant_target = target; }
    void setPredatorTarget(Predator* target) { predator_target = target; }
    void changeAgeBy(int delta) { age += delta; }
    void changeHungerby(int delta) { hunger += delta; }
    void setState(std::unique_ptr<PreyState> new_state) { state = std::move(new_state); }

};


class NormalPreyState : public PreyState
{
public:
    NormalPreyState() = default;
    void move(Prey* prey) override;
    void eat(Prey* prey) override;
    void lookForFood(Prey* prey) override;
    void updateState(Prey* prey) override;
    const char* getStateName() const override { return "Normal"; }
};


class ScaredPreyState : public PreyState
{
public:
    ScaredPreyState() = default;
    void move(Prey* prey) override;
    void eat(Prey* prey) override;
    void lookForFood(Prey* prey) override;
    void updateState(Prey* prey) override;
    const char* getStateName() const override { return "Scared"; }
};


class HungryPreyState : public PreyState
{
public:
    HungryPreyState() = default;
    void move(Prey* prey) override;
    void eat(Prey* prey) override;
    void lookForFood(Prey* prey) override;
    void updateState(Prey* prey) override;
    const char* getStateName() const override { return "Hungry"; }
};
