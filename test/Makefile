CFLAGS := -Wall -std=c++11 -I../
all: main

main: main.o
	g++ $(CFLAGS) $^ -L../ -largument -o $@

%.o: %.cpp %.hpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	$(RM) main.o main