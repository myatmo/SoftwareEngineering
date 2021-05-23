/**
 * @file opl.h
 */
#ifndef OPL_H
#define OPL_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "candidate.h"
#include "election.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <chrono>
#include <ctime> 
#include  <stdio.h>
#include <iterator>
#include <unistd.h>
#include <fstream>

namespace votesys{
/*******************************************************************************
* Class Definitions
******************************************************************************/
/**
* @brief This is the OPL class for the vote counting system
*
* This class will provide methods for the OPL election type
*/
class OPL: public Election {
	private:
		int numSeats;
		int quota;
		int repVotes;
		int demVotes;
		int indVotes;
		vector<int> firstSeats; // to save the seats from first allocation
		vector<int> remainingVotes; // to save the remaining votes after first seat allocation
		vector<int> secondSeats; // to save the seats from second allocation
		vector<Candidate*> republicans;
		vector<Candidate*> democrats;
		vector<Candidate*> independent;
		vector<Candidate*> winners;
	public:
		/**
		* @brief Generation of an OPL object.
		*
		* This function will be used for opl election purposes.
		*
		* @return OPL object to be used in election vote counting
		*/
		OPL();
		/**
		* @brief destruction of an OPL object.
		*
		* This function will be used for opl election purposes.
		*
		*/
		~OPL();
		/**
		* @brief overloaded outstream for ease of printing.
		*
		* This function will be used for printing a opl election info.
		*
		* @param[in] the out stream for the opl info to go into
		*
		* @param [in] opl object to outstream
		*
		* @return returns to the outstream
		*/
		friend ostream& operator<<(ostream& os, const OPL& opl);
		/**
		* @brief setter for the number of seats in an election.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] int representing the number of seats in opl election
		*/		
		void setNumSeats(int numSeats);
		/**
		* @brief getter for the number of seats in an election.
		*
		* This function will be used for opl election purposes.
		*
		* @return int representing the number of seats in opl election
		*/			
		int getNumSeats();
		/**
		* @brief setter for the number of republican votes in an election.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] int representing the number of republican votes in opl election
		*/	
		void setRepVotes(int repVotes);
		/**
		* @brief getter for the number of republican votes in an election.
		*
		* This function will be used for opl election purposes.
		*
		* @return int representing the number of republican votes in opl election
		*/	
		int getRepVotes();
		/**
		* @brief setter for the number of democrat votes in an election.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] int representing the number of democrat votes in opl election
		*/	
		void setDemVotes(int demVotes);
		/**
		* @brief getter for the number of democrat votes in an election.
		*
		* This function will be used for opl election purposes.
		*
		* @return int representing the number of democrat votes in opl election
		*/	
		int getDemVotes();
		/**
		* @brief setter for the number of independent votes in an election.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] int representing the number of independent votes in opl election
		*/	
		void setIndVotes(int indVotes);
		/**
		* @brief getter for the number of independent votes in an election.
		*
		* This function will be used for opl election purposes.
		*
		* @return int representing the number of independent votes in opl election
		*/	
		int getIndVotes();
		/**
		* @brief setter for the vector of first allocation party seats in an opl election.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] vector of first allocation party seats in an opl election
		*/	
		void setFirstSeats(vector<int> firstSeats);
		/**
		* @brief getter for the vector of first allocation party seats in an opl election.
		*
		* This function will be used for opl election purposes.
		*
		* @return vector of first allocation party seats in an opl election
		*/	
		vector<int> getFirstSeats();
		/**
		* @brief setter for the vector of remaining party votes in an opl election.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] vector of remaining party votes in an opl election
		*/	
		void setRemainingVotes(vector<int> remainingVotes);
		/**
		* @brief getter for the vector of remaining party votes in an opl election.
		*
		* This function will be used for opl election purposes.
		*
		* @return vector of remaining party votes in an opl election
		*/		
		vector<int> getRemainingVotes();
		/**
		* @brief setter for the vector of second allocation party seats in an opl election.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] vector of seond allocation party seats in an opl election
		*/	
		void setSecondSeats(vector<int> secondSeats);
		/**
		* @brief getter for the vector of second allocation party seats in an opl election.
		*
		* This function will be used for opl election purposes.
		*
		* @return vector of second allocation party seats in an opl election
		*/	
		vector<int> getSecondSeats();
		/**
		* @brief getter for the vector of candidates by party in an opl election.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] char representing the party list to return
		*
		* @return vector of candidates based on char input
		*
		*/	
		vector<Candidate*> getList(char party);
		/**
		* @brief adds candidate to a candidate vector by party in an opl election.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] char representing the party list to add candidate to
		*
		*/			
		void pushList(char party, Candidate* candidate);
		/**
		* @brief calculates and sets quota attribute.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] int representing the number of votes in an election
		* @param[in] int representing the number of seats in an election
		*
		*/	
		void calculateQuota(int numVotes, int numSeats, string fn);
		/**
		* @brief calculates and sets quota attribute.
		*
		* This function will be used for opl election purposes.
		*
		* @return int representing the quota in an opl election
		*/			
		int getQuota();
		/**
		* @brief calculates and sets seat allocations in an opl election.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] int vector representing the number of votes for each party in an election
		* @param[in] int representing the number quota in an opl election
		*
		* @return vector of seat totals for each party
		*/	
		vector<int> calculateSeatAllocation(vector<int> numVoteList, int quota, string fn);
		/**
		* @brief builds a winner list based on seat allocations and party member votes.
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] int representing the number of votes in an election
		*
		*/	
		void countVote(int numBallots, string fn);
};
}
#endif