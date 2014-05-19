CC = g++
CFLAGS = -Wall
DEPS = naiveAttack.hpp statAttack.hpp rc4.hpp bias.hpp
OBJ_FILES_NAIVE = main_naive.o naiveAttack.o bias.o rc4.o
OBJ_FILES_STATALGO = main_stat.o statAttack.o bias.o rc4.o


execNaive : $(OBJ_FILES_NAIVE)
	$(CC) $(CFLAGS) -o $@ $^

execStat : $(OBJ_FILES_STATALGO)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -f $(OBJ_FILES_NAIVE) $(OBJ_FILES_STATALGO)

mrproper: clean
	rm -rf execStat execNaive