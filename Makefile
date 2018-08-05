all: client server

client:
	g++ -Wall src/client.cpp -o bin/net-alert-client.exe `wx-config --cflags --libs` -static

server:
	g++ -Wall src/server.cpp -o bin/net-alert-server.exe `wx-config --cflags --libs` -static