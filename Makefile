CXX = clang++
LDFLAGS = -std=c++20 -march=native -O3 -DNDEBUG
PREFIX = /usr/local

.PHONY: install
install:
	$(CXX) ./src/main.cpp $(LDFLAGS) -o mkpass.o
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp mkpass.o $(DESTDIR)$(PREFIX)/bin/mkpass

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/mkpass
