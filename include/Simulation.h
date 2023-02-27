#pragma once
#include "Graph.h"
#include "Agent.h"
#include "Party.h"
#include <vector>
using std::string;
using std::vector;
using namespace std;
class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;
    vector<Agent> &getAgents();
    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;    
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const ;    
    void updateMandates(int coalitionID, int num);
    bool allJoined()const;
    bool thereIsACoalition()const;
    Graph &getGraph2();
    void insertToPartyByCoaltion(int coalitionID, int partyID);
    void addAgent(Agent Agent);
    int getCoalitionMandates(int i);

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<int> coalitionsMandates;
    vector<vector<int>> partiesByCoalitions;
};
