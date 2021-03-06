OPENCV ?= opencv4
CXXFLAGS ?= -std=c++17 -O2 -Werror ${shell pkg-config --cflags ${OPENCV}}
LIBS ?= ${shell pkg-config --libs ${OPENCV}}
PREFIX ?= /usr/local
BINDIR ?= ${PREFIX}/bin

doxabin: main.cpp
	${CXX} ${CXXFLAGS} -I gsm/Doxa -o $@ $< ${LIBS}

.PHONY: clean
clean:
	${RM} doxabin

.PHONY: install
install: doxabin
	install -m 577 doxabin ${BINDIR}
