output: functions.o main.o
	g++ -o output functions.o main.o
output.o: functions.C 
	g++ -c functions.C
main.o: main.C 
	g++ -c main.C

clean:
	rm *.o *.out output