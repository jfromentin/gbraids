EXE_W		= gb-worker
EXE_S 		= gb-server
EXE_I 		= gb-interface
EXE_A   	= gb-alone
CPP 		= g++ 
CFLAGS		= --std=c++11 -O3 -DNDEBUG -g

all: $(EXE_S) $(EXE_W) $(EXE_I) $(EXE_A)

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

src/dynnikov.o:src/dynnikov.cpp src/dynnikov.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/braid.o:src/braid.cpp src/braid.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/gtask.o:src/gtask.cpp src/gtask.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/signature.o:src/signature.cpp src/signature.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/init.o:src/init.cpp src/init.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE_W):dist/message.o dist/client.o dist/worker.o src/braid.o src/dynnikov.o src/signature.o src/main-worker.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(EXE_S):dist/message.o dist/server.o src/init.o src/braid.o src/dynnikov.o src/signature.o src/gtask.o src/main-server.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(EXE_I):dist/message.o dist/client.o dist/interface.o src/main-interface.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

$(EXE_A):src/init.o src/braid.o src/dynnikov.o src/signature.o src/main-alone.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)


clean:
	$(RM) -rf $(EXE_W) $(EXE_S) $(EXE_I) $(EXE_A)  dist/*.o dist/*~ src/*.o src/*~
