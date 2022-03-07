CXX = g++
CXXFLAGS = -g
INCS = -I./
OBJS = addition.o multiply.o

exampleapp: main.cc $(OBJS)
	$(CXX) $(CXXFLAGS) -o main main.cc $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm *.o main
