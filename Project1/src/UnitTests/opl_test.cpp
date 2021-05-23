#include "../include/opl.h"

#include "gtest/gtest.h"

namespace votesys{

// The fixture for testing class Foo.
class OPLTest : public ::testing::Test {
};

TEST_F(OPLTest, seatSetterGetter1) {
    OPL opl = OPL();
	opl.setNumSeats(10);
	int actual = opl.getNumSeats();
    EXPECT_EQ(actual,10);
}

TEST_F(OPLTest, partyVoteSetterGetter1){
    OPL opl = OPL();

	opl.setRepVotes(33);
    opl.setDemVotes(28);
    opl.setIndVotes(22);

	int actualRep = opl.getRepVotes();
	int actualDem = opl.getDemVotes();
	int actualInd = opl.getIndVotes();

    EXPECT_EQ(actualRep,33);
    EXPECT_EQ(actualDem,28);
    EXPECT_EQ(actualInd,22);
}

TEST_F(OPLTest, firstSeatSetterGetter1){
    OPL opl = OPL();
	vector<int> expected{4,3,2};
	opl.setFirstSeats(expected);
	vector<int> actual = opl.getFirstSeats();
    EXPECT_EQ(actual, expected);
}

TEST_F(OPLTest, secondSeatSetterGetter1){
    OPL opl = OPL();
	vector<int> expected{0,0,1};
	opl.setSecondSeats(expected);
	vector<int> actual = opl.getSecondSeats();
    EXPECT_EQ(actual, expected);
}

TEST_F(OPLTest, candListSetterGetter1){
    OPL* opl = new OPL();
	Candidate* ar = new Candidate();
	Candidate* ad = new Candidate();
	Candidate* ai = new Candidate();
	Candidate* aw = new Candidate();

	ar->setName("ar");
	ad->setName("ad");
	ai->setName("ai");
	aw->setName("aw");

    opl->pushList('R', ar);
	opl->pushList('D', ad);
	opl->pushList('I', ai);
	opl->pushList('W', aw);

    vector<Candidate*> listr = opl->getList('R');
	vector<Candidate*> listd = opl->getList('D');
	vector<Candidate*> listi = opl->getList('I');
	vector<Candidate*> listw = opl->getList('W');

    EXPECT_EQ(ar,listr[0]);
    EXPECT_EQ(ad,listd[0]);
    EXPECT_EQ(ai,listi[0]);
    EXPECT_EQ(aw,listw[0]);
	delete opl;
}
TEST_F(OPLTest, quotaSetterGetter1){
    OPL opl = OPL();
	opl.calculateQuota(83, 10,"test.txt");
	int actual = opl.getQuota();
    EXPECT_EQ(actual, 8);
}
TEST_F(OPLTest, calculateSeatAllocation1){
    OPL* opl = new OPL();
    opl->setNumSeats(10);
    Candidate* ar = new Candidate();
	ar->setName("ar");
	ar->setNumVotes(10);
	Candidate* br = new Candidate();
	br->setName("br");
	br->setNumVotes(13);
	Candidate* cr = new Candidate();
	cr->setName("cr");
	cr->setNumVotes(10);
	Candidate* dr = new Candidate();
	dr->setName("dr");
	dr->setNumVotes(4);

	opl->pushList('R', ar);
	opl->pushList('R', br);
	opl->pushList('R', cr);
	opl->pushList('R', dr);

	Candidate* ad = new Candidate();
	ad->setName("ad");
	Candidate* bd = new Candidate();
	bd->setName("bd");
	Candidate* cd = new Candidate();
	cd->setName("cd");
	Candidate* dd = new Candidate();
	dd->setName("dd");

	ad->setNumVotes(11);
	bd->setNumVotes(4);
	cd->setNumVotes(6);
	dd->setNumVotes(7);


	opl->pushList('D', ad);
	opl->pushList('D', bd);
	opl->pushList('D', cd);
	opl->pushList('D', dd);

	Candidate* ai = new Candidate();
	ai->setName("ai");
	Candidate* bi = new Candidate();
	bi->setName("bi");
	Candidate* ci = new Candidate();
	ci->setName("ci");

	ai->setNumVotes(11);
	bi->setNumVotes(8);
	ci->setNumVotes(3);

	opl->pushList('I', ai);
	opl->pushList('I', bi);
	opl->pushList('I', ci);
	vector<int> votes{33,28,22};
	vector<int> seats = opl->calculateSeatAllocation(votes, 8, "test.txt");
    vector<int> expected{4,3,3};
    EXPECT_EQ(seats, expected);
	delete opl;
}
TEST_F(OPLTest, countVote1){
	OPL* opl = new OPL();
    opl->setNumSeats(10);
    Candidate* ar = new Candidate();
	ar->setName("ar");
	ar->setNumVotes(10);
	Candidate* br = new Candidate();
	br->setName("br");
	br->setNumVotes(13);
	Candidate* cr = new Candidate();
	cr->setName("cr");
	cr->setNumVotes(10);
	Candidate* dr = new Candidate();
	dr->setName("dr");
	dr->setNumVotes(4);

	opl->pushList('R', ar);
	opl->pushList('R', br);
	opl->pushList('R', cr);
	opl->pushList('R', dr);

	Candidate* ad = new Candidate();
	ad->setName("ad");
	Candidate* bd = new Candidate();
	bd->setName("bd");
	Candidate* cd = new Candidate();
	cd->setName("cd");
	Candidate* dd = new Candidate();
	dd->setName("dd");

	ad->setNumVotes(11);
	bd->setNumVotes(4);
	cd->setNumVotes(6);
	dd->setNumVotes(7);


	opl->pushList('D', ad);
	opl->pushList('D', bd);
	opl->pushList('D', cd);
	opl->pushList('D', dd);

	Candidate* ai = new Candidate();
	ai->setName("ai");
	Candidate* bi = new Candidate();
	bi->setName("bi");
	Candidate* ci = new Candidate();
	ci->setName("ci");

	ai->setNumVotes(11);
	bi->setNumVotes(8);
	ci->setNumVotes(3);

	opl->pushList('I', ai);
	opl->pushList('I', bi);
	opl->pushList('I', ci);

	opl->countVote(83,"test.txt");

	vector<Candidate*> actual = opl->getList('W');
	vector<Candidate*> expected = {br,ar,cr,dr,ad,dd,cd,ai,bi,ci};
	EXPECT_EQ(actual, expected);
	delete opl;
}
TEST_F(OPLTest, countVote2){
    OPL* opl = new OPL();
	opl->setNumSeats(10);
	Candidate* ar = new Candidate();
	ar->setName("ar");
	ar->setNumVotes(11);
	Candidate* br = new Candidate();
	br->setName("br");
	br->setNumVotes(10);
	Candidate* cr = new Candidate();
	cr->setName("cr");
	cr->setNumVotes(9);
	Candidate* dr = new Candidate();
	dr->setName("dr");
	dr->setNumVotes(4);

	opl->pushList('R', ar);
	opl->pushList('R', br);
	opl->pushList('R', cr);
	opl->pushList('R', dr);

	Candidate* ad = new Candidate();
	ad->setName("ad");
	Candidate* bd = new Candidate();
	bd->setName("bd");
	Candidate* cd = new Candidate();
	cd->setName("cd");
	Candidate* dd = new Candidate();
	dd->setName("dd");
	Candidate* ed = new Candidate();
	ed->setName("ed");
	Candidate* fd = new Candidate();
	fd->setName("fd");
	Candidate* gd = new Candidate();
	gd->setName("gd");

	ad->setNumVotes(11);
	bd->setNumVotes(4);
	cd->setNumVotes(6);
	dd->setNumVotes(7);
	ed->setNumVotes(7);
	fd->setNumVotes(7);
	gd->setNumVotes(7);

	opl->pushList('D', ad);
	opl->pushList('D', bd);
	opl->pushList('D', cd);
	opl->pushList('D', dd);
	opl->pushList('D', ed);
	opl->pushList('D', fd);
	opl->pushList('D', gd);
	opl->setNumBallots(86);
	opl->countVote(86, "test.txt");
	vector<Candidate*> actual = opl->getList('W');
	vector<Candidate*> expected = {ar,br,cr,dr,ad,dd,ed,fd,gd,cd};
    EXPECT_EQ(actual,expected);
	delete opl;
}
TEST_F(OPLTest, countVote3){
    OPL* opl = new OPL();
	opl->setNumSeats(9);
	Candidate* ar = new Candidate();
	ar->setName("ar");
	ar->setParty('R');
	ar->setNumVotes(1);
	Candidate* br = new Candidate();
	br->setName("br");
	br->setParty('R');
	br->setNumVotes(3);
	Candidate* cr = new Candidate();
	cr->setName("cr");
	cr->setParty('R');
	cr->setNumVotes(10);
	Candidate* dr = new Candidate();
	dr->setName("dr");
	dr->setParty('R');
	dr->setNumVotes(14);

	opl->pushList('R', ar);
	opl->pushList('R', br);
	opl->pushList('R', cr);
	opl->pushList('R', dr);

	Candidate* ad = new Candidate();
	ad->setName("ad");
	ad->setParty('D');
	Candidate* bd = new Candidate();
	bd->setName("bd");
	bd->setParty('D');
	Candidate* cd = new Candidate();
	cd->setName("cd");
	cd->setParty('D');
	Candidate* dd = new Candidate();
	dd->setName("dd");
	dd->setParty('D');
	ad->setNumVotes(11);
	bd->setNumVotes(14);
	cd->setNumVotes(16);
	dd->setNumVotes(17);


	opl->pushList('D', ad);
	opl->pushList('D', bd);
	opl->pushList('D', cd);
	opl->pushList('D', dd);

	Candidate* ai = new Candidate();
	ai->setName("ai");
	ai->setParty('I');

	Candidate* bi = new Candidate();
	bi->setName("bi");
	bi->setParty('I');

	Candidate* ci = new Candidate();
	ci->setName("ci");
	ci->setParty('I');


	ai->setNumVotes(11);
	bi->setNumVotes(18);
	ci->setNumVotes(23);

	opl->pushList('I', ai);
	opl->pushList('I', bi);
	opl->pushList('I', ci);
	opl->setNumBallots(138);
	opl->countVote(138, "test.txt");
	vector<Candidate*> actual = opl->getList('W');
	vector<Candidate*> expected = {dr,cr,dd,cd,bd,ad,ci,bi,ai};
    EXPECT_EQ(actual, expected);
	delete opl;
}
}