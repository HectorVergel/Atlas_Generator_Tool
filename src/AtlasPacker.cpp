#include "AtlasPacker.h"
#include "AtlasRectPacker.h"
#include <unordered_set>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace fs = std::filesystem;

void AtlasPacker::Pack(const sOptions& aOptions)
{
	mOptions = aOptions;
	EnumerateImages();
	
	if(!ValidateImages())
	{
		return;
	}

	AtlasRectPacker RectPacker;

	if(!RectPacker.Pack(mImages, mOptions.AtlasSize, mOptions.Padding))
	{
		return;
	}

	BuildAtlas();
}

void AtlasPacker::EnumerateImages()
{
	mImages.clear();
	const auto Folder = fs::path(mOptions.InputPath);

	for (const auto& File : fs::directory_iterator(Folder))
	{
		if (!File.is_regular_file()) continue;

		const auto Extension = File.path().extension().string();
		if (Extension != ".png" && Extension != ".jpg") continue;

		sImageInfo ImageInfo;
		ImageInfo.Path = File.path();
		ImageInfo.Name = File.path().stem().string();

		if (stbi_info(ImageInfo.Path.string().c_str(), &ImageInfo.Width, &ImageInfo.Height, &ImageInfo.Channels))
		{
			mImages.push_back(std::move(ImageInfo));
		}
		else
		{
			LOG("LOAD WARNING: Invalid image: " + ImageInfo.Name);
		}
	}
}

bool AtlasPacker::ValidateImages()
{
	bool Result(true);
	std::unordered_set<std::string> ImagesNames;

	for(const auto& Image : mImages)
	{
		if(Image.Height <= 0 ||Image.Width <= 0)
		{
			LOG("VALIDATION ERROR: Invalid image size: " + Image.Name);
			Result = false;
		}
		else if(Image.Height > mOptions.AtlasSize || Image.Width > mOptions.AtlasSize)
		{
			LOG("VALIDATION ERROR: Image is larger than atlas: " + Image.Name);
			Result = false;
		}
		else if(Image.Channels != 3 && Image.Channels != 4)
		{
			LOG("VALIDATION ERROR: Unsupported channels: " + Image.Name);
			Result = false;
		}
		else if(!ImagesNames.insert(Image.Name).second)
		{
			LOG("VALIDATION ERROR: Duplicated name with image: " + Image.Name);
			Result = false;
		}
	}
	return Result;
}

void AtlasPacker::BuildAtlas()
{

	if (mImages.empty())
	{
		LOG("No images to build atlas.");
		return;
	}

	const int Channels = 4; // RGBA
	const int AtlasSize = mOptions.AtlasSize;

	std::vector<unsigned char> AtlasBuffer(AtlasSize * AtlasSize * Channels, 0);

	for (const auto& Img : mImages)
	{
		int w, h, c;
		unsigned char* ImageData = stbi_load(Img.Path.string().c_str(), &w, &h, &c, Channels);
		if (!ImageData)
		{
			LOG("Failed to load image: " + Img.Name);
			continue;
		}

		// Copy image to atlas.
		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < w; ++x)
			{
				int SrcIndex = (y * w + x) * Channels;
				int DestinationX = Img.Position.x + x;
				int DestinationY = Img.Position.y + y;
				int DestinationIndex = (DestinationY * AtlasSize + DestinationX) * Channels;

				for (int ch = 0; ch < Channels; ++ch)
				{
					AtlasBuffer[DestinationIndex + ch] = ImageData[SrcIndex + ch];
				}
			}
		}

		stbi_image_free(ImageData);
	}

	std::string OutputPath = mOptions.OutputPath;
	if (OutputPath.empty()) 
	{
		OutputPath = "atlas.png";
	}

	if (!stbi_write_png(OutputPath.c_str(), AtlasSize, AtlasSize, Channels,
		AtlasBuffer.data(), AtlasSize * Channels))
	{
		LOG("Failed to write atlas PNG.");
	}
	else
	{
		LOG("Atlas successfully saved to: " + OutputPath);
	}
	
}
