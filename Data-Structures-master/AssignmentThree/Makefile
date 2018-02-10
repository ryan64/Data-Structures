CXX = g++
RM = rm -f
CXXFLAGS = -Wall -std=c++11
TARGET = sparse

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) *.cpp

clean:
	$(RM) $(TARGET) *.diff *.stdout *.stderr TIMEOUT COMPILE.err *.out
