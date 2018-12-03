CXX = g++
CC = g++
CXXFLAGS = -std=c++11
LDLIBS =
# implicit compile rule: $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c
# implicit linking rule: $(CC) $(LDFLAGS) $(LOADLIBES) $(LDLIBS) (P.S. LOADLIBES is deprecated)

vpath %.cpp ./
vpath %.h ./
vpath %.o obj

OBJDIR=obj
#SRCDIR=src

OBJS = dna.o ptn.o organ.o resource.o map.o

go.x               : main.o $(OBJS)
	mkdir -p $(OBJDIR)
	$(CXX) $^ $(LDLIBS) -o $@
	mv *.o $(OBJDIR)
dna.o              : dna.h
ptn.o              : ptn.h
organ.o            : organ.h
resource.o         : resource.h
map.o              : map.h
main.o             : main.cpp
.PHONY: clean
clean :
	rm -rf *.x *.o $(OBJDIR)
