CC = fcc

all:
	@mkdir -p build
	$(CC) -o build/sqlite_fuzz src/harness.c src/sqlite3.c

clean:
	rm -rf build
	rm -rf .*.o.bc
	rm -rf .*.o
