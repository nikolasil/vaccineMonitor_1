CC = g++
CFLAFS = -g

FILES = vaccineMonitor.o util.o citizen.o date.o tree.o linkedListString.o bloomFilter.o

vaccineMonitor: clean $(FILES)
	$(CC) $(CFLAFS) -o vaccineMonitor $(FILES)

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

.PHONY: clean
clean:
	rm -f vaccineMonitor $(FILES)