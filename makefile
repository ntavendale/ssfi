CC=gcc
CFLAGS= -c -pipe -std=c++11 -pthread -g -std=gnu++11 -Wall -W -fPIC -DQT_QML_DEBUG -I../ssfi -I.
DEPS= fileprocessor.h utilities.h threadidlist.h wordmap.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
sssfi:  main.o fileprocessor.o utilities.o threadidlist.o wordmap.o
	$(CC) -o ssfi main.o fileprocessor.o utilities.o threadidlist.o wordmap.o -pthread -L/usr/lib/x86_64-linux-gnu -lboost_system -L/usr/lib/x86_64-linux-gnu -lboost_filesystem -lstdc++