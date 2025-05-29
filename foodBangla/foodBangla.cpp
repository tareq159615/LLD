#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Abstract class for Payment Method
class PaymentMethod
{
public:
    virtual bool pay(double amount) = 0;
    virtual string getName() const = 0;
    virtual ~PaymentMethod() = default;
};

// Concrete payment methods
class CashPayment : public PaymentMethod
{
public:
    bool pay(double amount) override
    {
        cout << "Paid " << amount << " in cash." << endl;
        return true;
    }

    string getName() const override
    {
        return "Cash";
    }
};

class BkashPayment : public PaymentMethod
{
public:
    bool pay(double amount) override
    {
        cout << "Paid " << amount << " using Bkash." << endl;
        return true;
    }

    string getName() const override
    {
        return "Bkash";
    }
};

class CardPayment : public PaymentMethod
{
public:
    bool pay(double amount) override
    {
        cout << "Paid " << amount << " using Card." << endl;
        return true;
    }

    string getName() const override
    {
        return "Card";
    }
};

class CartItem
{
private:
    string name;
    double price;

public:
    CartItem(string name, double price) : name(name), price(price) {}

    string getName() const { return name; }
    double getPrice() const { return price; }
};

class Cart
{
private:
    vector<CartItem> items;
    string restaurant;

public:
    Cart(string restaurant) : restaurant(restaurant) {}

    void addItem(const CartItem &item) { items.push_back(item); }
    vector<CartItem> getItems() const { return items; }
    string getRestaurant() const { return restaurant; }

    double getTotal() const
    {
        double total = 0;
        for (auto &item : items)
        {
            total += item.getPrice();
        }
        return total;
    }

    void clear() { items.clear(); }
};

class User
{
private:
    string name;
    Cart *cart;

public:
    User(string name, string restaurant) : name(name)
    {
        cart = new Cart(restaurant);
    }

    ~User()
    {
        delete cart;
    }

    string getName() const { return name; }
    Cart *getCart() const { return cart; }
};

class Order
{
protected:
    User *user;
    Cart *cart;
    string restaurant;
    vector<CartItem> items;
    double total;
    string orderType;
    PaymentMethod *paymentMethod;

public:
    Order(User *user, Cart *cart, string restaurant, vector<CartItem> items, double total, string orderType)
        : user(user), cart(cart), restaurant(restaurant), items(items), total(total), orderType(orderType), paymentMethod(nullptr) {}

    virtual ~Order() {}

    virtual void deliver() = 0;

    double getTotal() const { return total; }
    string getOrderType() const { return orderType; }
    vector<CartItem> getItems() const { return items; }
    string getRestaurant() const { return restaurant; }

    void setPaymentMethod(PaymentMethod *method) { paymentMethod = method; }
    PaymentMethod *getPaymentMethod() const { return paymentMethod; }

    bool processPayment()
    {
        if (!paymentMethod)
        {
            cout << "Please choose a payment method first" << endl;
            return false;
        }
        return paymentMethod->pay(total);
    }
};

// Concrete Order Types
class NowOrder : public Order
{
public:
    NowOrder(User *user, Cart *cart, string restaurant, vector<CartItem> items, double total, string orderType)
        : Order(user, cart, restaurant, items, total, orderType) {}

    void deliver() override
    {
        cout << "Delivering now order to " << user->getName() << endl;
    }
};

// Factory interface
class OrderFactory
{
public:
    virtual Order *createOrder(User *user, Cart *cart, string restaurant, vector<CartItem> items, double total, string orderType, PaymentMethod *paymentMethod) = 0;
    virtual ~OrderFactory() {}
};

// Concrete Factory
class NowOrderFactory : public OrderFactory
{
public:
    Order *createOrder(User *user, Cart *cart, string restaurant, vector<CartItem> items, double total, string orderType, PaymentMethod *paymentMethod) override
    {
        Order *order = new NowOrder(user, cart, restaurant, items, total, orderType);
        order->setPaymentMethod(paymentMethod);
        return order;
    }
};

class NotificationService
{
public:
    void notify(Order *order)
    {
        cout << "Notifying order placed for " << order->getRestaurant() << endl;
        cout << "Order Type: " << order->getOrderType() << endl;
        cout << "Payment Method: " << (order->getPaymentMethod() ? order->getPaymentMethod()->getName() : "None") << endl;
    }
};

class FoodBanga
{
private:
    NotificationService notificationService;

public:
    Order *checkoutNow(User *user, const string &orderType, PaymentMethod *paymentMethod)
    {
        Cart *cart = user->getCart();
        vector<CartItem> items = cart->getItems();
        double total = cart->getTotal();

        Order *order = (new NowOrderFactory())->createOrder(user, cart, cart->getRestaurant(), items, total, orderType, paymentMethod);

        if (!order->processPayment())
        {
            cout << "Payment failed. Order not placed." << endl;
            delete order;
            return nullptr;
        }

        order->deliver();
        notificationService.notify(order);
        cart->clear();

        return order;
    }
};

int main()
{
    User *user1 = new User("John", "Pizza Palace");
    Cart *cart = user1->getCart();
    cart->addItem(CartItem("Pizza", 400));
    cart->addItem(CartItem("Pepsi", 60));

    cout << "Cart items for " << user1->getName() << ":" << endl;
    for (auto &item : cart->getItems())
    {
        cout << "- " << item.getName() << " : " << item.getPrice() <<" tk"<< endl;
    }

    cout << "Total: " << cart->getTotal() <<" tk"<< endl;

    FoodBanga *foodBanga = new FoodBanga();

    // Select payment method (e.g., Bkash)
    PaymentMethod *payment = new BkashPayment();

    Order *order = foodBanga->checkoutNow(user1, "Now", payment);

    delete user1;
    delete foodBanga;
    delete payment;
    delete order;

    return 0;
}
