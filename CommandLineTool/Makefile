SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:%.cpp=%.o)
FLAGS   = -std=c++11 -m32 -O2
TARGET  = compete

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -m32 -o $(TARGET)

%.o: %.cpp $(HEADERS)
	g++ -c $(FLAGS) $< -o $@
	
clean:
	rm -rf *.o *~ $(TARGET)