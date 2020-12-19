all: contactbook

contactbook: interface.o
	gcc src/interface.c -I. src/data_base.c src/utility_func.c  -o  contact -g `pkg-config --cflags --libs gtk+-3.0` -lsqlite3 && ./contact
interface.o: src/interface.c
	gcc src/interface.c -I. src/data_base.c src/utility_func.c  -o  contact -g `pkg-config --cflags --libs gtk+-3.0` -lsqlite3

clean: 
	rm -rf *.o contact contacts_base.db projetGTK.glade~



