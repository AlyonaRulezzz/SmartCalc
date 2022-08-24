.PHONY: all re calc clean check test
#.PHONY если есть файлы с именем как цель, они игнорируются

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
TST_LIBS :=  -lcheck -lm -lpthread
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	CFLAGS+=-D LINUX
else
	ifeq ($(OS),Darwin)
		CFLAGS+=-D MAC
	endif
endif

# all, install, uninstall, clean, dvi, dist, tests, gcov_report

all: test calc.a gcov_report

re: clean test gcov_report

tests: calc.a test.o
	$(CC) $(CFLAGS) test.o calc.a $(TST_LIBS) -o test
	@./test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

calc.a: calc.o
	@ar rcs calc.a calc.o
	ranlib calc.a

calc.o: calc.c
	$(CC) $(CFLAGS) -c calc.c -o calc.o

gcov_report: gcov_test.info
	@genhtml -o report/ gcov_test.info
	@open report/index.html

gcov_test.info: gcov_test gcov_test.gcda
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: test.c calc.c
	$(CC) $(CFLAGS) --coverage test.c calc.c $(TST_LIBS) -o gcov_test

gcov_test.gcda:
	@chmod +x *
	@./gcov_test

install:
	make clean
	mkdir build
	cd calculatorrr && qmake && make && make clean && rm Makefile && cd ../ && mv calculatorrr/calculatorrr.app build

uninstall:
	rm -rf build*

dvi:
	open Read_me.html

dist:
	rm -rf Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/src
	cp -r ./build/calculatorrr.app Archive_calc_v1.0/src/
	tar cvzf Archive_calc_v1.0.tgz Archive_calc_v1.0/
	rm -rf Archive_calc_v1.0/

clean: 
	@rm -rf test gcov_test *.gcno *.gcda *.info report *.{a,o,dSYM,out} $(EXECUTABLE) build

cpp:
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py *.h *.c
	cppcheck calc.c test.c 
	
valgrind:
	valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./test
