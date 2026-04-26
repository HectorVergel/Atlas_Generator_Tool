#ifndef ATLAS_PACKER_TYPES_H
#define ATLAS_PACKER_TYPES_H

#include <filesystem>
#include "Types.hpp"


namespace fs = std::filesystem;

struct sImageInfo
{
	fs::path Path;
	std::string Name;
	int Width;
	int Height;
	int Channels;
	Vector2 Position;
};

struct sOptions
{
	std::string InputPath;
	std::string OutputPath = "atlas.png";
	int AtlasSize = 1024;
	u8 Padding = 2;
};

#endif