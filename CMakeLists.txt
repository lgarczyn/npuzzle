project(NPuzzle)

set(SRCS
	main.cpp
	Parser.cpp
	State.cpp
	Generator.cpp
	GridPoint.cpp
	Heuristics.cpp
	tools.cpp
	CliOptParser.cpp
	Heuristics.cpp
	Solver.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ofast -std=c++11 -Wall -Wextra")
add_executable(npuzzle ${SRCS})
target_link_libraries(npuzzle termcap)
