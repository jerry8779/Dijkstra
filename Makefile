CC=clang++
C++FLAGS=-Wall -std=c++11 -stdlib=libc++ -pedantic

MAIN_OBJ=main.o
TEST_MAIN_PROG=findPaths 


%.o : %.cpp
	$(CC)  -c $< -o $@ $(C++FLAGS)

all:
	make $(TEST_MAIN_PROG)

$(TEST_MAIN_PROG): $(MAIN_OBJ)
	$(CC) $(C++FLAG) -o $@ $(MAIN_OBJ)


clean:
	(rm -f *.o;)
	rm -f $(TEST_MAIN_PROG)

