project(NPuzzle)

set(SRCS
	main.cpp
	Parser.cpp
	State.cpp
	GridPoint.cpp
	)
add_executable(npuzzle ${SRCS})
