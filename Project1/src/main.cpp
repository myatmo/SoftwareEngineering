#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "election.h"
#include "candidate.h"
#include "ir.h"
#include "opl.h"
#include "ballot.h"
#include <cstring>
#include <sstream>
#include <iomanip>
#include <chrono>
using namespace std::chrono;
using namespace std;
using namespace votesys;
/*
	loadFile()
	parameters: string votingType - used for the main if block of the function
				OPL* opl - used if votingType is OPL and filled with needed info to count the vote
				IR* ir - used if votingType is IR and filled with needed info to count the vote
	purpose: This function is used to parse the input csv file for an election
	preconditions: must be a csv file deliminated by commas and each line ended by a newline
*/
void loadFile(string votingType, OPL* opl, IR* ir, string fn) {
	// loca variables
	string firstLine, fileName;	
	string numCandidates, numBallots, numSeats;
	int numBall;
	bool error;
	// ask user to input the file
	// open the file and confirm type
	std::ifstream file;
	printf("Loading file...\n");
	printf("Please enter the correct file name:\n");
	cin>>fileName;
	string path = "../testing/";
	path.append(fileName);
	file.open(path.c_str(), std::ifstream::in);
	getline(file, firstLine);
	std::size_t found = firstLine.find(votingType);
	// check if the file exists and the firstLine of file is same as votingType
	if (found!=std::string::npos) {
		error = false;
	}
	else {
		error = true;
	}
	// if not loop until the user enters the correct file name
	while (error) {
		file.close();
		printf("Incorrect file name!\n");
		printf("Please enter the correct file name:\n");
		cin>>fileName;
		path = "../testing/";
		path.append(fileName);
		file.open(path.c_str(), std::ifstream::in);
		getline(file, firstLine);
		found = firstLine.find(votingType);
		if (found!=std::string::npos) {
			error = false;
		}
	}
	
	// first line is always number of candidate, read in and convert to an int
	getline(file, numCandidates,'\n');
	int numCand;
	stringstream num(numCandidates);
	num>>numCand;
	// this is for IR voting type
	if(votingType == "IR"){
		string filename = "./Audits/IR"+fn;
		ofstream audit;
		audit.open(filename, std::ios_base::app);
		audit<<"IR Election Run Audit\n";
		audit<<"IR voting info colleciton\n";
		audit<<"Starting read from file\n";
		ir->setNumCandidates(numCand);
		audit<<"Number of candidates set to: "<<to_string(numCand)<<endl;
		// assume candiate line is as follows for delimination
		// Rosen (D), Kleinberg (R), Chou (I), Royce (L)
		// loop for numCand-1 and after loop read last candidate because of defferent delim
		for (int i=0; i<numCand-1; i++){
			string candidate;
			getline(file, candidate,' ');
			Candidate* cand = new Candidate();
			cand->setName(candidate);
			cand->setNumVotes(0);
			string party;
			getline(file, party, ' ');
			if(party.find("D") != std::string::npos){
				cand->setParty('D');
			}
			else if (party.find("R") != std::string::npos){
				cand->setParty('R');
			}
			else{
				cand->setParty('I');
			}
			ir->pushCandidateList(cand);
			audit<<"Added "<<*cand<<", "<<" to list\n";
		}
		// add last candidate here because of diff delim
		string candidate;
		getline(file, candidate,' ');
		Candidate* cand = new Candidate();
		cand->setName(candidate);
		cand->setNumVotes(0);
		string party;
		getline(file, party, '\n');
		if(party.find("D") != std::string::npos){
			cand->setParty('D');
		}
		else if (party.find("R") != std::string::npos){
			cand->setParty('R');
		}
		else{
			cand->setParty('I');
		}
		ir->pushCandidateList(cand);
		audit<<"Added "<<*cand<<", "<<" to list\n";
		// read in number of ballots and convert to an int
		getline(file, numBallots, '\n');
		stringstream bal(numBallots);
		bal>>numBall;
		ir->setNumBallots(numBall);
		audit<<"Set number of ballots to "<<numBallots<<endl;
		// now process ballots
		// look for position of 1 and give ballot to candidate in that same position
		for(int i=0; i<numBall; i++){
			int firstChoice=0;
			string vote;
			getline(file, vote, '\n');
			for(int j=0; j<(int)vote.size();j++){
				if(vote.at(j) == '1'){	// if 1 then firstchoice has been found
					break;
				}
				else if(isdigit(vote.at(j))){	// if digit other than 1, increment first choice position
					firstChoice++;
				}
				else if(j>0 && vote.at(j) == ',' && vote.at(j-1) == ','){	// if comma followed by comma, increment frist choice
					firstChoice++;
				}
				else if(j==0 && vote.at(j) == ','){		// if starting with comma, increment first choice
					firstChoice++;
				}
				else{	// else no reason to increment
					continue;
				}
			}
			// set up new ballot and give to first choice candidate
			// increment number of votes
			Ballot* ballot = new Ballot();
			ballot->setVote(vote);
			ballot->setRank(1);
			ballot->setID(i);
			ir->getCandidateList()[firstChoice]->pushBallotList(ballot);
			int cur = ir->getCandidateList()[firstChoice]->getNumVotes();
			ir->getCandidateList()[firstChoice]->setNumVotes(cur+1);
			audit<<"Process ballot "<<to_string(i)<<": "<<vote<<" given to "<<*ir->getCandidateList()[firstChoice]<<endl;
		}
		audit.close();
	}
	// this is for OPL voting type
	else if(votingType == "OPL"){
		string filename = "./Audits/OPL"+fn;
		ofstream audit;
		audit.open(filename, std::ios_base::app);
		audit<<"OPL Election Run Audit\n";
		audit<<"OPL voting info collection\n";
		audit<<"Starting read from file\n";
		// set number of candidates
		opl->setNumCandidates(numCand);
		audit<<"Number of candidates set to: "<<to_string(numCand)<<endl;
		// iterate through candidates, format of line is assumed to be as follows
		// [Pike,D], [Foster,D],[Deutsch,R], [Borg,R], [Jones,R],[Smith,I]
		// only iter until second to last canddiate and finish outside of loop becasue of diff delim
		for (int i=0; i<numCand-1; i++){
			string noneed;
			string candidate;
			getline(file, noneed,'[');
			getline(file, candidate,',');
			Candidate* cand = new Candidate();
			cand->setName(candidate);
			cand->setNumVotes(0);
			string party;
			getline(file, party, ']');
			if(party.find("D") != std::string::npos){
				cand->setParty('D');
			}
			else if (party.find("R") != std::string::npos){
				cand->setParty('R');
			}
			else{
				cand->setParty('I');
			}
			opl->pushCandidateList(cand);
			audit<<"Added "<<*cand<<", "<<" to list\n";
		}
		// add last here because of diff delim
		string noneed;
		string candidate;
		getline(file, noneed, '[');
		getline(file, candidate,',');
		Candidate* cand = new Candidate();
		cand->setName(candidate);
		cand->setNumVotes(0);
		string party;
		getline(file, party, '\n');
		if(party.find("D") != std::string::npos){
			cand->setParty('D');
		}
		else if (party.find("R") != std::string::npos){
			cand->setParty('R');
		}
		else{
			cand->setParty('I');
		}
		opl->pushCandidateList(cand);	
		audit<<"Added "<<*cand<<", "<<" to list\n";	
		// get number of seats after candidates finish processing
		// convert to an int
		getline(file, numSeats,'\n');
		int nums;
		stringstream ns(numSeats);
		ns>>nums;
		opl->setNumSeats(nums);
		audit<<"Set number of seats to "<<numSeats<<endl;
		// read in number of ballots and conver to an int
		getline(file, numBallots, '\n');
		stringstream bal(numBallots);
		bal>>numBall;
		opl->setNumBallots(numBall);
		audit<<"Set number of ballots to "<<numBallots<<endl;
		// now process the ballots
		// find the occurence of 1 and +1 numvotes for that candidate in that position
		for(int i=0; i<numBall; i++){
			string vote;
			getline(file, vote, '\n');
			int rank = vote.find("1");
			opl->getCandidateList()[rank]->setNumVotes(opl->getCandidateList()[rank]->getNumVotes()+1);
			audit<<"Process ballot "<<to_string(i)<<": "<<vote<<"\ngiven to "<<*opl->getCandidateList()[rank]<<endl;
		}
		// add all candidate to their own party lists in opl
		// this is done last because all votes have been processed and given to their respective candidates
		for(int i=0; i< numCand;i++){
			if(opl->getCandidateList()[i]->getParty() == 'R'){
				opl->pushList('R',opl->getCandidateList()[i]);
			}
			else if(opl->getCandidateList()[i]->getParty() == 'D'){
				opl->pushList('D',opl->getCandidateList()[i]);
			}
			else{
				opl->pushList('I',opl->getCandidateList()[i]);
			}
		}
		audit.close();
	}
	// close the open file
	file.close();
}

