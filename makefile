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
	export LD_LIBRARY_PATH="/usr/local/lib64:${LD_LIBRARY_PATH}"
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

graph.o: graph.cpp graph.h
	export LD_LIBRARY_PATH="/usr/local/lib64:${LD_LIBRARY_PATH}"
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
	
libgraph.a: $(OBJS)
	export LD_LIBRARY_PATH="/usr/local/lib64:${LD_LIBRARY_PATH}"
	ar -rs $@ $^
	swig -c++ -Wall -python graph.i
	//usr/local/bin/g++ -DNDEBUG --pedantic-errors -Wall -Werror -I/usr/local/include/python3.6m -fPIC -shared graph_wrap.cxx libgraph.a -o _graph.so -std=c++11

clean:
	rm -f $(OBJS) $(EXEC)
	
tar:
	zip gcalc.zip gcalc.cpp gcalc.h graph.cpp graph.h graph.i Makefile test_in.txt test_out.txt design.pdf