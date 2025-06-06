CC = g++
CFLAGS = -Iinclude -Wall
OBJDIR = obj
BINDIR = bin

all: $(BINDIR)/main1 $(BINDIR)/main2

$(OBJDIR)/Word.o: src/Word.cpp include/Word.h
	$(CC) $(CFLAGS) -c src/Word.cpp -o $(OBJDIR)/Word.o

$(OBJDIR)/GameState.o: src/GameState.cpp include/GameState.h include/Word.h
	$(CC) $(CFLAGS) -c src/GameState.cpp -o $(OBJDIR)/GameState.o

$(BINDIR)/main1: main1.cpp $(OBJDIR)/Word.o
	$(CC) $(CFLAGS) main1.cpp $(OBJDIR)/Word.o -o $(BINDIR)/main1

$(BINDIR)/main2: main2.cpp $(OBJDIR)/Word.o $(OBJDIR)/GameState.o
	$(CC) $(CFLAGS) main2.cpp $(OBJDIR)/Word.o $(OBJDIR)/GameState.o -o $(BINDIR)/main2

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/main1 $(BINDIR)/main2