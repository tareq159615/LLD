#include <bits/stdc++.h>
using namespace std;

// Product Class and subclasses
class Burger
{
public:
    virtual void prepare() = 0; // Pure virtual function
    virtual ~Burger() {}        // Virtual destructor
};

class BasicBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Basic Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class StandardBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Standard Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Premium Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class BasicWheatBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Basic Wheat Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class StandardWheatBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Standard Wheat Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

class PremiumWheatBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Premium Wheat Burger with bun, patty, cheese, and lettuce!" << endl;
    }
};

// Factory and its concretions
class BurgerFactory
{
public:
    virtual Burger *createBurger(string &type) = 0;
};

class SinghBurger : public BurgerFactory
{
public:
    Burger *createBurger(string &type)
    {
        if (type == "BasicBurger")
        {
            return new BasicBurger();
        }
        else if (type == "StandardBurger")
        {
            return new StandardBurger();
        }
        else if (type == "PremiumBurger")
        {
            return new PremiumBurger();
        }
        else
        {
            cout << "Invalid burger type!" << endl;
            return nullptr;
        }
    }
};

class KingBurger : public BurgerFactory
{
public:
    Burger *createBurger(string &type) override
    {
        if (type == "BasicWheatBurger")
        {
            return new BasicWheatBurger();
        }
        else if (type == "StandardWheatBurger")
        {
            return new StandardWheatBurger();
        }
        else if (type == "PremiumWheatBurger")
        {
            return new PremiumWheatBurger();
        }
        else
        {
            cout << "Invalid burger type!" << endl;
            return nullptr;
        }
    }
};

int main()
{
    cout << "--------------------" << endl;
    cout << "Choice your burger" << endl;
    cout << "--------------------" << endl;
    cout << "----Singh Burger----" << endl;
    cout << "--------------------" << endl;
    cout << "1. Basic Burger" << endl;
    cout << "2. Standard Burger" << endl;
    cout << "3. Premium Burger" << endl;
    cout << "--------------------" << endl;
    cout << "----King Burger----" << endl;
    cout << "--------------------" << endl;
    cout << "4. Basic Wheat Burger" << endl;
    cout << "5. Standard Wheat Burger" << endl;
    cout << "6. Premium Wheat Burger" << endl;
    cout << "Please type here -> ";
    int Choice;
    cin >> Choice;
    string type;
    if (Choice >= 1 && Choice <= 3)
    {
        if (Choice == 1)
        {
            type = "BasicBurger";
        }
        else if (Choice == 2)
        {
            type = "StandardBurger";
        }
        else if (Choice == 3)
        {
            type = "PremiumBurger";
        }
        BurgerFactory *myFactory = new SinghBurger();
        Burger *burger = myFactory->createBurger(type);
        burger->prepare();
    }
    else if (Choice >= 4 && Choice <= 6)
    {
        if (Choice == 4)
        {
            type = "BasicWheatBurger";
        }
        else if (Choice == 5)
        {
            type = "StandardWheatBurger";
        }
        else if (Choice == 6)
        {
            type = "PremiumWheatBurger";
        }
        BurgerFactory *myFactory = new KingBurger();
        Burger *burger = myFactory->createBurger(type);
        burger->prepare();
    }else{
        cout << "Invalid Type!" << endl;
    }
    return 0;
}


