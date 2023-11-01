CC=gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -c
LDFLAGS = -std=c11 -Wall -Werror -Wextra
FS= -fsanitize=address -g
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

TARGET=s21_matrix.a

SOURCE = s21_matrix.c s21_utils.c
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})
UNAME_S := $(shell uname -s)
NEW_TEST_SOURCE=$(wildcard unit_test/s21_*.c)

ifeq ($(UNAME_S), Darwin)
	ADD_LIB = -lcheck $(shell pkg-config --cflags --libs check)
endif
ifeq ($(UNAME_S), Linux)
	ADD_LIB = -lcheck -pthread -lrt -lm
endif

all: clean s21_matrix.a test

s21_matrix.a: $(SOURCE)
	@$(CC) $(CFLAGS) $(SOURCE)
	@ar rc s21_matrix.a $(OBJECTS)
	@ranlib s21_matrix.a

test: s21_matrix.a
	@$(CC) $(LDFLAGS) $(SOURCE) $^ $(NEW_TEST_SOURCE) -o test $(ADD_LIB)
	./test

gcov_report: clean s21_matrix.a
	@$(CC) $(LDFLAGS) --coverage $(SOURCE) $(NEW_TEST_SOURCE) s21_matrix.a -o test $(ADD_LIB)
	./test
	@lcov -t "test" -o tests.info -c -d .
	@genhtml -o coverage tests.info
	open coverage/index.html

valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

clean:
	@rm -f *.o *.gcno *.gcda
	@rm -f *.info *.gcov
	@rm -f test s21_matrix.a
	@rm -f *.txt *.out
	@rm -rf ./gcov_report ./report test.DSYM a.out.dSYM coverage

style:
	@clang-format -style=Google -i *.c *.h */*.c */*.h
	@cppcheck --enable=all --suppress=missingIncludeSystem ${SOURCE}

.PHONY:	s21_matrix.a test valgrind