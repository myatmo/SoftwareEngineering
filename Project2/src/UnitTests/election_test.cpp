#include "../include/election.h"

#include "gtest/gtest.h"

namespace votesys{

// The fixture for testing class Foo.
class ElectionTest : public ::testing::Test {
};

TEST_F(ElectionTest, typeSetterGetter1) {
    Election elec = Election();
	elec.setvotingType("OPL");
	string actual = elec.getVotingType();
	EXPECT_EQ(actual, "OPL");
}

TEST_F(ElectionTest, numBallotsSetterGetter1){
    Election elec = Election();
	elec.setNumBallots(10);
	int actual = elec.getNumBallots();
    EXPECT_EQ(actual, 10);
}

TEST_F(ElectionTest, numCandidatesSetterGetter1){
    Election elec = Election();
	elec.setNumCandidates(4);
	int actual = elec.getNumCandidates();
    EXPECT_EQ(actual, 4);
}

TEST_F(ElectionTest, candSetterGetter1){
    Election elec = Election();
	Candidate* cand = new Candidate();
	cand->setName("Towlie");
	elec.pushCandidateList(cand);
	vector<Candidate*> list = elec.getCandidateList();
    EXPECT_EQ(cand,list[0]);
	delete cand;
}
}
