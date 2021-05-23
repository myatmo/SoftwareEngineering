/**
 * @file ballot.h
 */
#ifndef Ballot_H
#define Ballot_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>

using namespace std;
namespace votesys{
/*******************************************************************************
* Class Definitions
******************************************************************************/
/**
* @brief This is the ballot class for the vote counting system
*
* This class will provide methods for the IR election type
*/
class Ballot {
    private:
        vector<int> rankings;
        int nextRank;
		int ballID;
		bool invalidated;	// to check whether the ballot is invalid or not
    public:
    	/**
		* @brief Generation of a ballot object.
		*
		* This function will be used for ir voting system purposes.
		*
		* @return ballot object to be used in IR election vote counting
		*/
        Ballot();
        /**
		* @brief destruction of a ballot object.
		*
		* This function will be used for ir election purposes.
		*
		*/
        ~Ballot();
		/**
		* @brief overloaded outstream for ease of printing.
		*
		* This function will be used for printing a ballot.
		*
		* @param[in] the out stream for the ballot info to go into
		*
		* @param [in] ballot object to outstream
		*
		* @return returns to the outstream
		*/
		friend ostream& operator<<(ostream& os, const Ballot& ball);
		/**
		* @brief overloaded equivalence operator.
		*
		* This function will be used for checking a ballot equivalence to another.
		*
		* @param[in] lhs ballot
		*
		* @param [in] rhs ballot
		*
		* @return returns bool for equivalence
		*/			
		friend bool operator==(const Ballot& ball1, const Ballot& ball2);
		/**
		* @brief copy constructor override.
		*
		* This function will be used for copying a ballot.
		*
		* @param[in] the ballot to copy
		*
		* @return ballot object with attributes filled
		*/		
		Ballot& operator=(const Ballot &other);
		/**
		* @brief getter for the bballot id.
		*
		* This function will be used for IR election purposes.
		*
		* @return id as an int
		*/	 
		int getID();
		/**
		* @brief setter for the ballot id.
		*
		* This function will be used for IR election purposes.
		*
		* @param[in] int for id of the ballot
		*/	
		void setID(int id);
		/**
		* @brief setter for the vote string name.
		*
		* This function will be used for IR election purposes.
        * this will change the input to a int vector
		*
		* @param[in] string for ranked votes
		*/	        
        void setVote(string);
		/**
		* @brief setter for the vote current rank.
		*
		* This function will be used for IR election purposes.
		*
		* @param[in] int for current rank of ballot
		*/	       
        void setRank(int);
		/**
		* @brief getter for the vote rankings.
		*
		* This function will be used for IR election purposes.
		*
		* @return vote as an int vector
		*/	         
        vector<int> getVote();
		/**
		* @brief getter for the ballots current rank.
		*
		* This function will be used for IR election purposes.
		*
		* @return current rank as an int
		*/    
        int getRank();
		/**
		* @brief getter for the ballots invalidated.
		*
		* This function will be used for IR election purposes.
		*
		* @return invalidated as a bool
		*/
		bool isInvalidated();
		/**
		* @brief setter for the ballots invalidated.
		*
		* This function will be used for IR election purposes.
		*
		* @param[in] bool for invalidated ballot
		*/    
		void setInvalidated(bool);
		/**
		* @brief check whether there are 0.5 or more candidates are ranked in the ballot
		*
		* This function will be used for IR election purposes.
		*
		* @param[in] Ballot that is being processed
		*/
		void checkInvalidBallot();
};
}
#endif