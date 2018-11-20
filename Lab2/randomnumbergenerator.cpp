/**
  randomnumbergenerator.cpp
  Purpose: generates random number
 */
#include "randomnumbergenerator.h"
#include <ctime>
#include <random>
#include <QDebug>
namespace
{

    static int seed = 0; // seed for randomize method
}

RandomNumberGenerator::RandomNumberGenerator() {}

RandomNumberGenerator::~RandomNumberGenerator() {}

//gets random number
int RandomNumberGenerator::GetRandomInt(int l, int r)
{
    std::mt19937_64 eng(seed); //choice of method for randomization of numbers
    std::uniform_int_distribution<int> distr(l, r); //distributon kit selection for randomization of numbers with a given range
    ++seed;

    return distr(eng);
}
