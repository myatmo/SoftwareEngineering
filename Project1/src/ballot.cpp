#include "include/ballot.h"
#include <iostream>

using namespace std;
namespace votesys{
// Set initial filler values for ballot class
Ballot::Ballot(){
    rankings={};
    nextRank=1;
    ballID = -1;
}
Ballot::~Ballot(){}

// Returns pointer with rankings and next rank
Ballot& Ballot::operator=(const Ballot &other){
    this->rankings = other.rankings;
    this->nextRank = other.nextRank;
    return *this;
}
// Formats a statement of ballot ID's along with their rankings and size
ostream& operator<<(ostream& os, const Ballot& ball){
    os<<"Ballot: "<<ball.ballID<<", {";
    for(int i=0; i<(int)ball.rankings.size()-1;i++){
        os<<ball.rankings[i]<<",";
    }
    os<<ball.rankings[(int)ball.rankings.size()-1]<<"}";
    return os;
}// Checks the equality between two input ballots
bool operator==(const Ballot& ball1, const Ballot& ball2){
    if(ball1.ballID == ball2.ballID)return true;
    else return false;
}
// Retrieves ID of a ballot
int Ballot::getID(){return ballID;}
// Sets ID of a ballot
void Ballot::setID(int id){ballID=id;}

void Ballot::setVote(string values) {
    // separate values by comma, convert those to int and set thoese int values to rankings
    stringstream ss(values);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        // check if it's empty then set it to zero; this is for both IR and OPL
        if (substr.empty())
            substr = "0";
        rankings.push_back(stoi(substr));
    }
}

// get the nextRank value
void Ballot::setRank(int rank) {nextRank = rank;}

// return the list of rankings
vector<int> Ballot::getVote() {return rankings;}

// return the nextRank value
int Ballot::getRank() {return nextRank;}
}