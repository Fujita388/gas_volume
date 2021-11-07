all: 

o:
	g++ -c -std=c++11 main.cpp split.cpp
	g++ -std=c++11 main.o split.o

py:
	python3 volume.py > volume.dat

test:
	g++ -std=c++11 test.cpp 

clean:
	rm -rf *.o a.out *.lammps test.sh.*