void displayResult(string votingType, OPL* opl, IR* ir) {
	// Print results of OPL election
	if(votingType == "OPL"){
		cout<<"Election type: OPL\n";
		cout<<"Seats: "<<opl->getNumSeats()<<endl;
		cout<<"Number of Candidates: "<<opl->getNumCandidates()<<endl;
		cout<<"Number of Ballots: "<<opl->getNumBallots()<<endl;
		cout<<"Winners: \n";
		vector<Candidate*> winners = opl->getList('W');
		for(int i=0; i<(int)winners.size(); i++){
			cout<<winners.at(i)->getName()<<" with "<<winners.at(i)->getNumVotes()<<endl;
		}
		vector<Candidate*> all = opl->getCandidateList();
		// Display name and # of votes for each candidate
		cout<<"All Candidates: \n";
		for(int i=0; i<(int)all.size(); i++){
			cout<<all.at(i)->getName()<<" with "<<all.at(i)->getNumVotes()<<endl;
		}
	}
	// Print results of IR election
	if(votingType == "IR"){
		cout<<"Election type: IR\n";
		cout<<"Winner: \n";
		cout<<ir->getWinner()->getName()<<endl;
		vector<Candidate*> all = ir->getCandidateList();
		// Display name and # of votes for each candidate
		cout<<"All Candidates: \n";
		for(int i=0; i<(int)all.size(); i++){
			cout<<all.at(i)->getName()<<" with "<<all.at(i)->getNumVotes()<<endl;
		}
	}	

	/*
	Purpose:    Display the final result of the voting based on the type of voting
	Input:      votingType (the type of voting that the user chose)
	Ouput:      None
	*/
	//printf("Display Final Result of Voting System\n");

	// display election result based on the type of voting
	// result storage for the media file

	// Open media file
	ofstream MyFile("DisplayResult.txt");

	// if votingType is 'IR', 2 cases to show the result
	if (votingType == "IR") {
	
		// Run IR election repeatedly until a winner is chosen
		/* Case 1: One candidate receives over 50% of the 1st-choice vote.
		   Then, the system will display the result of the election-> */
		if (ir->getTransferVotes().size() == 1) {
			// Write and format IR voting data to the media file
			MyFile << "Candidates & Parties  || First Choice Votes " << endl;
			for (int i = 0; i < (int)ir->getCandidateList().size(); i++) {
				ir->getCandidateList()[i]->getParty();
				MyFile << setw(18)<<ir->getCandidateList()[i]->getName() << " (" << ir->getCandidateList()[i]->getParty() << ")"<< "||" 
					   << setw(20)<<ir->getCandidateList()[i]->getNumVotes() << endl;
			}

			bool tie;
			// if the winner gets majority vote then tie is false; otherwise they tie
			if (ir->getWinner()->getNumVotes() > int(0.5 * ir->getNumBallots())) { tie = false; }
			else { tie = true; }
			int idx; // to save the candidate who is tie with the winner
			int trsize = ir->getTransferVotes().size() - 1;
			if (tie == true) { 
				for (int i = 0; i < (int)ir->getTransferVotes()[trsize].size(); i++) {
					// in the case when 2 candidates tie, the rest of the candidates have vote count zero
					// so we only need to get the candidate that has non-zero entry; of course need to exclude the winner
					if (ir->getTransferVotes()[trsize][i] != 0 && ir->getWinner()->getName() != ir->getCandidateList()[i]->getName()) {
						idx = i;    // save the index of that candidate to idx
					}
				}
				// Print tie message
				MyFile << ir->getWinner()->getName() << " and " << ir->getCandidateList()[idx]->getName() << "tie." << endl;
			}
			else {
				MyFile << "Winner: " << ir->getWinner()->getName() << " (" << ir->getWinner()->getParty() << ")." << endl;
			}



		}
		/* Case 2: If no candidate receives a majority, the candidate with the fewest
		   votes is eliminated, and the system will begin the transfer voting process. */
		else {
			    // Write and format IR voting data to the media file
				MyFile << "  Candidates (Parties)  ||";
				
				for(int i=0; i<(int)ir->getTransferVotes().size();i++){
					MyFile<<"  After "<<setw(3)<<i<<" Tranfser  ||";
				}
				MyFile<<"  Final Votes  "<<endl;

				vector<Candidate*> electlist = ir->getCandidateList();
				//ir->transferVote("test.txt");
				//candidate.popBallotList();

				//ir->transferVote("test.txt");
				//candidate.popBallotList();

				for (int i = 0; i < (int)ir->getCandidateList().size(); i++) {
					// First Count
					MyFile << setw(20)<<ir->getCandidateList()[i]->getName() << " (" << ir->getCandidateList()[i]->getParty() << ")"<<"||";
					MyFile<< setw(22)<<ir->getTransferVotes()[0][i] << "||";
					for(int j=1; j<(int)ir->getTransferVotes().size();j++){
						MyFile<<setw(18)<<"+"<<setw(4)<<ir->getTransferVotes()[j][i]-ir->getTransferVotes()[j-1][i] <<"||";
					}
					MyFile<<setw(15)<<ir->getCandidateList()[i]->getNumVotes()<<endl;
				}

				// Display winner
				MyFile << "Winner: " << ir->getWinner()->getName() << " (" << ir->getWinner()->getParty() << ")\n";
		}
	}

	// Show 'OPL' result
	else if (votingType == "OPL") {

		int totalVotes = opl->getRepVotes() + opl->getDemVotes() + opl->getIndVotes();
		vector<int> votelist{opl->getRepVotes(),opl->getDemVotes(),opl->getIndVotes()};

		// Write and format OPL voting data to the media file
		MyFile << setw(22) << ""<<"||  First Allocation || Remaining || Second Allocation || Final Seat || % of Vote to" << endl;
		MyFile << setw(13)<<"Parties"<<"|| Votes ||     of Seats      ||   Votes   ||      of Seats     ||    Total   ||  % of Seats" << endl;

		MyFile << setw(13)<<"Republicans"<<"||"<<setw(7)<<opl->getRepVotes() << "||" << setw(19)<<opl->getFirstSeats()[0] << "||"
			   << setw(11)<<opl->getRemainingVotes()[0] << "||" << setw(19)<<opl->getSecondSeats()[0] <<"||"
			   << setw(12)<<opl->getFirstSeats()[0] + opl->getSecondSeats()[0] << "||"
			   << setw(7)<<100*opl->getRepVotes() / totalVotes << "% / " <<100*opl->getSecondSeats()[0] / opl->getNumSeats() << "%" << endl;

		MyFile << setw(13)<<"Democrats"<<"||"<<setw(7) << opl->getDemVotes() << "||" << setw(19)<<opl->getFirstSeats()[1] << "||"
			   << setw(11)<<opl->getRemainingVotes()[1] << "||" << setw(19)<<opl->getSecondSeats()[1] <<  "||"
			   << setw(12)<<opl->getFirstSeats()[1] + opl->getSecondSeats()[1] << "||"
			   << setw(7)<<100*opl->getDemVotes() / totalVotes << "% / " << 100*opl->getSecondSeats()[1] / opl->getNumSeats() << "%" << endl;

		MyFile << setw(13)<<"Independents"<<"||" << setw(7)<<opl->getIndVotes() << "||" << setw(19)<<opl->getFirstSeats()[2] <<"||"
			   << setw(11)<<opl->getRemainingVotes()[2] << "||" << setw(19)<<opl->getSecondSeats()[2] << "||"
			   << setw(12)<<opl->getFirstSeats()[2] + opl->getSecondSeats()[2] << "||"
			   << setw(7)<<100*opl->getIndVotes() / totalVotes << "% / " << 100*opl->getSecondSeats()[2] / opl->getNumSeats() << "%" << endl;
		for (int i = 0; i<(int)opl->getList('W').size(); i++) {
			MyFile << "The " << opl->getList('W')[i]->getParty() << " winner is " << opl->getList('W')[i]->getName() << endl;
		}
	}

	// save a media txt file
	MyFile.close();

	printf("The election results have been saved to DisplayResult.txt\n");
}

