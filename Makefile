CXX = g++
CXXFLAGS = -std=c++11 -pthread

server: main_server.cpp ChatServer.cpp
	$(CXX) $(CXXFLAGS) main_server.cpp ChatServer.cpp -o server

client: main_client.cpp ChatClient.cpp
	$(CXX) $(CXXFLAGS) main_client.cpp ChatClient.cpp -o client

all: server client

clean:
	rm -f server client