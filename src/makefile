# align: align.c
#
# 	clang -std=c99 -O2 -o align align.c

# compiles objects, links tests, and runs tests
tests: ./tests/align_test.c align.c seq.c

	# compile and emit objects
	clang -std=c99 -O2 -c align.c seq.c

	# compile tests and link
	clang -std=c99 -O2 -o ./tests/align_test align.o seq.o ./tests/align_test.c

	# run tests
	./tests/align_test

# just makes sure the aliases are not tied to files to that
# the run regardless of whether files are updated
.PHONY: clean tests

# deletes all object files, and all test files
clean:
	rm *.o ./tests/*_test
