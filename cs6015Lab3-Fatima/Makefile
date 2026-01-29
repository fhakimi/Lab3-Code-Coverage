CXX = c++ -v
CFLAGS = -std=c++14 -I.
CCSOURCE = main.cpp cmdline.cpp expr.cpp tests.cpp
HEADERS = cmdline.h expr.h catch.h
OBJ = main.o cmdline.o expr.o tests.o
LINK = -o
COMPILE = -c
build: msdscript
run: msdscript
	./msdscript
msdscript: $(OBJ)
	$(CXX) $(CFLAGS) $(LINK) msdscript $(OBJ)
main.o: main.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(COMPILE) main.cpp
cmdline.o: cmdline.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(COMPILE) cmdline.cpp
expr.o: expr.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(COMPILE) expr.cpp
tests.o: tests.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(COMPILE) tests.cpp
.PHONY: clean
clean:
	rm -f *.o msdscript





