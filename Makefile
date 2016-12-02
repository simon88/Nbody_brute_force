CXX=g++
CXXFLAGS=-std=gnu++11
LDFLAGS=
SOURCES=main.cpp Particle.cpp ArgumentParser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=n_body_brute_force

.PHONY: clean mrproper

all: $(EXEC)

$(EXEC): $(OBJECTS) 
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

