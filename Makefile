EXE_W	= gbraids-worker
EXE_S 	= gbraids-server
EXE_I 	= gbraids-interface
CPP 	= g++
CFLAGS	= --std=c++11 -O3 -DNDEBUG -I ./tclap/include

all: $(EXE_S) $(EXE_W) $(EXE_I)

%o:%.cpp %.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE_W):dist/message.o dist/client.o dist/worker.o src/braid.o src/permutation.o src/work.o src/main-worker.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(EXE_S):dist/message.o dist/server.o src/init.o src/main-server.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(EXE_I):dist/message.o dist/client.o dist/interface.o src/main-interface.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)
clean:
	$(RM) $(EXE_W) $(EXE_S) $(EXE_I) dist/*.o dist/*~ src/*.o src/*~
