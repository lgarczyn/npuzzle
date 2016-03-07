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
	Heuristics.cpp Heuristics.hpp Solver.cpp Solver.hpp
	)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")

add_executable(npuzzle ${SRCS})
