# Detect OS
ifeq ($(OS),Windows_NT)
    PLATFORM = WINDOWS
    CXX = g++
    CXXFLAGS = -std=c++11 -pthread -D_WIN32
    LDFLAGS = -lws2_32
    DELETE = del
    SERVER_EXE = server.exe
    CLIENT_EXE = client.exe
else
    PLATFORM = UNIX
    CXX = g++
    CXXFLAGS = -std=c++11 -pthread
    LDFLAGS = 
    DELETE = rm -f
    SERVER_EXE = server
    CLIENT_EXE = client
endif

server: main_server.cpp ChatServer.cpp
	$(CXX) $(CXXFLAGS) main_server.cpp ChatServer.cpp -o $(SERVER_EXE) $(LDFLAGS)

client: main_client.cpp ChatClient.cpp
	$(CXX) $(CXXFLAGS) main_client.cpp ChatClient.cpp -o $(CLIENT_EXE) $(LDFLAGS)

all: server client

clean:
	$(DELETE) $(SERVER_EXE) $(CLIENT_EXE)