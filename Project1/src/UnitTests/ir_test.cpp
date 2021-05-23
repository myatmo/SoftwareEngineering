#include "../include/ir.h"

#include "gtest/gtest.h"

namespace votesys{

// The fixture for testing class Foo.
class IRTest : public ::testing::Test {
};

TEST_F(IRTest, winnerSetterGetter1) {
    IR ir = IR();
    Candidate* candA = new Candidate();
    candA->setName("Candidate A");
    candA->setNumVotes(10);
    ir.setWinner(candA);
    Candidate* actual = ir.getWinner();
    EXPECT_EQ(actual, candA);
    delete candA;
}

TEST_F(IRTest, loserSetterGetter1){
    IR ir = IR();
    Candidate* candA = new Candidate();
    candA->setName("Candidate A");
    candA->setNumVotes(10);
    ir.setLoser(candA);
    Candidate* actual = ir.getLoser();
    EXPECT_EQ(actual, candA);
    delete candA;
}

TEST_F(IRTest, countVote1){
    IR* ir = new IR();
    ir->setNumBallots(10);
	ir->setNumCandidates(4);
    vector<string> votes_case1 = {"1,2,3,4", "1,3,2,", "1,,,2", "1,,2,", "1,,,", "1,2,,", ",1,2,3", ",1,,2", ",,1,2", ",2,,1"};
    for (int i = 0; i < ir->getNumCandidates(); i++) {
        Candidate* cand = new Candidate();
        cand->setName("Cand"+to_string(i));
        cand->setNumVotes(0);
        ir->pushCandidateList(cand);
    }
    for(int i=0; i<(int)votes_case1.size();i++){
        Ballot* ball = new Ballot();
        ball->setRank(1);
        ball->setVote(votes_case1[i]);
        ball->setID(i);
        vector<int> curvote = ball->getVote();
        for(int j=0; j<ir->getNumCandidates();j++){
            if(curvote[j]==1){
                ir->getCandidateList()[j]->pushBallotList(ball);
                ir->getCandidateList()[j]->setNumVotes(ir->getCandidateList()[j]->getNumVotes()+1);
            }
        }
    }
    ir->setWinner(ir->countVote("test.txt"));
    vector<vector<int>> expected= {{6,2,1,1}};
    vector<vector<int>> actual = ir->getTransferVotes();
    EXPECT_EQ(actual,expected);
    EXPECT_EQ(ir->getWinner(),ir->getCandidateList()[0]);
    delete ir;
}

TEST_F(IRTest, countVote2){
    IR* ir = new IR();
    ir->setNumBallots(10);
	ir->setNumCandidates(4);
    vector<string> votes_case2 = {"1,2,3,4", "1,3,2,", "1,,,2", "1,,2,", "1,,,", "2,,,1", ",1,2,3", ",1,,2", "2,,1,", ",2,,1"};
    for (int i = 0; i < ir->getNumCandidates(); i++) {
        Candidate* cand = new Candidate();
        cand->setName("Cand"+to_string(i));
        cand->setNumVotes(0);
        ir->pushCandidateList(cand);
    }
    for(int i=0; i<(int)votes_case2.size();i++){
        Ballot* ball = new Ballot();
        ball->setRank(1);
        ball->setVote(votes_case2[i]);
        ball->setID(i);
        vector<int> curvote = ball->getVote();
        for(int j=0; j<ir->getNumCandidates();j++){
            if(curvote[j]==1){
                ir->getCandidateList()[j]->pushBallotList(ball);
                ir->getCandidateList()[j]->setNumVotes(ir->getCandidateList()[j]->getNumVotes()+1);
            }
        }
    }
    ir->setWinner(ir->countVote("test.txt"));
    vector<vector<int>> expected= {{5,2,1,2},{6,2,0,2}};
    vector<vector<int>> actual = ir->getTransferVotes();
    EXPECT_EQ(actual,expected);
    EXPECT_EQ(ir->getWinner(),ir->getCandidateList()[0]);
    delete ir;
}
TEST_F(IRTest, countVote3){
    IR* ir = new IR();
    ir->setNumBallots(10);
	ir->setNumCandidates(4);
    vector<string> votes_case3 = {"1,2,3,4", "1,3,2,", "1,,,2", "1,,2,", "1,,,", "2,,,1", "2,1,,3", ",1,,2", ",,1,2", ",2,,1"};
    for (int i = 0; i < ir->getNumCandidates(); i++) {
        Candidate* cand = new Candidate();
        cand->setName("Cand"+to_string(i));
        cand->setNumVotes(0);
        ir->pushCandidateList(cand);
    }
    for(int i=0; i<(int)votes_case3.size();i++){
        Ballot* ball = new Ballot();
        ball->setRank(1);
        ball->setVote(votes_case3[i]);
        ball->setID(i);
        vector<int> curvote = ball->getVote();
        for(int j=0; j<ir->getNumCandidates();j++){
            if(curvote[j]==1){
                ir->getCandidateList()[j]->pushBallotList(ball);
                ir->getCandidateList()[j]->setNumVotes(ir->getCandidateList()[j]->getNumVotes()+1);
            }
        }
    }
    ir->setWinner(ir->countVote("test.txt"));
    vector<vector<int>> expected= {{5,2,1,2},{5,2,0,3},{6,0,0,4}};
    vector<vector<int>> actual = ir->getTransferVotes();
    EXPECT_EQ(actual,expected);    
    EXPECT_EQ(ir->getWinner(),ir->getCandidateList()[0]);
    delete ir;
}
TEST_F(IRTest, countVote4){
    IR* ir = new IR();
    ir->setNumBallots(10);
	ir->setNumCandidates(4);
    vector<string> votes_case4 = {"1,2,3,4", "1,3,2,", "1,,,2", "1,,2,", "1,,,", "2,,,1", "3,1,2,", ",1,,2", ",,1,2", ",2,,1"};
    for (int i = 0; i < ir->getNumCandidates(); i++) {
        Candidate* cand = new Candidate();
        cand->setName("Cand"+to_string(i));
        cand->setNumVotes(0);
        ir->pushCandidateList(cand);
    }
    for(int i=0; i<(int)votes_case4.size();i++){
        Ballot* ball = new Ballot();
        ball->setRank(1);
        ball->setVote(votes_case4[i]);
        ball->setID(i);
        vector<int> curvote = ball->getVote();
        for(int j=0; j<ir->getNumCandidates();j++){
            if(curvote[j]==1){
                ir->getCandidateList()[j]->pushBallotList(ball);
                ir->getCandidateList()[j]->setNumVotes(ir->getCandidateList()[j]->getNumVotes()+1);
            }
        }
    }
    ir->setWinner(ir->countVote("test.txt"));
    vector<vector<int>> expected= {{5,2,1,2},{5,2,0,3},{6,0,0,4}};
    vector<vector<int>> actual = ir->getTransferVotes();
    EXPECT_EQ(actual,expected);
    EXPECT_EQ(ir->getWinner(),ir->getCandidateList()[0]);
    delete ir;
}
TEST_F(IRTest, countVote5){
    IR* ir = new IR();
    ir->setNumBallots(10);
	ir->setNumCandidates(4);
    vector<string> votes_case5 = {"1,2,3,4", "1,3,2,", "1,,,2", "1,,2,", ",,1,2", "2,,,1", ",1,,2", ",1,,2", "2,,1,", ",2,,1"};
    for (int i = 0; i < ir->getNumCandidates(); i++) {
        Candidate* cand = new Candidate();
        cand->setName("Cand"+to_string(i));
        cand->setNumVotes(0);
        ir->pushCandidateList(cand);
    }
    for(int i=0; i<(int)votes_case5.size();i++){
        Ballot* ball = new Ballot();
        ball->setRank(1);
        ball->setVote(votes_case5[i]);
        ball->setID(i);
        vector<int> curvote = ball->getVote();
        for(int j=0; j<ir->getNumCandidates();j++){
            if(curvote[j]==1){
                ir->getCandidateList()[j]->pushBallotList(ball);
                ir->getCandidateList()[j]->setNumVotes(ir->getCandidateList()[j]->getNumVotes()+1);
            }
        }
    }
    ir->setWinner(ir->countVote("test.txt"));
    vector<vector<int>> expected1 = {{4,2,2,2},{4,0,2,4},{5,0,0,5}};
    vector<vector<int>> expected2 = {{4,2,2,2},{5,2,0,3},{5,0,0,5}};
    vector<vector<int>> expected3 = {{4,2,2,2},{5,3,2,0},{6,3,0,0}};
    vector<vector<int>> actual = ir->getTransferVotes();
    EXPECT_EQ(actual,expected1);
    EXPECT_EQ(actual,expected2);
    EXPECT_EQ(actual,expected3);
    EXPECT_EQ(ir->getCandidateList()[0],ir->getWinner());
    EXPECT_EQ(ir->getCandidateList()[3],ir->getWinner());
    delete ir;
}
}
