#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <iostream>

namespace 
{
	#define LOG(str) std::cout << str << std::endl

	using u8 = std::uint8_t;
	using u32 = std::uint32_t;
	struct Vector2
	{
		int x = 0;
		int y = 0;
	};
}

#endif