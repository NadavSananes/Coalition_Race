#include "../include/Party.h"
#include <vector>
#include "../include/JoinPolicy.h"
#include "../include/Simulation.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),
 timer(0), coalitionGivenOffers(), partyIdGivenOffers(){}

Party::Party(const Party &other) : mId(other.getID()), mName(other.getName()), mMandates(other.getMandates()),
    mJoinPolicy(other.getJoinPolicy()->clone()), mState(other.getState()),
    timer(other.getTimer()), coalitionGivenOffers(other.getCoalitionGivenOffers()), partyIdGivenOffers(other.getPartyIdGivenOffers()){}
    
Party::Party(Party &&other) : mId(other.getID()), mName(other.getName()), mMandates(other.getMandates()),
    mJoinPolicy(other.getJoinPolicy()), mState(other.getState()), timer(other.getTimer()), 
    coalitionGivenOffers(move(other.coalitionGivenOffers)), partyIdGivenOffers(move(other.partyIdGivenOffers))
{
    other.mJoinPolicy = nullptr;
}
int Party::getTimer() const{
    return timer;
}

vector<int> Party::getCoalitionGivenOffers() const{
    return coalitionGivenOffers;
}
vector<int> Party::getPartyIdGivenOffers() const{
    return partyIdGivenOffers;
}
State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}
JoinPolicy* Party::getJoinPolicy() const{
    return mJoinPolicy;
}
int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}


void Party::addOffer(int partyId, int coalitionId)
{
    coalitionGivenOffers.push_back(coalitionId);
    partyIdGivenOffers.push_back(partyId);
    if(mState == Waiting)       
        setState(CollectingOffers);
}

bool Party::alreadyOffered(int coalitionID) const
{
    bool ans = false;
    for (size_t i = 0; i < coalitionGivenOffers.size(); i = i + 1)
    {
        if(coalitionGivenOffers[i] == coalitionID)
            return true;
    }
    return ans;
}

int Party:: getID() const{
    return mId ;
};

void Party::step(Simulation &s)
{
    if(mState == CollectingOffers){    // check condition
     timer++;                      
     if(timer == 3){                 // it is time to choose.
        int toJoin = mJoinPolicy->Join(coalitionGivenOffers, partyIdGivenOffers, s);  // call for the function Join who need to select who to join.
        setState(Joined);            
        s.updateMandates(coalitionGivenOffers[toJoin], getMandates());
        s.insertToPartyByCoaltion(coalitionGivenOffers[toJoin], mId);
        Agent& agentToJoin = ((s.getAgents())[coalitionGivenOffers[toJoin]]);
        agentToJoin.clone(s, getID()); // clone the agent.
        }

    }
}


 Party& Party::operator=(const Party& other){
    if(this != &other){
        this->~Party();
        mId = other.getID();
        mName = other.getName();
        mMandates = other.getMandates();
        mJoinPolicy = other.getJoinPolicy()->clone();
        mState = other.getState();
        timer = other.getTimer();
        coalitionGivenOffers = other.getCoalitionGivenOffers();
        partyIdGivenOffers = other.getPartyIdGivenOffers();
    }

    return *this;
 }
 Party& Party::operator=(Party&& other){
    if(this != &other){
        this->~Party();
        mId = other.getID();
        mName = other.getName();
        mMandates = other.getMandates();
        mJoinPolicy = other.getJoinPolicy();
        mState = other.getState();
        timer = other.getTimer();

        coalitionGivenOffers = move(other.coalitionGivenOffers);
        partyIdGivenOffers = move(other.partyIdGivenOffers);

        other.mJoinPolicy = nullptr;
    }
    
    return *this;
 }
 
Party::~Party(){
    delete mJoinPolicy;
}


