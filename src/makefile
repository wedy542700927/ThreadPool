CC := g++  
TARGET := threadpool 
INCLUDE := -I.
LIBS := -lpthread
CXXFLAGS := -g -Wall -D_REENTRANT -std=c++11

OBJECTS := main.o ThreadPool.o Task.o

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)
	
%.o:%.cpp
	$(CC) -c $(CXXFLAGS) $(INCLUDE) $< -o $@ 

.PHONY: clean  
clean:   
	-rm -f $(OBJECTS) $(TARGET)