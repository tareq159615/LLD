#include <bits/stdc++.h>
using namespace std;

// Product 1 --> Burger
class Burger {
public:
    virtual void prepare() = 0;
    virtual ~Burger() {} // Added virtual destructor
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger with bun, patty, and ketchup!" << endl;
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Burger with bun, patty, ketchup, and lettuce!" << endl;
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger with bun, patty, ketchup, lettuce, cheese, and special sauce!" << endl;
    }
};

class BasicWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Wheat Burger with wheat bun, patty, and ketchup!" << endl;
    }
};

class StandardWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Wheat Burger with wheat bun, patty, ketchup, and lettuce!" << endl;
    }
};

class PremiumWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Wheat Burger with wheat bun, patty, ketchup, lettuce, cheese, and special sauce!" << endl;
    }
};

// Product 2 --> GarlicBread
class GarlicBread {
public:
    virtual void prepare() = 0;
    virtual ~GarlicBread() {} // Added virtual destructor
};

class BasicGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Basic Garlic Bread with butter and garlic!\n";
    }
};

class CheeseGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Cheese Garlic Bread with butter, garlic, and cheese!\n";
    }
};

class BasicWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Basic Wheat Garlic Bread with wheat bread, butter, and garlic!\n";
    }
};

class CheeseWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Cheese Wheat Garlic Bread with wheat bread, butter, garlic, and cheese!\n";
    }
};

// Factory and its concretions
class MealFactory {
public:
    virtual Burger* createBurger(string type) = 0;
    virtual GarlicBread* createGarlicBread(string type) = 0;
    virtual ~MealFactory() {} // Added virtual destructor
};

class SinghBurger : public MealFactory {
public:
    Burger* createBurger(string type) override {
        if (type == "BasicBurger") return new BasicBurger();
        else if (type == "StandardBurger") return new StandardBurger();
        else if (type == "PremiumBurger") return new PremiumBurger();
        return nullptr;
    }

    GarlicBread* createGarlicBread(string type) override {
        if (type == "BasicGarlicBread") return new BasicGarlicBread();
        else if (type == "CheeseGarlicBread") return new CheeseGarlicBread();
        return nullptr;
    }
};

class KingBurger : public MealFactory {
public:
    Burger* createBurger(string type) override {
        if (type == "BasicWheatBurger") return new BasicWheatBurger();
        else if (type == "StandardWheatBurger") return new StandardWheatBurger();
        else if (type == "PremiumWheatBurger") return new PremiumWheatBurger();
        return nullptr;
    }

    GarlicBread* createGarlicBread(string type) override {
        if (type == "BasicWheatGarlicBread") return new BasicWheatGarlicBread();
        else if (type == "CheeseWheatGarlicBread") return new CheeseWheatGarlicBread();
        return nullptr;
    }
};

int main() {
    cout << "---------------------------------------------" << endl;
    cout << "Welcome to Burger Factory!" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Choose your burger type:" << endl;
    cout << "1. Basic Burger" << endl;
    cout << "2. Standard Burger" << endl;
    cout << "3. Premium Burger" << endl;
    cout << "4. Basic Wheat Burger" << endl;
    cout << "5. Standard Wheat Burger" << endl;
    cout << "6. Premium Wheat Burger" << endl;
    cout << "Please enter your choice (1-6): ";

    int burgerChoice;
    cin >> burgerChoice;

    string burgerType;
    switch (burgerChoice) {
        case 1: burgerType = "BasicBurger"; break;
        case 2: burgerType = "StandardBurger"; break;
        case 3: burgerType = "PremiumBurger"; break;
        case 4: burgerType = "BasicWheatBurger"; break;
        case 5: burgerType = "StandardWheatBurger"; break;
        case 6: burgerType = "PremiumWheatBurger"; break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }

    int need;
    cout << "You need bread ?" << endl;
    cout << "1. YES" << "\n" << "2. NO" << "\n" << ">>> "; 
    cin >> need;

    GarlicBread* garlicBread = nullptr;
    string breadType;
    int breadChoice = 0;

    if(need == 1) { 
        cout << "Choose your garlic bread type:" << endl;
        cout << "1. Basic Garlic Bread" << endl;
        cout << "2. Cheese Garlic Bread" << endl;
        cout << "3. Basic Wheat Garlic Bread" << endl;
        cout << "4. Cheese Wheat Garlic Bread" << endl;
        cout << "Please enter your choice (1-4): ";

        cin >> breadChoice;

        switch (breadChoice) {
            case 1: breadType = "BasicGarlicBread"; break;
            case 2: breadType = "CheeseGarlicBread"; break;
            case 3: breadType = "BasicWheatGarlicBread"; break;
            case 4: breadType = "CheeseWheatGarlicBread"; break;
            default:
                cout << "Invalid choice!" << endl;
                return 1;
        }
    }

    // Improved factory selection logic
    MealFactory* factory;
    if (breadChoice >= 3 || burgerChoice >= 4) {
        factory = new KingBurger(); // Use KingBurger for wheat products
    } else {
        factory = new SinghBurger(); // Use SinghBurger for regular products
    }

    Burger* burger = factory->createBurger(burgerType);
    if (need == 1) {
        garlicBread = factory->createGarlicBread(breadType);
    }

    if (burger) {
        burger->prepare();
        delete burger;
    } else {
        cout << "Failed to create burger!" << endl;
    }

    if (need == 1) {
        if (garlicBread) {
            garlicBread->prepare();
            delete garlicBread;
        } else {
            cout << "Failed to create garlic bread!" << endl;
        }
    }

    delete factory;
    return 0;
}
