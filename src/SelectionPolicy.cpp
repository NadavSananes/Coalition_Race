#include "../include/SelectionPolicy.h"

int MandatesSelectionPolicy::select(vector<int> &offersPartyId, vector<int> &offersEdgeWeight, int coalitionID, Graph &graph){
    int ans = -1;
    
    for (size_t i = 0; i < offersPartyId.size(); i++)
    {
        if(graph.getParty(offersPartyId[i]).getState() != Joined && !graph.getParty(offersPartyId[i]).alreadyOffered(coalitionID)){
            if(ans == -1)
                ans = i;
            else{
                if(graph.getParty(offersPartyId[i]).getMandates() > graph.getParty(offersPartyId[ans]).getMandates())
                    ans = i;
            }
        }

        else{
            offersPartyId.erase(offersPartyId.begin() + i);
            offersEdgeWeight.erase(offersEdgeWeight.begin() + i);
        }

    }
    return ans;
    }

SelectionPolicy* MandatesSelectionPolicy::clone(){
    return new MandatesSelectionPolicy();

}
int EdgeWeightSelectionPolicy::select(vector<int> &offersPartyId, vector<int> &offersEdgeWeight, int coalitionID, Graph &graph) {
    int ans = -1;
    int size = offersPartyId.size();
    for (int i = 0; i < size; i++)
    {
        if(graph.getParty(offersPartyId[i]).getState() != Joined && !graph.getParty(offersPartyId[i]).alreadyOffered(coalitionID)){
            if(ans == -1)
                ans = i;
            else{
                if(offersEdgeWeight[i] > offersEdgeWeight[ans])
                    ans = i;
            }
        }
        else
        {  
            offersPartyId.erase(offersPartyId.begin() + i);
            offersEdgeWeight.erase(offersEdgeWeight.begin() + i);
            i = i - 1;
            size = size - 1;
        }

    }
    return ans;
}

SelectionPolicy* EdgeWeightSelectionPolicy::clone() {
    return new EdgeWeightSelectionPolicy();
}