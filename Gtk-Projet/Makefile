all: contactbook

contactbook: interface.o
	gcc interface.c -I. data_base.c utility_func.c  -o  contact -g `pkg-config --cflags --libs gtk+-3.0` -lsqlite3
interface.o: interface.c
	gcc interface.c -I. data_base.c utility_func.c  -o  contact -g `pkg-config --cflags --libs gtk+-3.0` -lsqlite3

clean: 
	rm -rf *.o contact contacts_base.db



