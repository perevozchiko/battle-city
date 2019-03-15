#include "utils.h"

#include <cmath>
#include <algorithm>


namespace Utils {

bool equalFloat(float x, float y)
{
    float maxXYOne = std::max({1.0f, std::fabs(x), std::fabs(y)});
    return std::fabs(x - y) <= std::numeric_limits<float>::epsilon()*maxXYOne;
}

}
