#include "AtlasPacker.h"

namespace fs = std::filesystem;

void AtlasPacker::Pack(const sOptions& aOptions)
{
	mOptions = aOptions;
	EnumerateImages();
}

void AtlasPacker::EnumerateImages()
{
	const auto Folder = fs::path(mOptions.InputPath);
	std::vector<fs::path> ImagesPath;
	
	for(const auto& File : fs::directory_iterator(Folder))
	{
		if (!File.is_regular_file()) 
		{
			continue;
		}

		const auto Extension = File.path().extension().string();
		if (Extension == ".png" || Extension == ".jpg") 
		{
			ImagesPath.emplace_back(File.path());
		}
	}
}
