/*! \mainpage IRL and OPL Election Mainpage
 *
 * \tableofcontents
 *
 * \section intro_sec Introduction
 *
 * This project as a whole focuses on developing a working voting system
 * for two different election types, including thorough written documentation as well as
 * functioning code to bring our solutions to life.
 *
 * In IR election, candidates are ranked with data of the ballots imported as a CSV file.
 * In OPL election, single candidates are voted for with data of the ballots imported as a CSV file.
 *
 * \section overview_sec Overview
 *
 * \subsection IR_subsec IR Election
 *
 * The basic technical flow of the simulation as implemented in IR Election was as follows:
 * - An election was started from running the main file\n
 * - A CSV file was loaded into the program and the election type is determined from the first line of the CSV file\n
 * - Candidates are extracted and dynamically created as an object\n
 * - Ballot data is then extracted from the CSV file and brought into the election.\n
 * - In IR, each candidate is ranked. Depending on rank, a winner is determined by the highest rank.\n
 *
 * This implementation was actually already flexible enough to
 *  handle any ties that may occur by removing the lowest ranked candidate and recalculating a winner 
 *  where votes from ballot data are then redistributed amongs the remaining candidates.\n
 *  A winner is then presented as output from the program, and the election is deleted.
 *
 * \subsection OPL_subsec OPL Election
 *
 * The basic technical flow of the simulation as implemented in OPL Election was as follows:
 * - An election was started from running the main file\n
 * - A CSV file was loaded into the program and the election type is determined from the first line of the CSV file\n
 * - Candidates are extracted and dynamically created as an object\n
 * - Ballot data is then extracted from the CSV file and brought into the election.\n
 * - In OPL, each candidate has a vote count and each ballot holds exactly one vote for a single candidate.
 * - The winner is determined by the candidate with the highest vote count once all ballots have been counted.\n
 *
 * This implementation was actually already flexible enough to
 *  handle any ties that may occur by calculating a winner based on a random coin toss.\n
 *  A winner is then presented as output from the program, and the election is deleted.
 *
 * \section getting_started_sec Getting Started
 *
 * To test it out for yourself...\n
 * First, ensure that you are in the `/project` directory.\n
 * Once there, build and run:
 *
 *      make
 *      ./votecount
 * The system will ask for input on which type of election and then the file name. Ensure that the file is in the Project1/testing folder\n
 * A detailed audit will be created for each election and placed in Project1/src/Audits folder with the current date and time stamp\n
 * A summary of the results will be written over the DisplayResults.txt which can be shared with the media if saved elsewhere before running an additional election\n
 * The timing constraint will be printed to the terminal as well as additional summary of the election.\n
 * 
 * \subsection test_sub Testing the Classes
 * 
 * You can test the class methods by navigating to Project1/src/UnitTests\n
 * Once there, build a run:
 * 
 *      make
 *      ./test
 * You can save a record of these tests by inputing ./test >> ../../testing/testinglogs.txt\n
 * DO NOT USE > AS THIS WILL OVERWRTIE EXISTING TEST RECORDS!
 */
