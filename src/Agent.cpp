#include "../include/Agent.h"


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy),
 coalitionID(agentId), offersPartyId(), offersEdgeWeight(), graph(nullptr) {}

Agent::Agent(const Agent &other) : mAgentId(other.getId()), mPartyId(other.getPartyId()), mSelectionPolicy((other.getSelectionPolicy())->clone()) 
,coalitionID(other.getCoalitionID()), offersPartyId(other.getOffersPartyId()) , offersEdgeWeight(other.getOffersEdgeWeight()), graph(other.getGraph()) {}

Agent::Agent(Agent &&other) : mAgentId(other.getId()), mPartyId(other.getPartyId()), mSelectionPolicy((other.getSelectionPolicy())) 
,coalitionID(other.getCoalitionID()), offersPartyId(move(other.offersPartyId)) , offersEdgeWeight(move(other.offersEdgeWeight)), 
 graph(other.getGraph())
{
 other.mSelectionPolicy = nullptr;
 other.graph = nullptr;
}

int Agent::getId() const
{
    return mAgentId;
}
void Agent::setId(int i){
    mAgentId = i;
}

int Agent::getPartyId() const
{
    return mPartyId;
}
void Agent::setCoalitionID(int i){
    coalitionID = i;
}
int Agent::getCoalitionID() const
{
    return coalitionID;
}
SelectionPolicy* Agent::getSelectionPolicy() const
{  
    return mSelectionPolicy;
}
void Agent::setGraph(Graph* otherGraph){
    graph = otherGraph;
}
Graph *Agent::getGraph() const{
    return graph;
}
void Agent::resetOffers(){
    offersEdgeWeight.clear();
    offersPartyId.clear();
}


  void Agent::clone(Simulation &s, int partyID){
    Agent toJoinAgent = Agent(*this);
    toJoinAgent.resetOffers();
    toJoinAgent.setId(s.getAgents().size());  // correcting the agent id, partyId and creating the offers vectors.
    toJoinAgent.setPartyID(partyID);
    toJoinAgent.CreateOffersVector();
    s.addAgent(toJoinAgent);         // pushing the cloned agent to the agents vector.
  }

void Agent::setPartyID (int partyID){
    mPartyId = partyID;
};

void Agent::CreateOffersVector(){
    for (int i = 0; i < graph->getNumVertices(); i = i + 1)
    {
        if (graph->getEdgeWeight(mPartyId, i) > 0 && (graph->getParty(i)).getState() != Joined)
        {
            offersPartyId.push_back(graph->getParty(i).getID());  // inserting the partyId.
            offersEdgeWeight.push_back(graph->getEdgeWeight(mPartyId, i));  // inserting the EdgeWeight.
        }
        
    }
    
    
}
void Agent::step(Simulation &)
{
    if(offersPartyId.size() > 0){
        int toOffer = mSelectionPolicy->select(offersPartyId, offersEdgeWeight, coalitionID, *graph);
        if(toOffer != -1){
            (graph->getParty2(offersPartyId[toOffer]))->addOffer(mPartyId, coalitionID);

            offersPartyId.erase(offersPartyId.begin() + toOffer);
            offersEdgeWeight.erase(offersEdgeWeight.begin() + toOffer);
        }
       
    } 
    
}

vector<int> Agent::getOffersPartyId() const{
    return offersPartyId;
}
vector<int> Agent::getOffersEdgeWeight() const{
    return offersEdgeWeight;
}

Agent& Agent::operator=(const Agent &other){
    if(this != &other){
        this->~Agent();
        mAgentId = other.getId();
        mPartyId = other.getPartyId();
        mSelectionPolicy = other.getSelectionPolicy()->clone();
        coalitionID = other.getCoalitionID();
        offersPartyId = other.getOffersPartyId();
        offersEdgeWeight = other.getOffersEdgeWeight();
        graph = other.getGraph();
    }
    return *this;
}
Agent& Agent::operator=(Agent &&other){
    if(this != &other){
        this->~Agent();
        mAgentId = other.getId();
        mPartyId = other.getPartyId();
        mSelectionPolicy = other.getSelectionPolicy();
        coalitionID = other.getCoalitionID();
        offersPartyId = move(other.offersPartyId);
        offersEdgeWeight = move(other.offersEdgeWeight);
        graph = other.getGraph();

        other.mSelectionPolicy = nullptr;
        other.graph = nullptr;
    }
    return *this;
}
Agent::~Agent(){
    delete mSelectionPolicy;
}
