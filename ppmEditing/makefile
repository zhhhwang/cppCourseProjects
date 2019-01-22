ppmEditing.exe: ColorClass.o RowColumnClass.o ColorImageClass.o RectangleClass.o main.o getUserIntOption.o printColorMenu.o setColorOption.o callMenu.o setFillOption.o addRectangle.o
	g++ ColorClass.o RowColumnClass.o ColorImageClass.o RectangleClass.o main.o getUserIntOption.o printColorMenu.o setColorOption.o callMenu.o setFillOption.o addRectangle.o -o ppmEditing.exe

main.o: main.cpp
	g++ -c main.cpp -o main.o

RectangleClass.o: RectangleClass.cpp RectangleClass.h
	g++ -c RectangleClass.cpp -o RectangleClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h
	g++ -c ColorImageClass.cpp -o ColorImageClass.o

ColorClass.o: ColorClass.cpp ColorClass.h
	g++ -c ColorClass.cpp -o ColorClass.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h
	g++ -c RowColumnClass.cpp -o RowColumnClass.o

getUserIntOption.o: getUserIntOption.cpp getUserIntOption.h
	g++ -c getUserIntOption.cpp -o getUserIntOption.o

printColorMenu.o: printColorMenu.cpp printColorMenu.h
	g++ -c printColorMenu.cpp -o printColorMenu.o

setColorOption.o: setColorOption.cpp setColorOption.h
	g++ -c setColorOption.cpp -o setColorOption.o

setFillOption.o: setFillOption.cpp setFillOption.h
	g++ -c setFillOption.cpp -o setFillOption.o

callMenu.o: callMenu.cpp callMenu.h
	g++ -c callMenu.cpp -o callMenu.o

addRectangle.o: addRectangle.cpp addRectangle.h
	g++ -c addRectangle.cpp -o addRectangle.o

clean:
	rm -rf main.o ColorClass.o RowColumnClass.o ColorImageClass.o RectangleClass.o getUserIntOption.o printColorMenu.o setColorOption.o callMenu.o setFillOption.o addRectangle.o ppmEditing.exe 
