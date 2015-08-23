#pragma once
#include <vector>
#include "light_string.h"

namespace fs { namespace utils
{

//! 3-way partition quick string sorting with some parallelism
/**
 *	It is better to make interface of this function more STL-like but this way a little bit easier to implement it.
 *	
 */
void string_sort(std::vector<light_string>& data);

}}