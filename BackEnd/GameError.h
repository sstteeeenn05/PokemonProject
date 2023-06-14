#pragma once

#include <stdexcept>

class FileOpenError : public std::invalid_argument {
public:
    explicit FileOpenError(const std::string &fileName) : std::invalid_argument("cannot open " + fileName) {}
};

class NoPokemonError : public std::invalid_argument {
public:
    explicit NoPokemonError() : std::invalid_argument("player must has at least one pokemon to battle") {}
};

class PokemonNotfoundError : public std::invalid_argument {
public:
    explicit PokemonNotfoundError(const std::string &pokemonName) :
            std::invalid_argument("cannot found Pokemon " + pokemonName) {}
};

class MoveNotFoundError : public std::invalid_argument {
public:
    explicit MoveNotFoundError(const std::string &moveName) :
            std::invalid_argument("cannot found Move " + moveName) {}
};

class PowerPointError : public std::logic_error {
public:
    explicit PowerPointError(const std::string &moveName) :
    std::logic_error("PP of move " + moveName + " is not enough") {}
};

class InvalidPokemonError : public std::invalid_argument {
public:
    explicit InvalidPokemonError(const std::string &what) : std::invalid_argument(what) {}
};

class InvalidCommandError : public std::invalid_argument {
public:
    explicit InvalidCommandError(const std::string &what) : std::invalid_argument(what) {}
};