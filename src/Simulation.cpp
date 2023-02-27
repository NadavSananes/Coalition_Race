#include "../include/Simulation.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), coalitionsMandates(),
partiesByCoalitions()
{
    
    for (size_t i = 0; i < mAgents.size(); i = i + 1)
    {
        coalitionsMandates.push_back((mGraph.getParty(agents[i].getPartyId())).getMandates()); // Creating a vector with the number of mandates for each coalition.

        vector<int> coalition;
        partiesByCoalitions.push_back(coalition) ;  // creating the  coalitions lists.
        partiesByCoalitions[i].push_back(mAgents[i].getPartyId()) ;
       
    }

    for(size_t i = 0; i < mAgents.size(); i = i + 1){   
        mAgents[i].setGraph(&mGraph);  // initialing the graph* field.
        mAgents[i].CreateOffersVector(); // initialing the offers vector of each agent.
    }
    
}

void Simulation::step()
{
    for (int i = 0; i < mGraph.getNumVertices(); i = i + 1)
    {
        mGraph.getParty2(i)->step(*this);
    }
    
    for(Agent &agent: mAgents)
    {
        agent.step(*this);
    }
}


bool Simulation::shouldTerminate() const
{
    return (allJoined() || thereIsACoalition());
}

bool Simulation::allJoined() const
{
    for (int i = 0; i < mGraph.getNumVertices(); i = i + 1)
    {
        if(mGraph.getParty(i).getState() != Joined)
            return false;
    }
    return true;
}

bool Simulation::thereIsACoalition() const
{
    for (size_t i = 0; i < coalitionsMandates.size(); i = i + 1)
    {
        if(coalitionsMandates[i] >= 61)
            return true;
    }
    return false;
}
void Simulation::addAgent(Agent Agent)
{
    mAgents.push_back(Agent);
}
const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

vector<Agent> &Simulation::getAgents()
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}
void Simulation::updateMandates(int coalitionID, int num)
{
    coalitionsMandates[coalitionID] = coalitionsMandates[coalitionID] + num;
}

Graph& Simulation::getGraph2(){
    return mGraph;
}
int Simulation::getCoalitionMandates(int i){
    return coalitionsMandates[i];
}



/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    return partiesByCoalitions;
}

void Simulation::insertToPartyByCoaltion(int coalitionID, int partyID)
{
    partiesByCoalitions[coalitionID].push_back(partyID);
}
