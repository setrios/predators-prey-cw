#pragma once
#include "../base_classes/animal.h"
#include "../field.h"
#include <memory>
#include <typeinfo>

class Predator;
class Prey;

class PredatorState
{
public:
    virtual void move(Predator* predator) = 0;
    virtual void eat(Predator* predator) = 0;
    virtual void lookForFood(Predator* predator) = 0;
    virtual void updateState(Predator* predator) = 0;
    virtual const char* getStateName() const = 0;
};

class Predator : public Animal // public to public and protected data are inherited without changing the level of access to them
{
protected:
    Field* field;
    Prey* prey_target;
    std::unique_ptr<PredatorState> state;

public:
    Predator(Field* field, int x, int y, int age, int death_age, int speed, int fov, int hunger, int value, int repr_age, int repr_chance, int get_hungry_at);
    virtual ~Predator() = default;

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

    bool isPrey() override { return false; }
    virtual bool isBig() { return false; }


    // Getters and setters for states to use
    Field* getField() const { return field; }
    Prey* getPreyTarget() const { return prey_target; }

    int getFov() const { return fov; }
    const std::vector<std::pair<int, int>>*  getDirections() { return &directions; }
    
    const std::type_info& getStateId() const { return typeid(*state); }
    const char* getStateName() const { return state->getStateName(); }

    void setX(int new_x) { x = new_x; }
    void setY(int new_y) { y = new_y; }
    void setPreyTarget(Prey* target) { prey_target= target; }
    void changeAgeBy(int delta) { age += delta; }
    void changeHungerby(int delta) { hunger += delta; }
    void setState(std::unique_ptr<PredatorState> new_state) { state = std::move(new_state); }

};


class NormalPredatorState : public PredatorState
{
public:
    NormalPredatorState() = default;
    void move(Predator* predator) override;
    void eat(Predator* predator) override;
    void lookForFood(Predator* predator) override;
    void updateState(Predator* predator) override;
    const char* getStateName() const override { return "Normal"; }
};


// no scared state for predators, only for preys

// class ScaredState : public PreyState
// {
// public:
//     ScaredState() = default;
//     void move(Prey* prey) override;
//     void eat(Prey* prey) override;
//     void lookForFood(Prey* prey) override;
//     void updateState(Prey* prey) override;
//     const char* getStateName() const override { return "Scared"; }
// };


class HungryPredatorState : public PredatorState
{
public:
    HungryPredatorState() = default;
    void move(Predator* predator) override;
    void eat(Predator* predator) override;
    void lookForFood(Predator* predator) override;
    void updateState(Predator* predator) override;
    const char* getStateName() const override { return "Hungry"; }
};

