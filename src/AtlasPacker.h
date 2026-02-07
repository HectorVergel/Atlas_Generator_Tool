#ifndef ATLAS_PACKER_H
#define ATLAS_PACKER_H

#include <iostream>
#include <string>
#include <filesystem>

#include "stb_image.h"
#include "Types.hpp"

namespace fs = std::filesystem;

struct sOptions
{
	std::string InputPath;
	std::string OutputPath = "atlas.png";
	u8 AtlasSize = 1024;
};

class AtlasPacker {
public:

	void Pack(const sOptions& aOptions);

private:

	struct sImageInfo
	{
		fs::path Path;
		std::string Name;
		u32 Width;
		u32 Height;
		u8 Channels;
		Vector2 position;
	};

	void EnumerateImages();

	sOptions mOptions;
	std::vector<sImageInfo> mImages;
};

#endif