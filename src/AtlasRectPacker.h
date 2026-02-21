#ifndef ATLAS_RECT_PACKER_H
#define ATLAS_RECT_PACKER_H

#include <vector>
#include "AtlasPackerTypes.h"

class AtlasRectPacker
{
public:
	bool Pack(std::vector<sImageInfo>& aImages, int aAtlasSize, int aPadding);
};

#endif