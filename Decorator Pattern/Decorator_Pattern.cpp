#include<bits/stdc++.h>
using namespace std;

// Component Interface: defines a common interface for Mario and all power-up decorators.
class Character{
    public: 
    virtual string getAbilities() const = 0; 
    virtual ~Character() {}
}; 

// Concrete Component: Basic Mario character with no power-ups.
class Mario : public Character{
    public: 
    string getAbilities() const override{
        return "Mario"; 
    }
}; 

// Abstract Decorator: CharacterDecorator "is-a" Charatcer and "has-a" Character.
class CharacterDecorator : public Character{
    protected: 
    Character* character; 
    public: 
    CharacterDecorator(Character* c){
        this->character = c; 
    }
};

// Concrete Decorator: Height-Increasing Power-Up.
class HeighUP : public CharacterDecorator{
    public : 
    HeighUP(Character* c) : CharacterDecorator(c){ }

    string getAbilities() const override{
        return character->getAbilities() + "with HeightUP"; 
    }
}; 

// Concrete Decorator: Gun Shooting Power-Up.
class GunPowerUp : public CharacterDecorator {
public:
    GunPowerUp(Character* c) : CharacterDecorator(c) { }
    
    string getAbilities() const override {
        return character->getAbilities() + " with Gun";
    }
};
// Concrete Decorator: Star Power-Up (temporary ability).
class StarPowerUp : public CharacterDecorator {
public:
    StarPowerUp(Character* c) : CharacterDecorator(c) { }
    
    string getAbilities() const override {
        return character->getAbilities() + " with Star Power (Limited Time)";
    }
    
    ~StarPowerUp() {
        cout << "Destroying StarPowerUp Decorator" << endl;
    }
}; 

int main (){
    // Create a basic Mario character.
    Character* mario = new Mario(); 
    cout << "Basic Character: " << mario->getAbilities() << endl;

    // Decorate Mario with a HeightUp power-up.
    mario = new HeighUP(mario); 
    cout << "After HeightUp: " << mario->getAbilities() << endl;

    // Decorate Mario further with a GunPowerUp.
    mario = new GunPowerUp(mario);
    cout << "After GunPowerUp: " << mario->getAbilities() << endl;

    // Finally, add a StarPowerUp decoration.
    mario = new StarPowerUp(mario);
    cout << "After StarPowerUp: " << mario->getAbilities() << endl;

    delete mario;

    return 0;
}