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

OBJS = dna.o ptn.o organ.o resource.o map.o creature.o

# exe
go.x               : main.o $(OBJS)
	mkdir -p $(OBJDIR)
	$(CXX) $^ $(LDLIBS) -o $@
	mv *.o $(OBJDIR)
check.x            : check.o $(OBJS)
	mkdir -p $(OBJDIR)
	$(CXX) $^ $(LDLIBS) -o $@
	mv *.o $(OBJDIR)

disp_map.x         : disp_map.o $(OBJS)
	mkdir -p $(OBJDIR)
	$(CXX) $^ $(LDLIBS) -o $@
	mv *.o $(OBJDIR)

# obj
dna.o              : dna.h
ptn.o              : ptn.h
organ.o            : organ.h
resource.o         : resource.h
map.o              : map.h
creature.o         : creature.h

# for exe
main.o             : main.cpp
check.o            : check.cpp
disp_map.o         : disp_map.cpp
.PHONY: clean
clean :
	rm -rf *.x *.o *.dat $(OBJDIR)
