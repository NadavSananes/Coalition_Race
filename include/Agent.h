#pragma once
#include <vector>
#include "Graph.h"
#include "Simulation.h"
#include "SelectionPolicy.h"

using namespace std;

class SelectionPolicy;
class Simulation;
class Graph;
class Party;
class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(const Agent &other);
    Agent(Agent &&other);

    
    void setId(int i);
    void step(Simulation &);    
    void setCoalitionID(int i);
    void setGraph(Graph* otherGraph);
    void CreateOffersVector();
    void clone(Simulation &s, int partyID);
    void setPartyID (int partyID);
    void resetOffers();

    int getCoalitionID() const;
    int getPartyId() const;
    int getId() const;

    SelectionPolicy *getSelectionPolicy() const;
    Graph *getGraph() const;
    
    vector<int> getOffersEdgeWeight() const;
    vector<int> getOffersPartyId() const;
    
    Agent& operator=(const Agent &other);
    Agent& operator=(Agent &&other);
    ~Agent();
    
   

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int coalitionID;
    vector<int> offersPartyId;
    vector<int> offersEdgeWeight;
    Graph *graph;

};
