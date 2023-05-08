CC = gcc
CFLAGS = -std=c89 -pthread
TARGET = prog

$(TARGET): main.o c_queue.o customer.o teller.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o c_queue.o customer.o teller.o

main.o: main.c c_queue.h customer.h teller.h struct.h mutex.h
	$(CC) $(CFLAGS) -c main.c

c_queue.o: c_queue.c c_queue.h customer.h struct.h mutex.h
	$(CC) $(CFLAGS) -c c_queue.c

customer.o: customer.c customer.h c_queue.h mutex.h
	$(CC) $(CFLAGS) -c customer.c

teller.o: teller.c struct.h c_queue.h teller.h mutex.h
	$(CC) $(CFLAGS) -c teller.c

clean:
	rm -f *.o $(TARGET)

