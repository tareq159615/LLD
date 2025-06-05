#include <bits/stdc++.h>
using namespace std;

// Command Interface
class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// Receivers
class Light
{
public:
    void on()
    {
        cout << "Light is ON" << endl;
    }
    void off()
    {
        cout << "Light is OFF" << endl;
    }
};

class Fan
{
public:
    void on()
    {
        cout << "Fan is ON" << endl;
    }
    void off()
    {
        cout << "Fan is OFF" << endl;
    }
};

// Concrete Command for Light
class LightCommand : public Command
{
private:
    Light *light;

public:
    LightCommand(Light *l)
    {
        light = l;
    }
    void execute() override
    {
        light->on();
    }
    void undo() override
    {
        light->off();
    }
};

// Concrete Command for Fan
class FanCommand : public Command
{
private:
    Fan *fan;

public:
    FanCommand(Fan *f)
    {
        fan = f;
    }
    void execute() override
    {
        fan->on();
    }
    void undo() override
    {
        fan->off();
    }
};

// Invoker: Remote Controller with static 1D array of 4 buttons
class RemoteController
{
private:
    static const int numButton = 4;
    Command *buttons[numButton];
    bool buttonPressed[numButton];

public:
    RemoteController()
    {
        for (int i = 0; i < numButton; i++)
        {
            buttons[i] = nullptr;
            buttonPressed[i] = false;
        }
    }

    void setCommand(int idx, Command *cmd)
    {
        if (idx >= 0 && idx < numButton)
        {
            if (buttons[idx] != nullptr)
                delete buttons[idx]; // Free old command
            buttons[idx] = cmd;     // Assign new command
            buttonPressed[idx] = false;
        }
    }

    void pressButton(int idx)
    {
        if (idx >= 0 && idx < numButton && buttons[idx] != nullptr)
        {
            if (!buttonPressed[idx])
                buttons[idx]->execute();
            else
                buttons[idx]->undo();

            buttonPressed[idx] = !buttonPressed[idx];
        }
        else
        {
            cout << "No command assigned at button " << idx << endl;
        }
    }

    ~RemoteController()
    {
        for (int i = 0; i < numButton; i++)
        {
            if (buttons[i] != nullptr)
                delete buttons[i];
        }
    }
};

int main()
{
    Light *livingRoomLight = new Light();
    Fan *ceilingFan = new Fan();

    RemoteController *remote = new RemoteController();

    remote->setCommand(0, new LightCommand(livingRoomLight));
    remote->setCommand(1, new FanCommand(ceilingFan));

    // Simulate button presses (toggle behavior)
    cout << "--- Toggling Fan Button 1 ---" << endl;
    remote->pressButton(1); // ON
    remote->pressButton(1); // OFF

    cout << "--- Toggling Light Button 1 ---" << endl;
    remote->pressButton(0); // ON
    remote->pressButton(0); // OFF

    cout << "--- Pressing Unassigned Button 2 ---" << endl;
    remote->pressButton(2);

    // Clean up
    delete remote;
    delete livingRoomLight;
    delete ceilingFan;

    return 0;
}
