all: nouh_p3

nouh_p3: nouh_p3.o knapsack.o
	g++ nouh_p3.o knapsack.o -o submission

knapsack.o:knapsack.cpp
	g++ -c knapsack.cpp -o knapsack.o

nouh_p3.o:nouh_p3.cpp
	g++ -c nouh_p3.cpp -o nouh_p3.o
clean:
	rm -f *.o submission

