CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iincludes
LDFLAGS = -lsqlite3
SRC = src/main.cpp src/db.cpp src/auth.cpp src/driver_menu.cpp src/admin_menu.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = bin/autopark_app

all: create_dirs $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

create_dirs:
	mkdir -p bin

clean:
	rm -f $(TARGET) $(OBJ)

run: all
	./$(TARGET)