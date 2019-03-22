#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <random>
namespace BattleCity {

/** @class
 *
 */
class RandomGen
{
public:
    RandomGen() : engine{device()} {}

    int generate(int min, int max)
    {
        if (min > max)
        {
            std::swap(min, max);
        }
        if (min != distribution.min() || max != distribution.max())
        {
            distribution = std::uniform_int_distribution<int>(min, max);
        }
        return distribution(engine);
    }

    int operator()(int min, int max)
    {
        return generate(min, max);
    }

private:
    std::random_device device;
    std::mt19937 engine{device()};
    std::uniform_int_distribution<> distribution;
};
} //namespace BattleCity
#endif // RANDOMGEN_H
