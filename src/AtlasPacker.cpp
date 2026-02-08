#include "AtlasPacker.h"

namespace fs = std::filesystem;

void AtlasPacker::Pack(const sOptions& aOptions)
{
	mOptions = aOptions;
	EnumerateImages();
	LoadImagesInfo();
	
	if(ValidateImages)
	{

	}
	else
	{

	}
}

void AtlasPacker::EnumerateImages()
{
	const auto Folder = fs::path(mOptions.InputPath);
	mImagesPaths.clear();
	
	for(const auto& File : fs::directory_iterator(Folder))
	{
		if (!File.is_regular_file()) 
		{
			continue;
		}

		const auto Extension = File.path().extension().string();
		if (Extension == ".png" || Extension == ".jpg") 
		{
			mImagesPaths.emplace_back(File.path());
		}
	}
}

void AtlasPacker::LoadImagesInfo()
{
	mImages.clear();

	for (const auto& Path : mImagesPaths) 
	{
		sImageInfo ImageInfo;
		ImageInfo.Path = Path;
		ImageInfo.Name = Path.stem().string();

		if(stbi_info(Path.string().c_str(), &ImageInfo.Width, &ImageInfo.Height, &ImageInfo.Channels))
		{
			mImages.push_back(ImageInfo);
		}
		else 
		{
			LOG("LOAD WARNING: Invalid image found: " + ImageInfo.Name + " with the following path: " + ImageInfo.Path.string());
		}
	}
}

bool AtlasPacker::ValidateImages()
{

	return false;
}
