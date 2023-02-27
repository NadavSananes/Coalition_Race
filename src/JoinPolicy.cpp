#include "../include/JoinPolicy.h"
#include "../include/Simulation.h"
#include <vector>
using std::vector;


int MandatesJoinPolicy::Join(vector<int> &coalitionGivenOffers, vector<int> &partyIdGivenOffers, Simulation &s){
    int ans = 0;
    for (size_t i = 1; i < coalitionGivenOffers.size(); i = i + 1)
    {
        if(s.getCoalitionMandates(coalitionGivenOffers[i]) >
               s.getCoalitionMandates(coalitionGivenOffers[ans]))
               ans = i;
    }
    return ans;
    
}
JoinPolicy* MandatesJoinPolicy::clone(){
    return new MandatesJoinPolicy();
}

int LastOfferJoinPolicy::Join(vector<int> &coalitionGivenOffers, vector<int> &partyIdGivenOffers, Simulation &s){
        return partyIdGivenOffers.size() - 1;  // return the last element in the vector.
}
JoinPolicy* LastOfferJoinPolicy::clone(){
    return new LastOfferJoinPolicy();
}
