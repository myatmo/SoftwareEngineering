#include "include/ir.h"

using namespace std;
namespace votesys{
IR::IR(){
    winner = NULL;
    loser = NULL;
	transferVotes = {};
    candidateList = {};
}
IR::~IR(){
    for(int i=0;i<(int)candidateList.size();i++){
		delete candidateList[i];
	}
}

// set the candidate as winner
void IR::setWinner(Candidate *candidate) {winner = candidate;}

// set the candidate who got fewest votes as loser
void IR::setLoser(Candidate *candidate) {loser = candidate;}

// get the winner candidate
Candidate* IR::getWinner() {return winner;}

// return the candidate who got fewest vote
Candidate* IR::getLoser() {return loser;}

// return the transfer votes list for all candidates
vector<vector<int>> IR::getTransferVotes() {return transferVotes;}

Candidate* IR::countVote(string fn) {
	/*
	Purpose:	Count first-choice vote for all candidates, do transfer voting if require
				and, determine winning and losing candidates
	Input:		vector<Candidate> this->getCandidateList(); all the candidates object
	Return:		the candidate object who wins the election
	*/
    ofstream audit;
	audit.open(fn, std::ios_base::app);
	audit<<"Start IR Vote Counting Process...\n";
	// local variables:
	int minVotes;				// to save the minimum vote count
	vector<int> minIdx;			// to save the indices of the candidates who receive the lowest vote
	int majorityVote;			// to save the 50% of total votes
	int candidateLeft;			// to save the number of candidates left after elimination
	vector<int> idxRemainder;	// to save the indices of two candidates who tie
	int loserIdx;				// to save the index of the loser candidate
	vector<int> initialVote;	// to save the initial vote cout for all candidates

	// add initial vote cout to transferVotes
	for (int i = 0; i < (int)this->getCandidateList().size(); i++) {
		initialVote.push_back(this->getCandidateList()[i]->getNumVotes());
	}
	transferVotes.push_back(initialVote);
	// initialize candidateLeft to total number of candidates in list
	candidateLeft = getNumCandidates();

	// 1. calculate the 50% of total votes
	majorityVote = int(0.5 * getNumBallots());
    audit<<"Majority to win calculated: "<<to_string(majorityVote)<<endl;
	// 2. loop until there is a winner or only 2 candidates left
	while (candidateLeft > 2) {
		// initialize minVotes to overall total number of ballots
		minVotes = getNumBallots();
		// set minIdx to empty
		minIdx = {};
		// 2.1 if one candidate gets majority vote, set winner and return winner
		for (int i = 0; i < (int)this->getCandidateList().size(); i++) {
			// first check if the candidate has not been eliminated yet
			if (!this->getCandidateList()[i]->isEliminated()) {
				if (this->getCandidateList()[i]->getNumVotes() > majorityVote) {
					// set winner to this->getCandidateList()[i]
					setWinner(this->getCandidateList()[i]);
                    audit<<*getCandidateList()[i]<<" has majority!\n";
                    return winner;
				}
				// 2.2 get minimum vote counts and save it to minVoteCount
				if (minVotes > (int)this->getCandidateList()[i]->getNumVotes())
					minVotes = this->getCandidateList()[i]->getNumVotes();
			}
		}
        audit<<"Minimum vote count: "<<minVotes<<endl;
		// 2.3 get all candidates who got minimum votes, and save them to minIdx
		for (int i = 0; i < (int)this->getCandidateList().size(); i++) {
			if (!this->getCandidateList()[i]->isEliminated() && (int)this->getCandidateList()[i]->getNumVotes() == minVotes) {
				minIdx.push_back(i);
                audit<<"Adding loser to list in case of tie: "<<*getCandidateList()[i]<<endl;
			}
		}
		// 2.4 if there are more than one candidates who got minimum votes, call coinToss to select one
		if (minIdx.size() > 1) {
			// get index of loser candidate by calling coinToss
			loserIdx = coinToss(minIdx);
            audit<<"Coin toss made "<<*getCandidateList()[loserIdx]<<" the loser\n";
		}
		else {
			loserIdx = minIdx[0];
            audit<<*getCandidateList()[loserIdx]<<" is the loser\n";
		}
		// 2.5 eliminate the loser candidate by setting setCandidateEliminated to true, and set it to loser
		this->getCandidateList()[loserIdx]->setCandidateEliminated(true);
		setLoser(this->getCandidateList()[loserIdx]);
		// 2.6 call transferVote to transfer votes from the loser candidate
        audit<<"Transferring vote of the loser...\n";
		transferVote(fn);
		// reduce one from the candidateLeft
		candidateLeft--;
        audit<<to_string(candidateLeft)<<" candidates remain\n";
	}
	// 3. Only two candidates must have left after the loop
	// 3.1 get the two candidates left:
    audit<<"Only 2 candidates left check for majority or do coin toss\n";
	for (int i = 0; i < (int)this->getCandidateList().size(); i++) {
		if (!this->getCandidateList()[i]->isEliminated()) {
			idxRemainder.push_back(i);
		}
	}
	// 3.2 call coinToss to determine the winner between two canidates
	// sanity check if there are only 2 left
	if ((int)idxRemainder.size() == 2) {
		// check if one candidate get majority vote then return as winner
		for (int i = 0; i < (int)idxRemainder.size(); i++) {
			if ((int)this->getCandidateList()[i]->getNumVotes() > majorityVote) {
				// set winner to this->getCandidateList()[i]
				setWinner(this->getCandidateList()[i]);
                audit<<"Winner found!\n";
                audit<<*getCandidateList()[i]<<" won the election!\n";
                return winner;
			}
		}
		// if not, call coinToss to determine a winner
		if (winner==NULL) {
			audit<<"Candidates Tie; running coinToss process...\n";
			setWinner(this->getCandidateList()[coinToss(idxRemainder)]);
            audit<<"Coin toss to determine winner, no majority found\n";
            audit<<*getCandidateList()[coinToss(idxRemainder)]<<" is the winner!\n";
            //cout<<this->getCandidateList()[coinToss(idxRemainder)]->getName()<<" winner!\n";
		}
	}
    //cout<<winner->getName()<<" winner!\n";
    audit.close();
	return winner;
}

void IR::transferVote(string fn) {
	/*
	Purpose:	Transfer votes from the candidate with the fewest votes to other candidates
	Input:		Candidate loser; the candidate with the fewest votes
				vector<Candidate> this->getCandidateList(); all candidate list
	Return:		None
	*/
    ofstream audit;
	audit.open(fn, std::ios_base::app);
	audit<<"Start Transfering Votes Process...\n";
	// local variables:
	Ballot* transferVote;	// to store the current ballot from lowestVote candidate
	int nextRank;			// to save the index of the next ranked candidate
	int idx;				// to save the index of the candidate who gets the transfer vote
	vector<int> updatedVote;// to save the number of votes after the transferred process
	// 1. get each ballot of the loser candidate
	for (int j = 0; j < loser->getNumVotes(); j++) {
		transferVote = loser->popBallotList(j);
        audit<<"Transferring ballot "<<to_string(transferVote->getID())<<" to next choice\n";
		// 1.1 get the next rank in the ballot
		nextRank = transferVote->getRank() + 1;
		idx = -1;
		// 1.2 transfer the ballot to the corresponding candidate
		// if 2nd preference candidate is already eliminated, look for 3rd and so on
		// get the corresponding index of this->getCandidateList()
        audit<<"Looking for choice number "<<to_string(nextRank)<<endl;
		while (nextRank < getNumCandidates() && idx == -1) {
			for (int i = 0; i < getNumCandidates(); i++) {
				if (!this->getCandidateList()[i]->isEliminated() && transferVote->getVote()[i] == nextRank) {
					idx = i;
                    audit<<"Found choice "<<to_string(nextRank)<<", candidate "<<*getCandidateList()[i]<<" gets the vote!\n";
				}
			}
			if (idx == -1) {
                audit<<"Choice "<<to_string(nextRank)<<" not found\n";
                nextRank++;
                audit<<"Incrementing rank to "<<to_string(nextRank)<<endl;
            }
		}
		// set the loser ballot rank to nextRank
		transferVote->setRank(nextRank);
		// push the ballot to the corresponding candidate
		if (idx != -1) {
			this->getCandidateList()[idx]->pushBallotList(transferVote);
		}
	}
	// 2. update numVotes for each candidate and save transfer vote in transferVotes
	for (int i = 0; i < getNumCandidates(); i++) {
		if (!this->getCandidateList()[i]->isEliminated()) {
			this->getCandidateList()[i]->setNumVotes(this->getCandidateList()[i]->getBallotList().size());
            audit<<"Setting "<<*getCandidateList()[i]<<" new number of votes to "<<to_string(getCandidateList()[i]->getBallotList().size())<<endl;
		}
		else {
			this->getCandidateList()[i]->setNumVotes(0);
            audit<<*getCandidateList()[i]<<" Eliminated!\n";
		}
		updatedVote.push_back(this->getCandidateList()[i]->getNumVotes());
        audit<<"Updated votes for "<<*getCandidateList()[i]<<endl;
	}
	// save updated transfer votes in transferVotes
	transferVotes.push_back(updatedVote);
    audit.close();
}
}