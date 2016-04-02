GCC = gcc -std=c11

CHECK_INCLUDE = -isystem /usr/local/include
CHECK_LIB = -L/usr/local/lib -lcheck

USER_DIR = .

GCCFLAGS += -g -Wall -Wextra

EXECUTABLE = read_1bit_bmp
TESTS = read_1bit_bmp_test

all : $(TESTS) $(EXECUTABLE)

clean :
	rm -f $(TESTS) *.o read_1bit_bmp *.gch
	rm -r *.dSYM

read_1bit_bmp.o : $(USER_DIR)/read_1bit_bmp.c
	$(GCC) $(GCCFLAGS) -c $(USER_DIR)/read_1bit_bmp.c

read_1bit_bmp_test.o : $(USER_DIR)/read_1bit_bmp_test.c
	$(GCC) $(GCCFLAGS) $(CHECK_INCLUDE) -c $(USER_DIR)/read_1bit_bmp_test.c $(CHECK_LIB)

read_1bit_bmp_test : read_1bit_bmp.o read_1bit_bmp_test.o
	$(GCC) $(GCCFLAGS) $(CHECK_INCLUDE) $^ -o $@ $(CHECK_LIB)

read_1bit_bmp : $(USER_DIR)/main.c $(USER_DIR)/read_1bit_bmp.c
	$(GCC) $^ -o $@

