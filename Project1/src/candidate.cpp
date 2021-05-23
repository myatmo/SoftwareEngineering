#include "include/candidate.h"
#include <iostream>
using namespace std;
namespace votesys{
// Set initial filler values for candidate class
Candidate::Candidate(){
    candidateName = "noname";
    party = 'N';
    numVotes = -1;
    eliminated = false;
    ballotList = {};
}// Clear ballot list
Candidate::~Candidate(){
    for(int i=0;i<(int)ballotList.size();i++){
        delete ballotList[i];
    }
}
// Return the attributes of a candidate
Candidate& Candidate::operator=(const Candidate &candidate){
    candidateName = candidate.candidateName;
    party = candidate.party;
    numVotes = candidate.numVotes;
    eliminated = candidate.eliminated;
    ballotList = candidate.ballotList;
    return *this;
}// Format a statement for a candidate's name/party/vote total
ostream& operator<<(ostream& os, const Candidate& cand){
    os<<cand.candidateName<<", "<<cand.party<<" with "<<cand.numVotes;
    return os;
}// Compare names of two candidates
bool operator==(const Candidate& cand1, const Candidate& cand2){
    if(cand1.candidateName == cand2.candidateName)return true;
    else return false;
}

// Set a candidate's name
void Candidate::setName(string name) {candidateName = name;}
// Set a candidate's party 
void Candidate::setParty(char name) {party = name;}
// Set a candidate's vote count
void Candidate::setNumVotes(int num) {
    numVotes = num;
    if(num<=0){
        ballotList = {};
    }
}
// Set Eliminated status of a candidate (used in IR transfering)
void Candidate::setCandidateEliminated(bool value) {eliminated = value;}
// Retrieve a candidate's name
string Candidate::getName() {return candidateName;}
// Retrieve a candidate's party
char Candidate::getParty() {return party;}
// Retrieve a candidate's vote count
int Candidate::getNumVotes() {return numVotes;}
// Check eliminated status of a candidate
bool Candidate::isEliminated() {return eliminated;}
// Retrieve list of candidates
vector<Ballot*> Candidate::getBallotList() {return ballotList;}
// Add a candidate to the ballot list
void Candidate::pushBallotList(Ballot*  newBallot) {ballotList.push_back(newBallot);}
// Remove a candidate from the ballot list
Ballot* Candidate::popBallotList(int i){
    Ballot* ret = ballotList[i];
    return ret;
}
}