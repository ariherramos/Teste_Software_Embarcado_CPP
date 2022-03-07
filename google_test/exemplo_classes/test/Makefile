CXX = g++
CXXFLAGS = -g -L/opt/gtest/lib -lgtest -lgtest_main -lpthread
INCS = -I./ -I.. -I/opt/gtest/include
OBJS = ../addition.o addition-test.o ../multiply.o multiply-test.o

main-test: main-test.o addition-test.o multiply-test.o
	$(CXX) -o main-test $(OBJS) $(CXXFLAGS)

.cc.o:
	$(CXX) -c $< -o $@ $(INCS)

clean:
	rm main-test *.o main-test.xml
