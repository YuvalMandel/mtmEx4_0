CC=/usr/local/bin/gcc
CXX=/usr/local/bin/g++
OBJS= gcalc.o graph.o libgraph.a
EXEC=gcalc
SRVR_FLAGS =
DEBUG_FLAG=
COMP_FLAG= -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG

$(EXEC) :$(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@ $(SRVR_FLAGS)
	
MtmParkingLot.o: gcalc.cpp gcalc.h graph.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

graph.o: graph.cpp graph.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
	
libgraph.a: $(OBJS)
	ar -rs $@ $^

clean:
	rm -f $(OBJS) $(EXEC)

