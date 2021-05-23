/**
 * @file ir.h
 */
#ifndef IR_H
#define IR_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>
#include "candidate.h"
#include "election.h"
#include "candidate.h"
#include "election.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <chrono>
#include <ctime> 
#include <stdio.h>
#include <iterator>
#include <unistd.h>
#include <fstream>
namespace votesys{
/*******************************************************************************
* Class Definitions
******************************************************************************/
/**
* @brief This is the IR class for the vote counting system
*
* This class will provide methods for the IR election types
*/
class IR: public Election {
	private:
		Candidate* winner;
		Candidate* loser;
		vector<vector<int>> transferVotes;
	public:
		/**
		* @brief Generation of an IR object.
		*
		* This function will be used for IR election purposes.
		*
		* @return IR object to be used in election vote counting
		*/
		IR();
		/**
		* @brief destruction of an IR object.
		*
		* This function will be used for IR election purposes.
		*
		*/
		~IR();
		/**
		* @brief setter for the winner in an IR election.
		*
		* This function will be used for IR election purposes.
		*
		* @param[in] candidate that won an IR election
		*/				
		void setWinner(Candidate*);
		/**
		* @brief setter for the loser in an IR election.
		*
		* This function will be used for IR election purposes.
		*
		* @param[in] candidate that lost an IR election
		*/		
		void setLoser(Candidate*);
		/**
		* @brief getter for the winner of an IR election.
		*
		* This function will be used for IR election purposes.
		*
		* @return candidate that won an ir election
		*/	
		Candidate* getWinner();
		/**
		* @brief getter for the loser of an IR election.
		*
		* This function will be used for IR election purposes.
		*
		* @return candidate that lost an ir election
		*/		
		Candidate* getLoser();
		/**
		* @brief getter for the list of votes to be transfered in IR election.
		*
		* This function will be used for IR election purposes.
		*
		* @return list of vote transfer lists
		*/		
		vector<vector<int>> getTransferVotes();
		/**
		* @brief counts the ballots of each candidate in the candidate list
		*
		* This function will be used for IR election purposes.
		*
		* @param[in] list of candidates in an election
		*
		* @return winning candidate
		*
		*/		
		Candidate* countVote(string fn);
		/**
		* @brief transfers votes from candidate to candidates in the list
		*
		* This function will be used for opl election purposes.
		*
		* @param[in] candidate that lost in current round
		*
		* @param[in] list of candidates to redistribute votes to
		*/
		void transferVote(string fn);
};
}
#endif