CPPFLAGS=-std=c++11
CPPFILE=main.cpp split.cpp
OFILE=main.o split.o

all: o

o:
	cp ../rescale.lammpstrj .
	$(CXX) -c $(CPPFLAGS) $(CPPFILE)
	$(CXX) $(CPPFLAGS) $(OFILE)

clean:
	$(RM) *.o a.out *.log g_v_with_surf01.e* g_v_with_surf01.o*
