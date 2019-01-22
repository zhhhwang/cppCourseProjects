simulation.exe:  main.o SimuClass.o EventClass.o getUserIntInput.o getUserDoubleInput.o random.o 
	g++  main.o SimuClass.o EventClass.o getUserIntInput.o getUserDoubleInput.o random.o -o simulation.exe

main.o: main.cpp LinkedNodeClass.h SortedListClass.h FIFOQueueClass.h
	g++ -c main.cpp -o main.o

SimuClass.o: SimuClass.cpp SimuClass.h LinkedNodeClass.h SortedListClass.h FIFOQueueClass.h
	g++ -c SimuClass.cpp -o SimuClass.o

EventClass.o: EventClass.cpp EventClass.h LinkedNodeClass.h SortedListClass.h FIFOQueueClass.h
	g++ -c EventClass.cpp -o EventClass.o

getUserIntInput.o: getUserIntInput.cpp getUserIntInput.h
	g++ -c getUserIntInput.cpp -o getUserIntInput.o

getUserDoubleInput.o: getUserDoubleInput.cpp getUserDoubleInput.h
	g++ -c getUserDoubleInput.cpp -o getUserDoubleInput.o

random.o: random.cpp random.h
	g++ -c random.cpp -o random.o

clean:
	rm -rf main.o SimuClass.o EventClass.o getUserIntInput.o getUserDoubleInput.o random.o simulation.exe 


