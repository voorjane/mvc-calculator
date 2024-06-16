CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 #-pedantic -fsanitize=address
TEST_FLAGS = -lcheck -lpthread -lm
COV_FLAG = --coverage
LIB = s21_calc.a

ifeq ($(shell uname), Linux)
        TEST_FLAGS += -lrt -lsubunit
endif

all: s21_calc.a test gcov_report

s21_calc.a:
	$(CC) $(CFLAGS) -c s21_calc.c s21_credit.c
	ar rcs $(LIB) s21_calc.o s21_credit.o

tests.o:
	$(CC) $(CFLAGS) -c s21_calc_test.c
	$(CC) $(CFLAGS) $(COV_FLAG) -c s21_calc.c

test: s21_calc.a tests.o
	$(CC) -o tests $(CFLAGS) *.o -L. $(LIB) $(COV_FLAG) $(TEST_FLAGS)
	./tests

install: clean
	mkdir app
	cd app && qmake ../C7_SmartCalc.pro && make

install-strip: install
	cd app && rm -f *.o moc* ui* Makefile

uninstall:
	rm -rf app

gcov_report:
	gcovr -r . --html --html-details -o report.html
	open report.html

dvi:
	doxygen Doxyfile
	open html/index.html

dist: clean
	mkdir SmartCalc
	cp -r *.c *.h *.cpp *.ui *.pro Makefile SmartCalc
	tar -cvzf SmartCalc.tar.gz SmartCalc
	-rm -rf SmartCalc

leaks: test
	leaks -atExit -- ./tests

app_leaks: uninstall install
	leaks -atExit -- ./app/C7_SmartCalc.app/Contents/MacOS/C7_SmartCalc

valgrind: test
	valgrind --leak-check=full ./tests

app_valgrind: install
	valgrind --leak-check=full ./app/C7_SmartCalc.app/Contents/MacOS/C7_SmartCalc

clang:
	cp ../.clang-format .
	clang-format -n *.c *.h *.cpp
	rm -rf .clang-format

clean:
	@rm -rf *.html *.gcno *.gcda *.o *.out *.css *coverage* *.a tests SmartCalc *.gz html

rebuild:
	$(MAKE) clean
	$(MAKE) all

.PHONY: all clean rebuild test gcov_report leaks valgrind clang install uninstall dist app_leaks app_valgrind install-strip