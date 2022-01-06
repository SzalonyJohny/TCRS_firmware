/*
 * helper_func.hpp
 *
 *  Created on: Jan 5, 2022
 *      Author: jan
 */

#ifndef INC_HELPER_FUNC_HPP_
#define INC_HELPER_FUNC_HPP_

#include <cstdio>

template <const std::size_t n, const uint32_t increment, typename T>
bool rising_edge_or_overflow(const T &value,
                             const auto &threshold,
                             const std::size_t &i) {

    static T last_value[n] = {0};

    if ((value > threshold &&
         last_value[i] <= threshold) ||  // normal rising edge
        (increment + last_value[i] >= threshold && last_value[i] < threshold &&
         value < last_value[i]))  // over flow and crosses the threshold for
                                  // example last = 498, now = 5, threshold =
                                  // 500
    {
        last_value[i] = value;
        return true;
    } else {
        last_value[i] = value;
        return false;
    }
}


#endif /* INC_HELPER_FUNC_HPP_ */
