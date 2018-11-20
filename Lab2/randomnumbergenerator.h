/**
  randomnumbergenerator.h
  Purpose: generates random number
 */

#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H
class RandomNumberGenerator //class for generating random numbers
{
public:
    RandomNumberGenerator();
    ~RandomNumberGenerator();
    /**
     * gets random number
     *
     * @brief GetRandomInt
     * @param l
     * @param r
     * @return random number
     */
    int GetRandomInt(int l, int r);
};

#endif // RANDOMNUMBERGENERATOR_H
