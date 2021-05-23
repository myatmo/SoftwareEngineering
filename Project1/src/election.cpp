#include "include/election.h"

using namespace std;
namespace votesys{
Election::Election(){
	string votingType = "";
	vector<Candidate*> candidateList = {};
}
Election::~Election(){}

// set the type of voting
void Election::setvotingType(string voteType) {votingType = voteType;}

// set the total number of ballots
void Election::setNumBallots(int num) {numBallots = num;}

// set the total number of candidates
void Election::setNumCandidates(int num) {numCandidates = num;}

// return the type of voting
string Election::getVotingType() {return votingType;}

// return the total number of ballots
int Election::getNumBallots() {return numBallots;}

// return the total number of candidates
int Election::getNumCandidates() {return numCandidates;}

// get all the candidate list
vector<Candidate*> Election::getCandidateList() {return candidateList;}

// add new candidate to the list
void Election::pushCandidateList(Candidate *newCandidate) {candidateList.push_back(newCandidate);}

int Election::coinToss(vector<int> numbers) {
	/*
	Purpose:	Randomly choose one number from the list of integers
	Input:		vector<int>  numbers; list of indices in candidateList
	Return:		The index of the chosen candidate object
	*/
	// local variable:	int  chosenNum;
	int chosenNum;
	// srand(time(NULL));	// to get true random number each time
	// choose a random number from numbers list and save it to chosenNum:
	chosenNum = rand() % numbers.size() + 0;
	return numbers[chosenNum];
}
}