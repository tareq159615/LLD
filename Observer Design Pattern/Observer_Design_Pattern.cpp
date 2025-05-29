#include <bits/stdc++.h>
using namespace std;

class ISubscriber
{
public:
    virtual void update() = 0;
    virtual ~ISubscriber() {}
};

class IChannel
{
public:
    virtual void subscribe(ISubscriber *subscriber) = 0;
    virtual void unsubscribe(ISubscriber *subscriber) = 0;
    virtual void notifySubscribers() = 0;
    virtual ~IChannel() {}
};

class Channel : public IChannel
{
private:
    vector<ISubscriber *> subscribers;
    string name;
    string latestVideo;

public:
    Channel(const string &name)
    {
        this->name = name;
    }

    // Add a subscriber (avoid duplicates)
    void subscribe(ISubscriber *subscriber) override
    {
        if (find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end())
        {
            subscribers.push_back(subscriber);
        }
    }

    // Remove a subscriber if present
    void unsubscribe(ISubscriber *subscriber) override
    {
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if (it != subscribers.end())
        {
            subscribers.erase(it);
        }
    }

    // Notify all subscribers of the latest video
    void uploadVideo(const string &title)
    {
        latestVideo = title;
        cout << "\n[" << name << " uploaded \"" << title << "\"]\n";
        notifySubscribers();
    }

    void notifySubscribers() override
    {
        for (auto subscriber : subscribers)
        {
            subscriber->update();
        }
    }

    // Read viddeo data
    string getVideoData()
    {
        return "\ncheckout our new Video : " + latestVideo + "\n";
    }
};

// Concrete Observer: represents a subscriber to the channel
class Subscriber : public ISubscriber
{
private:
    string name;
    Channel *channel;

public:
    Subscriber(const string &name, Channel *channel)
    {
        this->name = name;
        this->channel = channel;
    }

    void update() override
    {
        cout << "Hey " << name << "," << channel->getVideoData();
    }
};

int main()
{
    // Create a channel and subscribers
    Channel *channel = new Channel("CoderArmy");

    Subscriber *subs1 = new Subscriber("Aziz", channel);
    Subscriber *subs2 = new Subscriber("Tareq", channel);

    channel->subscribe(subs1);
    channel->subscribe(subs2);

    channel->uploadVideo("Observer Pattern Tutorial");

    channel->unsubscribe(subs2);
    
    channel->uploadVideo("lld video");
}
