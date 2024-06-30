# ID: 212051007
# Mail: mayrozen45@gmail.com

CXX = clang++
CXXFLAGS = -std=c++11 -Werror -Wsign-conversion -g
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = node.cpp Complex.cpp TestCounter.cpp Test.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

run: demo test
	./demo
	./test

demo: Demo.o $(filter-out TestCounter.o Test.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) -v $^ $(SFML_LIBS) -o demo

test: TestCounter.o Test.o $(filter-out Demo.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) -v $^ $(SFML_LIBS) -o test  # Add SFML_LIBS here

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-,clang-analyzer-,cppcoreguidelines-,performance-,portability-,readability-,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp tree.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o demo test
