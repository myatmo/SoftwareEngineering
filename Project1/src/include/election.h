/**
 * @file election.h
 */

#ifndef Election_H
#define Election_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <string>
#include "candidate.h"
#include <unistd.h>
namespace votesys{
/*******************************************************************************
* Class Definitions
******************************************************************************/
/**
* @brief This is the election class for the vote counting system
*
* This class will provide methods and attributes for both election types
*/
class Election {
    private:
        string votingType;
	protected:
		int numBallots;
		int numCandidates;
		vector<Candidate*> candidateList;

    public:
		/**
		* @brief Generation of an election object.
		*
		* This function will be used for election purposes.
		*
		* @return election object to be used in election vote counting
		*/
		Election();
		/**
		* @brief destruction of an election object.
		*
		* This function will be used for opl election purposes.
		*
		*/
		~Election();
		/**
		* @brief setter for the number of seats in an election.
		*
		* This function will be used for election purposes.
		*
		* @param[in] string representing the voting type
		*/	
		void setvotingType(string);
		/**
		* @brief setter for the number of ballots in an election.
		*
		* This function will be used for election purposes.
		*
		* @param[in] int representing the number of ballots in an election
		*/	
		void setNumBallots(int);
		/**
		* @brief setter for the number of candidates in an election.
		*
		* This function will be used for election purposes.
		*
		* @param[in] int representing the number of candidates in an election
		*/	
		void setNumCandidates(int);
		/**
		* @brief getter for the voting type of an election.
		*
		* This function will be used for election purposes.
		*
		* @return string representing the voting type
		*/	
		string getVotingType();
		/**
		* @brief getter for the number of ballots in an election.
		*
		* This function will be used for election purposes.
		*
		* @return int representing the number of ballots in an election
		*/	
		int getNumBallots();
		/**
		* @brief getter for the number of candidates in an election.
		*
		* This function will be used for election purposes.
		*
		* @return int representing the number of candidates in an election
		*/	
		int getNumCandidates();
		/**
		* @brief getter for the list of candidates in an election.
		*
		* This function will be used for election purposes.
		*
		* @return list of candidates in an election
		*/	
		vector<Candidate*> getCandidateList();
		/**
		* @brief adds candidate to candidate list in an election.
		*
		* This function will be used for election purposes.
		*
		* @param[in] Candidate to be added to list
		*
		*/			
		void pushCandidateList(Candidate*);
		/**
		* @brief method to settle a tie between 2 or more candidates.
		*
		* This function will be used for election purposes.
		*
		* @param[in] list of ints representing candidates
		* 
		* @return int representing the candidate from the input that won the coin toss
		*
		*/	
		int coinToss(vector<int>);
};
}
#endif