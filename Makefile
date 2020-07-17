EXE	   	= gbraids
CPP 		= g++-7
CFLAGS		= --std=c++11  -fcilkplus -O3 -DNDEBUG
LIBS		= -lcilkrts
all:$(EXE)

src/permutation.o:src/permutation.cpp src/permutation.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/dynnikov.o:src/dynnikov.cpp src/dynnikov.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/braid.o:src/braid.cpp src/braid.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/init.o:src/init.cpp src/init.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/signature.o:src/signature.cpp src/signature.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

src/results.o:src/results.cpp src/results.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE):src/init.o src/dynnikov.o src/braid.o src/signature.o  src/main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)


clean:
	$(RM) $(EXE) data/* dist/*.o dist/*~ src/*.o src/*~
