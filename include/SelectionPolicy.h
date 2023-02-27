#pragma once
#include "Party.h"
#include <vector>
#include "Agent.h"
using std::vector;

class Party;

class SelectionPolicy {
    public:
        virtual int select(vector<int> &offersPartyId, vector<int> & offersEdgeWeight, int coalitionID, Graph &graph)=0;
        virtual SelectionPolicy* clone()=0;
        virtual ~SelectionPolicy() = default;
 };

class MandatesSelectionPolicy: public SelectionPolicy{
    public:
        virtual int select(vector<int> &offersPartyId, vector<int> & offersEdgeWeight, int coalitionID, Graph &graph);
        virtual SelectionPolicy* clone();
        virtual ~MandatesSelectionPolicy() = default;
 };

class EdgeWeightSelectionPolicy: public SelectionPolicy{ 
    public:
        virtual int select(vector<int> &offersPartyId, vector<int> & offersEdgeWeight, int coalitionID, Graph &graph);
        virtual SelectionPolicy* clone();
        virtual ~EdgeWeightSelectionPolicy() = default;

};