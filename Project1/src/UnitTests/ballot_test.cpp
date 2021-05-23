#include "../include/ballot.h"

#include "gtest/gtest.h"

namespace votesys{

// The fixture for testing class Foo.
class BallotTest : public ::testing::Test {
};

TEST_F(BallotTest, rankSetterGetter1) {
    Ballot ballot = Ballot();
    ballot.setRank(1);
    int actual = ballot.getRank();
    EXPECT_EQ(actual, 1);
}
TEST_F(BallotTest, voteSetterGetter1){
    Ballot ballot = Ballot();
    vector<int> expectedvote{1,2,3,4};
    ballot.setVote("1,2,3,4");
    vector<int> actualvote = ballot.getVote();
    EXPECT_EQ(actualvote, expectedvote);
}
 // namespace my
}


