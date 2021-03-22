CC = g++ -std=c++11
CFLAFS = -Wall -g

FILES = main.o vaccineMonitor.o util.o citizen.o date.o tree.o linkedListString.o bloomFilter.o skipList.o population.o

vaccineMonitor: clean $(FILES)
	$(CC) $(CFLAFS) -o vaccineMonitor $(FILES)

main.o:
	$(CC) $(CFLAFS) -c main.cpp

vaccineMonitor.o:
	$(CC) $(CFLAFS) -c vaccineMonitor.cpp

util.o:
	$(CC) $(CFLAFS) -c util.cpp

citizen.o:
	$(CC) $(CFLAFS) -c citizenRecords/citizen.cpp

date.o:
	$(CC) $(CFLAFS) -c DataStructures/date/date.cpp

tree.o:
	$(CC) $(CFLAFS) -c DataStructures/binaryAvlTree/tree.cpp

linkedListString.o:
	$(CC) $(CFLAFS) -c DataStructures/linkedList/linkedListString.cpp

bloomFilter.o:
	$(CC) $(CFLAFS) -c DataStructures/bloomFilter/bloomFilter.cpp

skipList.o:
	$(CC) $(CFLAFS) -c DataStructures/skipList/skipList.cpp

population.o:
	$(CC) $(CFLAFS) -c DataStructures/population/population.cpp

.PHONY: clean
clean:
	rm -f vaccineMonitor $(FILES)