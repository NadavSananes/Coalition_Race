#pragma once
#include <vector>
#include <string>


using std::string;
using std::vector;

class JoinPolicy;
class Simulation;
class Agent;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *);
    Party(const Party &other);
    Party(Party &&other);

    void step(Simulation &s);
    void setState(State state);
    void addOffer(int partyId, int coalitionId);
    State getState() const;
    int getMandates() const;
    int getID() const;
    int getTimer() const;
    const string &getName() const; 
    vector<int> getCoalitionGivenOffers() const;
    vector<int> getPartyIdGivenOffers() const;
    bool alreadyOffered(int coalitionID) const;
    JoinPolicy* getJoinPolicy() const;
    Party& operator=(const Party& other);
    Party& operator=(Party &&other);
    ~Party();

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    vector<int> coalitionGivenOffers;
    vector<int> partyIdGivenOffers;
};
