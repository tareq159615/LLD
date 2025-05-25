#include <bits/stdc++.h>
using namespace std;

// --- Strategy Interface for Walk ---
class WalkableRobot
{
public:
    virtual void walk() = 0;
    virtual ~WalkableRobot() {};
};

// --- Concrete Strategies for walk ---
class NormalWalk : public WalkableRobot
{
public:
    void walk() override
    {
        cout << "This Robot Walking normally..." << endl;
    }
};

class NoWalk : public WalkableRobot
{
public:
    void walk() override
    {
        cout << "This Robot Cannot walk..." << endl;
    }
};

// --- Strategy Interface for Talk ---
class TalkableRobot
{
public:
    virtual void talk() = 0;
    virtual ~TalkableRobot() {};
};

class NormalTalk : public TalkableRobot
{
public:
    void talk() override
    {
        cout << "This Robot NormalTalk..." << endl;
    }
};

class NoTalk : public TalkableRobot
{
public:
    void talk() override
    {
        cout << "This Robot NoTalk..." << endl;
    }
};

// --- Strategy Interface for Fly ---
class FlyableRobot
{
public:
    virtual void fly() = 0;
    virtual ~FlyableRobot() {};
};

class NormalFly : public FlyableRobot
{
public:
    void fly() override
    {
        cout << "This Robot NormalFly..." << endl;
    }
};

class NoFly : public FlyableRobot
{
public:
    void fly() override
    {
        cout << "This Robot No Fly..." << endl;
    }
};

class Robot
{
protected:
    FlyableRobot *flyableRobot;
    TalkableRobot *talkableRobot;
    WalkableRobot *walkableRobot;

public:
    Robot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f)
    {
        this->walkableRobot = w;
        this->talkableRobot = t;
        this->flyableRobot = f;
    }

    void walk()
    {
        walkableRobot->walk();
    }

    void fly()
    {
        flyableRobot->fly();
    }

    void talk()
    {
        talkableRobot->talk();
    }

    virtual void projection() = 0; // Abstract method for subclasses
};

// --- Concrete Robot Types ---
class CompanionRobot : public Robot
{
public:
    CompanionRobot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f)
        : Robot(w, t, f) {}

    void projection() override
    {
        cout << "Displaying fliendly companion features..." << endl;
    }
};

// --- Main Function ---
int main()
{
    Robot *robot1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NormalFly());
    robot1 -> walk(); 
    robot1 -> talk(); 
    robot1 -> fly(); 
    robot1->projection();
    cout << "--------------------" << endl;
    Robot *robot2 = new CompanionRobot(new NoWalk(), new NoTalk(), new NormalFly());
    robot2->walk();
    robot2->talk();
    robot2->fly();
    robot2->projection();
    return 0;
}
