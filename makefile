align: align.c

	clang -std=c99 -O2 -o align align.c

test: align_test.c align.c
	clang -std=c99 -O2 -c align_test.c
	clang -o align_test align_test.o

clean:
	rm align
