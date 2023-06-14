project(Pokemon)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pokemon
        main.cpp
        Types.h
        Pokemon.h Pokemon.cpp
        Move.h Move.cpp
        GameError.h
        GameBase.h GameBase.cpp
        GameTest.h GameTest.cpp
        GameAI.h GameAI.cpp)
