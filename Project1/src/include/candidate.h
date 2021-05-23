/**
 * @file candidate.h
 */
#ifndef Candidate_H
#define Candidate_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>
#include "ballot.h"
#include <unistd.h>

using namespace std;
namespace votesys{
/*******************************************************************************
* Class Definitions
******************************************************************************/
/**
* @brief This is the Candidate class for the vote counting system
*
* This class will provide methods for both election types
*/
class Candidate {
    private:
        string candidateName;
        char party;
        int numVotes;
        vector<Ballot*> ballotList;
        bool eliminated = false;   // initially this will be false
    public:
		/**
		* @brief Generation of a Candidate object.
		*
		* This function will be used for voting system purposes.
		*
		* @return Candidate object to be used in election vote counting
		*/
        Candidate();
        /**
		* @brief destruction of a candidate object.
		*
		* This function will be used for election purposes.
		*
		*/
        ~Candidate();
		/**
		* @brief copy constructor override.
		*
		* This function will be used for copying a candidate.
		*
		* @param[in] the candidate to copy
		*
		* @return candidate object with attributes filled
		*/
		Candidate& operator=(const Candidate &candidate);
		/**
		* @brief overloaded outstream for ease of printing.
		*
		* This function will be used for printing a candidate.
		*
		* @param[in] the out stream for the candidate info to go into
		*
		* @param [in] candidate object to outstream
		*
		* @return returns to the outstream
		*/
		friend ostream& operator<<(ostream& os, const Candidate& cand);
		/**
		* @brief overloaded equivalence operator.
		*
		* This function will be used for checking a candidates equivalence to another.
		*
		* @param[in] lhs candidate
		*
		* @param [in] rhs candidate
		*
		* @return returns bool for equivalence
		*/		
		friend bool operator==(const Candidate& cand1, const Candidate& cand2);
		/**
		* @brief setter for the candidate name.
		*
		* This function will be used for election purposes.
		*
		* @param[in] name of candidate as a string
		*/		
        void setName(string);
		/**
		* @brief setter for the candidate party.
		*
		* This function will be used for election purposes.
		*
		* @param[in] first char in candidates party
		*/	
        void setParty(char);
    	/**
		* @brief setter for the candidates vote count.
		*
		* This function will be used for election purposes.
		*
		* @param[in] number of votes as an int
		*/	
        void setNumVotes(int);
		/**
		* @brief setter for the bool value eliminated for candidate.
		*
		* This function will be used for election purposes.
		*
		* @param[in] bool true if eliminated else false 
		*/	
        void setCandidateEliminated(bool);
		/**
		* @brief getter for the name of the candidate.
		*
		* This function will be used for election purposes.
		*
		* @return candidates name as a string
		*/	        
        string getName();
		/**
		* @brief getter for the party of the candidate.
		*
		* This function will be used for election purposes.
		*
		* @return candidates party represented by the first char in the party
		*/	  
        char getParty();
		/**
		* @brief getter for the number of votes the candidate has.
		*
		* This function will be used for election purposes.
		*
		* @return candidates number of votes as an int
		*/	  
        int getNumVotes();
  		/**
		* @brief getter for the bool of candidates elimination status .
		*
		* This function will be used for election purposes.
		*
		* @return bool true if eliminated else false 
		*/	       
        bool isEliminated();
  		/**
		* @brief getter for the the candidates ballots list.
		*
		* This function will be used for election purposes.
		*
		* @return list of ballots assigned to the candidate 
		*/	          
        vector<Ballot*> getBallotList();
  		/**
		* @brief adds a ballot to the candidates ballot list.
		*
		* This function will be used for election purposes.
		*
		* @param[in] ballot to be assigned to the candidate 
		*/	  
        void pushBallotList(Ballot*);
  		/**
		* @brief removes a ballot from the candidates ballot list.
		*
		* This function will be used for election purposes.
		*
		* @return ballot to be assigned to different candidate 
		*/
        Ballot* popBallotList(int i);
};
}
#endif