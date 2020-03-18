EXE_W	= gbraids-worker
EXE_S 	= gbraids-server
EXE_I 	= gbraids-interface
CPP 	= g++ 
CFLAGS	= --std=c++11 -O3 -DNDEBUG -I ./tclap/include

all: $(EXE_S) $(EXE_W) $(EXE_I)

dist/message.o:dist/message.cpp dist/message.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

dist/client.o:dist/client.cpp dist/client.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

dist/server.o:dist/server.cpp dist/server.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

dist/interface.o:dist/interface.cpp dist/interface.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

dist/worker.o:dist/worker.cpp dist/worker.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/permutation.o:src/permutation.cpp src/permutation.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/work.o:src/work.cpp src/work.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/braid.o:src/braid.cpp src/braid.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/init.o:src/init.cpp src/init.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE_W):dist/message.o dist/client.o dist/worker.o src/braid.o src/permutation.o src/work.o src/main-worker.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(EXE_S):dist/message.o dist/server.o src/init.o src/main-server.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(EXE_I):dist/message.o dist/client.o dist/interface.o src/main-interface.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)
clean:
	$(RM) $(EXE_W) $(EXE_S) $(EXE_I) dist/*.o dist/*~ src/*.o src/*~
