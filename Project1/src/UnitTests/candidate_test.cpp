#include "../include/candidate.h"

#include "gtest/gtest.h"

namespace votesys{

// The fixture for testing class Foo.
class CandidateTest : public ::testing::Test {
};

TEST_F(CandidateTest, nameSetterGetter1) {
    Candidate cand1 = Candidate();
    cand1.setName("Eric Cartman");
    string actual = cand1.getName();
    EXPECT_EQ(actual, "Eric Cartman");
}

TEST_F(CandidateTest, partySetterGetter1){
    Candidate cand1 = Candidate();
    cand1.setParty('R');
    char actual = cand1.getParty();
    EXPECT_EQ(actual, 'R');
}

TEST_F(CandidateTest, votesSetterGetter1){
    Candidate cand1 = Candidate();
    cand1.setNumVotes(1);
    int actual = cand1.getNumVotes();
    EXPECT_EQ(actual, 1);
}
TEST_F(CandidateTest, eliminatedSetterGetter1){
    Candidate cand1 = Candidate();
    cand1.setCandidateEliminated(true);
    bool actual = cand1.isEliminated();
    EXPECT_EQ(actual, true);
}
TEST_F(CandidateTest, ballotListSetterGetter1){
    Candidate cand1 = Candidate();
    Ballot* ballot = new Ballot();
    ballot->setID(1);
    cand1.pushBallotList(ballot);
    vector<Ballot*> ballotlist = cand1.getBallotList();
    Ballot* actualballot = cand1.popBallotList(0);

    EXPECT_EQ(actualballot, ballot);
    EXPECT_EQ(ballotlist[0], ballot);
}

}
