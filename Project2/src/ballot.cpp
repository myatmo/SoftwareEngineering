#include "include/ballot.h"
#include <iostream>
#include <math.h>

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

// return true if the ballot is invalidated, false otherwise
bool Ballot::isInvalidated() {return invalidated;}

// set invalidated for the ballot
void Ballot::setInvalidated(bool value) {invalidated = value;}

void Ballot::checkInvalidBallot() {
	// Check whether there are 0.5 or more ranked candidates in the ballot
	// local variables:
	int count = 0;	// to save the count of valid rankings in the ballot
	for (int i=0;  i < (int)this->rankings.size(); i++) {
		// if the rank in the ballot is not zero, it's valid and thus increment the count
		if (this->rankings[i] != 0)
			count ++;
	}
	// check if the total valid count is greater than 0.5 of total rankings then set Invalidated in ballot to false
	// otherwise true
	if (count >= int(ceil(0.5 * this->rankings.size()))) {
		this->setInvalidated(false);
	}
    else {
        this->setInvalidated(true);
    }
}
}