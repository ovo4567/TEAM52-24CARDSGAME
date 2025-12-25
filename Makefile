CC = g++
CFLAGS = -Wall -std=c++11
LDFLAGS = -lncursesw

TARGET = 24game

OBJS = main.o generate.o generateasciiart.o takeinput.o displaymessage.o timeattackmode.o 24cardgame.o hint.o tutorial.o tutorialminigame.o

HEADERS = generate.h asciiart.h takeinput.h displaymessage.h timeattackmode.h 24cardgame.h hint.h tutorial.h tutorialminigame.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $<

generate.o: generate.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $<

generateasciiart.o: generateasciiart.cpp asciiart.h
	$(CC) $(CFLAGS) -c $<

takeinput.o: takeinput.cpp takeinput.h
	$(CC) $(CFLAGS) -c $<

displaymessage.o: displaymessage.cpp displaymessage.h
	$(CC) $(CFLAGS) -c $<

timeattackmode.o: timeattackmode.cpp timeattackmode.h 24cardgame.h
	$(CC) $(CFLAGS) -c $<

24cardgame.o: 24cardgame.cpp 24cardgame.h
	$(CC) $(CFLAGS) -c $<

hint.o: hint.cpp hint.h
	$(CC) $(CFLAGS) -c $<

tutorial.o: tutorial.cpp tutorial.h tutorialminigame.h displaymessage.h takeinput.h
	$(CC) $(CFLAGS) -c $<

tutorialminigame.o: tutorialminigame.cpp tutorialminigame.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
