EXEFILE = test

$(EXEFILE): $(OBJECTS)
	g++ main_test.cpp opl_test.cpp ir_test.cpp candidate_test.cpp ballot_test.cpp election_test.cpp ../election.cpp ../opl.cpp ../ir.cpp ../candidate.cpp ../ballot.cpp -o test -lgtest -lpthread

clean:
	rm $(EXEFILE)