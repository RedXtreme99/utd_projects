CXX=g++
CPPFLAGS=-Wall -std=c++11

SRCS= main.cpp

OBJS=$(SRCS:.cpp=.o)

TARGET=csp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
