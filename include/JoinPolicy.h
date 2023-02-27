#pragma once
#include "Agent.h"
#include <vector>
#include "Simulation.h"

using namespace std;

class JoinPolicy {
    public:
        virtual int Join(vector<int> &coalitionGivenOffers, vector<int> &partyIdGivenOffers, Simulation &s)=0;
        virtual JoinPolicy* clone()=0;
        virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual int Join(vector<int> &coalitionGivenOffers, vector<int> &partyIdGivenOffers, Simulation &s);
        virtual JoinPolicy* clone();
        virtual ~MandatesJoinPolicy() = default;
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual int Join(vector<int> &coalitionGivenOffers, vector<int> &partyIdGivenOffers, Simulation &s); // refrence to a vector to pointers!
        virtual JoinPolicy* clone();
        virtual ~LastOfferJoinPolicy() = default;
};