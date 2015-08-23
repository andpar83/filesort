#pragma once
#include <vector>
#include "light_string.h"
#include "buffer.h"

namespace fs
{

//! Class for parsing buffer to separate strings, splitting them by \n-symbol
/**
 *	Last string in buffer should be terminated with \n
 *  (this way all strings will be new-line-symbol terminated)
 *	and could be sorted and outputted safely 
 *	(no any 2 strings will be outputted to the same line because of absence of new-line for one of them)
 */
class buffer_parser
{
public:
	std::vector<light_string> parse(buffer& buf) const;
};

}