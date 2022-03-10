CC = g++
CFLAGS = -Wall -Wextra -g -m32 -Wpedantic

build: 
	$(CC) $(CFLAGS) crypto.cpp -o crypto
	$(CC) $(CFLAGS) stocks.cpp -o stocks
	$(CC) $(CFLAGS) valley.cpp -o valley
	$(CC) $(CFLAGS) ridge.cpp -o ridge
	$(CC) $(CFLAGS) trigigel.cpp -o trigigel

run-p1:
	./crypto

run-p2:
	./stocks

run-p3:
	./valley

run-p4:
	./ridge

run-p5:
	./trigigel


clean:
	rm -rf crypto stocks valley ridge trigigel