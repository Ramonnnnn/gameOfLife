CC = g++ -I../thread -I../mutex -I../semaphore -I../time -pthread
CFLAGS = -c -pedantic -ansi -Wall -g


game: game.o input.o logic.o drawer.o board.o main.o ../thread/thread.o ../mutex/mutex.o ../semaphore/semaph.o ../mutex/timeOps.o
	$(CC) -o game game.o input.o logic.o drawer.o board.o main.o ../thread/thread.o ../mutex/mutex.o ../semaphore/semaph.o ../mutex/timeOps.o

#-lDS -L./mostUpdatedDS/DS/
	
main.o: main.cpp game.h
		$(CC) $(CFLAGS) main.cpp


game.o: game.cpp game.h
	$(CC) $(CFLAGS) game.cpp


drawer.o: drawer.cpp drawer.h ../thread/thread.h
	$(CC) $(CFLAGS) drawer.cpp


logic.o: logic.cpp logic.h drawer.h
	$(CC) $(CFLAGS) logic.cpp


input.o: input.cpp input.h coordinate.h
	$(CC) $(CFLAGS) input.cpp


board.o: board.cpp board.h coordinate.h
	$(CC) $(CFLAGS) board.cpp
	

#timeOps.o: ../time/timeOps.cpp ../time/timeOps.h
	#$(CC) $(CFLAGS) ../time/timeOps.cpp
	
	
clean:
	rm -rf *.o
	rm -f game
	