void initializeVotingSystem(string fn) {
	/*
	Purpose:	Ask the user to choose between IR or OPL voting system,
				load the correct CSV file, read the file and process counting votes
	Input:		None
	Return:		None
	*/
	printf("Initialize Voting System\n");

	int user_choice;
	bool error = true;
	while (error) {
		// prompt user to enter 1 for 'IR' voting or 2 for 'OPL' voting
		printf("Please choose 1 to select Instant Runoff voting system (IR)\n");
		printf("Please choose 2 to select Open Party Listing voting system (OPL)\n");
		printf("Enter your choice here: ");
		string input;
		cin >> input;
		stringstream toint(input);
		toint >> user_choice;

		printf("You entered %d.\n", user_choice);
		// check if user input is either 1 or 2
		if (user_choice == 1 || user_choice == 2) {
			error = false;
		}
		// error message if the input is not either 1 or 2, otherwise continue
		else {
			printf("Invalid input.\n");
		}
	}

	// create Election object
	string votingType;
	// set Election::setvotingType to the user choice (if user input is 1, set it to 'IR', else 'OPL')
	if (user_choice == 1) {
		votingType = "IR";
	}
	if(user_choice == 2) { 
		votingType = "OPL"; 
	}

	// set Election::setvotingType to the user choice (if user input is 1, set it to 'IR', else 'OPL')
	IR* ir = new IR();
	OPL* opl = new OPL();

	loadFile(votingType,opl,ir,fn);

	
	// start vote counting process:
	if (votingType == "IR"){
		//      call IR::countVote(Election::candidateList)
		string filename = "./Audits/IR"+fn;
		ir->countVote(filename);
	}
	else if (votingType == "OPL") {
		//		call OPL::countVote(Election::candidateList, Election::numBallots)
		string filename = "./Audits/OPL"+fn;
		opl->countVote(opl->getNumBallots(),filename);
	}
	displayResult(votingType,opl, ir);

	delete opl;
	delete ir;
}
/*
	Timing a function methodology found and cited: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
*/
int main(int argc, char *argv[]) {
	auto begin = high_resolution_clock::now();
	time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%d-%m-%Y-%H-%M-%S",timeinfo);
	string fn = "AuditFile-"+string(buffer);
	srand(time(NULL));	// to get true random number each time
	printf("Welcome to Voting System Application\n");
	initializeVotingSystem(fn);
	auto end = high_resolution_clock::now();
	auto totalTime = duration_cast<seconds>(end - begin);
	cout << "Counting ballots took "<<totalTime.count() << " seconds to complete\n"<<endl;
	return 1;
}
