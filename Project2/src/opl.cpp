#include "include/opl.h"

using namespace std;
namespace votesys{
OPL::OPL(){
    firstSeats = {}; 		// to append the seats from first allocation
    remainingVotes = {}; 	// to append the remaining votes after first seat allocation
    secondSeats = {0,0,0}; 	// to set the seats from second allocation
    republicans = {};		// to append the republicans to a list
    democrats = {};			// to append the democrats to a list
    independent = {};		// to appends the independents to a list
    winners = {};			// to append the winners to a list
	numSeats=0;
	quota=0;
	repVotes=0;
	demVotes=0;
	indVotes=0;
	numBallots = 0;
}
OPL::~OPL(){
	// delete all the dynamic candidates
	for(int i=0;i<(int)republicans.size();i++){
		delete republicans[i];
	}
	for(int i=0;i<(int)democrats.size();i++){
		delete democrats[i];
	}
	for(int i=0;i<(int)independent.size();i++){
		delete independent[i];
	}
}
// << operator override to make printing election info easier after election has been run
ostream& operator<<(ostream& os, const OPL& opl){
	os<<"Number of Seats: "<<opl.numSeats<<endl
	  <<"Number of Votes: "<<opl.numBallots<<endl
	  <<"Quota: "<<opl.quota<<endl;
	os<<"First Round Allocation: "<<opl.firstSeats[0]<<", "<<opl.firstSeats[1]<<", "<<opl.firstSeats[2]<<endl
	  <<"Second Round Allocation: "<<opl.secondSeats[0]<<", "<<opl.firstSeats[1]<<", "<<opl.firstSeats[2]<<endl
	  <<"Republican Candidates: \n";
	for(int i=0; i<(int)opl.republicans.size();i++){
		os<<*opl.republicans[i]<<endl;
	}
	os<<"Total Republican Votes: "<<opl.repVotes<<endl;
	os<<"Democrat Candidates: \n";
	for(int i=0; i<(int)opl.democrats.size();i++){
		os<<*opl.democrats[i]<<endl;
	}
	os<<"Total Democrat Votes: "<<opl.demVotes<<endl;
	os<<"Independent Candidates: \n";
	for(int i=0; i<(int)opl.independent.size();i++){
		os<<*opl.independent[i]<<endl;
	}
	os<<"Total Inpedendent Votes: "<<opl.indVotes<<endl;
	os<<"Winning Candidates: \n";
	for(int i=0; i<(int)opl.winners.size();i++){
		os<<*opl.winners[i]<<endl;
	}
	return os;
}
// getters and setters from number of seats to be filled for opl election
void OPL::setNumSeats(int numSeats){this->numSeats = numSeats;}
int OPL::getNumSeats(){return this->numSeats;}

// getters and setters for party votes
void OPL::setRepVotes(int repVotes){this->repVotes = repVotes;}
int OPL::getRepVotes(){return this->repVotes;}

void OPL::setDemVotes(int demVotes){this->demVotes = demVotes;}
int OPL::getDemVotes(){return this->demVotes;}

void OPL::setIndVotes(int indVotes){this->indVotes = indVotes;}
int OPL::getIndVotes(){return this->indVotes;}

// getters and setters for seat allocations in opl
void OPL::setFirstSeats(vector<int> firstSeats){this->firstSeats = firstSeats;}
vector<int> OPL::getFirstSeats(){return this->firstSeats;}

void OPL::setRemainingVotes(vector<int> remainingVotes){this->remainingVotes = remainingVotes;}
vector<int> OPL::getRemainingVotes(){return this->remainingVotes;}

void OPL::setSecondSeats(vector<int> secondSeats){this->secondSeats = secondSeats;}
vector<int> OPL::getSecondSeats(){return this->secondSeats;}

// getter for the lists in an opl election 'R'=republicans,'D'=democrats,'I'=independent,'W'=winners
vector<Candidate*> OPL::getList(char party){
    assert(party == 'R' || party == 'D' || party == 'I' || party == 'W');
    if(party == 'R'){return republicans;}
    else if(party == 'D'){return democrats;}
    else if(party == 'I'){return independent;}
    else{return winners;}
}
// push function for lists in opl election same rules as above
void OPL::pushList(char party, Candidate* candidate){
    assert(party == 'R' || party == 'D' || party == 'I' || party == 'W');
    if(party == 'R'){this->republicans.push_back(candidate);}
	else if(party == 'D'){this->democrats.push_back(candidate);}
    else if(party == 'I'){this->independent.push_back(candidate);}
    else{this->winners.push_back(candidate);}
}
// calculate quota (sets as well) and get quota functions
void OPL::calculateQuota(int numVotes, int numSeats, string fn){
	this->quota = numVotes / numSeats;
	ofstream audit;
	audit.open(fn, std::ios_base::app);
	audit<<"Quota Calculated: "<<to_string(numVotes)<<"/"<<to_string(numSeats)<< " = "<<to_string(quota)<<endl;
	audit.close();
}
int OPL::getQuota(){return this->quota;}

// calculate the first and second seat allocations for opl elections
vector<int> OPL::calculateSeatAllocation(vector<int> numVoteList, int quota, string fn){
	ofstream audit;
	audit.open(fn, std::ios_base::app);
	audit<<"Calculating Seat allocations\n";
	// local variables
	int allocatedSeats = 0;
	int remainingSeats=0; 
	vector<int> totalSeats; 
	vector<vector<Candidate*>> candidateList{republicans,democrats,independent};
	// iterate through the numVotes parameter and add seats for each party to the first allocation
	// if the number of seats allocated is larger than the number of candidates
	// make equal to the size of the candidate list
	vector<string> parties{"Republicans", "Democrats","Independents"};
	for (int i=0; i<(int)numVoteList.size(); i++){
        this->firstSeats.push_back(numVoteList[i] / quota);
		audit<<parties[i]<<" first allocation is "<<to_string(firstSeats[i])<<endl;
		if(this->firstSeats[i] > (int)candidateList.at(i).size()){
			this->firstSeats[i] = (int)candidateList.at(i).size();
			audit<<parties[i]<<" first allocation is too many! Set to "<<to_string(firstSeats[i])<<endl;
		}
	    this->remainingVotes.push_back(numVoteList[i] % quota);		// add remainder votes for second allocation
		allocatedSeats += (this->firstSeats[i]);					// update total allocated seats
		audit<<"Total seat allocation is now "<<to_string(allocatedSeats)<<endl;
    }
	remainingSeats = this->numSeats - allocatedSeats;
	audit<<"Remaining seats to fill is "<<to_string(remainingSeats)<<endl;
    vector<int> sortedIndexes{0,0,0};										// vector to sort values based on index
    vector<int> tempRemainingVotes = this->remainingVotes;			// store in temp variable to be manipulated

	// iterate through remaining votes to sort based on index value
	// append the max values index at each iteration to the sortedIndexes list
	for (int i=0; i<(int)numVoteList.size(); i++){
        int index = distance(tempRemainingVotes.begin(), max_element(tempRemainingVotes.begin(), tempRemainingVotes.end()));
        sortedIndexes[i]=index;
        tempRemainingVotes[index] = -1;			// set value to seminal value to ensure the
    }											// next highest will be found at next iteration

	// loop until remaining seats == 0
	// use the sorted indexes to access second seats and add 1 if the current value of second seats
	// and first seats is <= to the total number of candidates for that party
    int j = 0;
    while(remainingSeats > 0){
		if(this->secondSeats[sortedIndexes[j]] + this->firstSeats[sortedIndexes[j]]<(int)candidateList.at(sortedIndexes[j]).size()){
			this->secondSeats[sortedIndexes[j]] += 1;
			audit<<parties[sortedIndexes[j]]<<" get another seat in second alloaction for "<<to_string(secondSeats[sortedIndexes[j]])<<" second seat total\n";
			remainingSeats --;
			audit<<"Remaining seats to fill is now "<<to_string(remainingSeats)<<endl;
		}
        j++;
		if(j==3){			// reset to 0 for another round of allocation
			j=0;
		} 
    }

	// iterate through totalSeats and add firstseats+secondseats to the return list, total seats
	for (int i=0; i<(int)numVoteList.size(); i++){
		totalSeats.push_back((int)(this->firstSeats[i]+this->secondSeats[i]));
		audit<<"Total Seats is now "<<to_string(totalSeats[i])<<" for "<<parties[i]<<endl;
    }
	audit.close();
	return totalSeats;
}

// opl elections main function that takes in total number of ballots and assembles
// the winners list for the election
bool compareDecending(Candidate* cand1, Candidate* cand2) {return (cand1->getNumVotes() > cand2->getNumVotes());}
void OPL::countVote(int numBallots, string fn){
	ofstream audit;
	audit.open(fn, std::ios_base::app);
	audit<<"Counting Votes\n";
	// local variables
	vector<int> numVoteList{0,0,0}; 
	vector<int> totalSeats{0,0,0};
	
	// calcualte the quota for opl election
	// this function will set the quota attribute

	calculateQuota(numBallots, this->numSeats, fn);
	audit<<"Calculate seat vote total for each party\n";
	// iterate through all party lists and add each candidates votes to the
	// total count of votes for each party
	for (int i=0; i<(int)this->republicans.size(); i++){
		this->repVotes += (int)this->republicans.at(i)->getNumVotes();
    }
	audit<<"Republicans have "<<to_string(repVotes)<<" total votes\n";
	for (int i=0; i<(int)this->democrats.size(); i++){
		this->demVotes += (int)this->democrats.at(i)->getNumVotes();
    }
	audit<<"Democrats have "<<to_string(demVotes)<<" total votes\n";

	for (int i=0; i<(int)this->independent.size(); i++){
		this->indVotes += (int)this->independent.at(i)->getNumVotes();
    }
	audit<<"Independents have "<<to_string(indVotes)<<" total votes\n";

	// push these votes to the numVotes list for use in calculateSeatAllocation
	numVoteList[0]=this->repVotes;
	numVoteList[1]=this->demVotes;
	numVoteList[2]=this->indVotes;

	// get the total seats for each party with this function
	totalSeats = calculateSeatAllocation(numVoteList, this->quota, fn);
	// sort each party list based on the number of votes each candidate has
	// the overloaded < and > operators in candidate class take care of this
	// they are overloaded to be opposite for this function so it gives a descending order list
	audit<<"Sorting parties based on number of votes per candidate\n";
    sort(this->republicans.begin(), this->republicans.end(),compareDecending);
    sort(this->democrats.begin(), this->democrats.end(),compareDecending);
    sort(this->independent.begin(), this->independent.end(),compareDecending);

	// for republicans
	// checking if there are candidates who got the same votes
	vector<int> sameIdx = {};	// to save all the candidate's indices who got same number of votes
	int chosenIdx = -1;	// to save the chosen candidate's index
	int lastNum;		// to save the number of votes for the candidate who get the last seat
	if(!republicans.empty()){		
		if(totalSeats[0]>0){
			lastNum = this->republicans.at(totalSeats[0]-1)->getNumVotes();
		}
		
		
		// get all the indices that are the same as the first index vote count, then save those in sameIdx
		for (int i=0; i<(int)this->republicans.size(); i++){
			if(this->republicans.at(i)->getNumVotes() == lastNum) {
				sameIdx.push_back(i);
			}
		}

		// based on each parties n allocated seats, add the first n candidates from each party list
		for (int i=0; i<totalSeats[0]; i++){
			Candidate* cand = new Candidate();
			// check if the candidate tie with others, if yes play coinToss to determine the winners
			// the condition to check this is a bit tricky; we first need to check if there are duplicates by checking sameIdx.size > 1
			// then we need to check how many seat left and how many candidates to fill up; if there are more candidates with the same votes than seat left
			// call coinToss to choose one
			if ((int)sameIdx.size() > 1 && (int)sameIdx.size() > totalSeats[0]-i && this->republicans.at(i)->getNumVotes() == lastNum) {
				chosenIdx = coinToss(sameIdx);
				cout << "Calling CoinToss. Republicans who win: " << this->republicans.at(chosenIdx)->getName() << ", seatLeft: " << totalSeats[0]-i << "\n";
				cand = this->republicans.at(chosenIdx);
				// delete the winner candidate's index from sameIdx
				sameIdx.erase(std::find(sameIdx.begin(), sameIdx.end(), chosenIdx));
			}
			// if there is no tie, just add the top n candidates
			else {
				cand = this->republicans.at(i);
				if (this->republicans.at(i)->getNumVotes() == lastNum) {
					// delete the index i from sameIdx if the index i is in sameIdx
					sameIdx.erase(std::find(sameIdx.begin(), sameIdx.end(), i));
				}
			}
				this->pushList('W', cand);
				audit<<*cand<<" declared a winner!\n";
		}
	}
	// for democrats
	if(!democrats.empty()){
		// checking if there are candidates who got the same votes
		sameIdx = {};		// to save all the candidate's indices who got same number of votes
		chosenIdx = -1;		// to save the chosen candidate's index
		if(totalSeats[1]>0){
			lastNum = this->democrats.at(totalSeats[1]-1)->getNumVotes();
		}
		
		// get all the indices that are the same as the first index vote count, then save those in sameIdx
		for (int i=0; i<(int)this->democrats.size(); i++){
			if(this->democrats.at(i)->getNumVotes() == lastNum) {
				sameIdx.push_back(i);
			}
		}

		// based on each parties n allocated seats, add the first n candidates from each party list
		for (int i=0; i<totalSeats[1]; i++){
			Candidate* cand = new Candidate();
			// check if the candidate tie with others, if yes play coinToss to determine the winners
			if ((int)sameIdx.size() > 1 && (int)sameIdx.size() > totalSeats[1]-i && this->democrats.at(i)->getNumVotes() == lastNum) {
				chosenIdx = coinToss(sameIdx);
				cout << "Calling CoinToss. Democrats who win: " << this->democrats.at(chosenIdx)->getName() << ", seatLeft: " << totalSeats[1]-i << "\n";
				cand = this->democrats.at(chosenIdx);
				// delete the winner candidate's index from sameIdx
				sameIdx.erase(std::find(sameIdx.begin(), sameIdx.end(), chosenIdx));
			}
			// if there is no tie, just add the top n candidates
			else {
				cand = this->democrats.at(i);
				if (this->democrats.at(i)->getNumVotes() == lastNum) {
					// delete the index i from sameIdx if the index i is in sameIdx
					sameIdx.erase(std::find(sameIdx.begin(), sameIdx.end(), i));
				}
			}
				this->pushList('W', cand);
				audit<<*cand<<" declared a winner!\n";
		}
	}
	// for independent
	if(!independent.empty()){
		// checking if there are candidates who got the same votes
		sameIdx = {};		// to save all the candidate's indices who got same number of votes
		chosenIdx = -1;		// to save the chosen candidate's index
		if(totalSeats[2]>0){
			lastNum = this->independent.at(totalSeats[2]-1)->getNumVotes();
		}
		
		// get all the indices that are the same as the first index vote count, then save those in sameIdx
		for (int i=0; i<(int)this->independent.size(); i++){
			if(this->independent.at(i)->getNumVotes() == lastNum) {
				sameIdx.push_back(i);
			}
		}

		for (int i=0; i<totalSeats[2]; i++){
			Candidate* cand = new Candidate();
			// check if the candidate tie with others, if yes play coinToss to determine the winners
			if ((int)sameIdx.size() > 1 && (int)sameIdx.size() > totalSeats[2]-i && this->independent.at(i)->getNumVotes() == lastNum) {
				chosenIdx = coinToss(sameIdx);
				cout << "Calling CoinToss. Independent who win: " << this->independent.at(chosenIdx)->getName() << ", seatLeft: " << totalSeats[2]-i << "\n";
				cand = this->independent.at(chosenIdx);
				// delete the winner candidate's index from sameIdx
				sameIdx.erase(std::find(sameIdx.begin(), sameIdx.end(), chosenIdx));
			}
			// if there is no tie, just add the top n candidates
			else {
				cand = this->independent.at(i);
				if (this->independent.at(i)->getNumVotes() == lastNum) {
					// delete the index i from sameIdx if the index i is in sameIdx
					sameIdx.erase(std::find(sameIdx.begin(), sameIdx.end(), i));
				}
			}
				this->pushList('W', cand);
				audit<<*cand<<" declared a winner!\n";
		}
	}

	audit<<"OPL Vote Summary: \n"<<*this;
	audit.close();
}
}
