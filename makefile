CC=/usr/local/bin/gcc
CXX=/usr/local/bin/g++
OBJS= gcalc.o graph.o
EXEC=gcalc
SRVR_FLAGS =
DEBUG_FLAG=
COMP_FLAG= -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -fPIC

$(EXEC) :$(OBJS)
	export LD_LIBRARY_PATH="/usr/local/lib64:${LD_LIBRARY_PATH}"
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@ $(SRVR_FLAGS)
	
gcalc.o: gcalc.cpp gcalc.h graph.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

graph.o: graph.cpp graph.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
	
libgraph.a: $(OBJS)
	ar -rs $@ $^

clean:
	rm -f $(OBJS) $(EXEC)
	
tar:
	zip gcalc.zip gcalc.cpp gcalc.h graph.cpp graph.h graph.i Makefile test_in.txt test_out.txt design.pdf