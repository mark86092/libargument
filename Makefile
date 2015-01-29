CFLAGS := -Wall -std=c++11
all: libargument.a

%.o: %.cpp %.hpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

libargument.a: argument.o
	ar rcs libargument.a argument.o

.PHONY: test
test:
	cd test && make

clean:
	$(RM) *.o
