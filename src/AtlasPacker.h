#ifndef ATLAS_PACKER_H
#define ATLAS_PACKER_H

#include <string>
#include "stb_image.h"
#include "AtlasPackerTypes.h"


class AtlasPacker 
{
public:

	void Pack(const sOptions& aOptions);

private:

	void EnumerateImages();
	bool ValidateImages();
	void BuildAtlas();

	sOptions mOptions;
	std::vector<fs::path> mImagesPaths;
	std::vector<sImageInfo> mImages;
};

#endif