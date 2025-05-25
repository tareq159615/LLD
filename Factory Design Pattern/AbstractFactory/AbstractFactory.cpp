#include <bits/stdc++.h>
using namespace std;

// Product 1 --> Burger
class Burger
{
public:
    virtual void prepare() = 0; // Pure virtual function
};

class BasicBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Basic Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Standard Burger with bun, patty, and ketchup!" << endl;
    }
};

class PremiumBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Premium Burger with bun, patty, and ketchup!" << endl;
    }
};

class BasicWheatBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Basic Wheat Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandarWheatBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Basic Wheat Burger with bun, patty, and ketchup!" << endl;
    }
};

class PremiumWheatBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Basic Wheat Burger with bun, patty, and ketchup!" << endl;
    }
};

// Product 2 --> GarlicBread
class GarlicBread
{
public:
    virtual void prepare() = 0;
};

class BasicGarlicBread : public GarlicBread
{
public:
    void prepare() override
    {
        cout << "Preparing Basic Garlic Bread with butter and garlic!\n";
    }
};

class CheeseGarlicBread : public GarlicBread
{
public:
    void prepare() override
    {
        cout << "Preparing Cheese Garlic Bread with butter and garlic!\n";
    }
};

class BasicWheatGarlicBread : public GarlicBread
{
public:
    void prepare() override
    {
        cout << "Preparing Basic Wheat Garlic Bread with butter and garlic!\n";
    }
};

class CheeseWheatGarlicBread : public GarlicBread
{
public:
    void prepare() override
    {
        cout << "Preparing Cheese Wheat Garlic Bread with butter and garlic!\n";
    }
};

// Factory and its concretions
class MealFactory
{
public:
    virtual Burger *createBurger(string &type) = 0;
    virtual GarlicBread *createGarlicBread(string &type) = 0;
};

class SinghBurger : public MealFactory
{
public:
    Burger *createBurger(string &type)
    {
        if (type == "BasicBurger")
            return new BasicBurger();
        else if (type == "StandardBurger")
            return new StandardBurger();
        else if (type == "PremiumBurger")
            return new PremiumBurger();
        else
            return nullptr;
    }
};

class KingBurger : public MealFactory
{
public:
    Burger *createBurger(string &type) override
    {
        if (type == "BasicWheatBurger")
            return new BasicWheatBurger();
        else if (type == "StandarWheatBurger")
            return new StandarWheatBurger();
        else if (type == "PremiumWheatBurger")
            return new PremiumWheatBurger();
        else
            return nullptr;
    }
    GarlicBread *createGarlicBread(string &type) override
    {
        if (type == "BasicWheatGarlicBread")
            return new BasicWheatGarlicBread();
        else if (type == "CheeseWheatGarlicBread")
            return new CheeseWheatGarlicBread();
        else
            return nullptr;
    }
};

int main(){
    // int Choice; 
    // cout << "---------------------------------------------" << endl; 
    // cout << ""
    string burgerType = "basic";
    string garlicBreadType = "cheese";

    MealFactory* mealFactory = new KingBurger();

    Burger* burger = mealFactory->createBurger(burgerType);
    GarlicBread* garlicBread = mealFactory->createGarlicBread(garlicBreadType);

    burger->prepare();
    garlicBread->prepare();
}