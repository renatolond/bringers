all: bringers.so

bringers.so: bringersV2.cpp bringersV2.h
	g++ -Wl,--export-dynamic -Wall -O1 -shared -fPIC bringersV2.cpp -o bringers.so
