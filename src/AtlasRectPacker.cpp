#include "AtlasRectPacker.h"
#include "finders_interface.h"
#include "rect_structs.h"

bool AtlasRectPacker::Pack(std::vector<sImageInfo>& aImages, int aAtlasSize, int aPadding)
{
	if (aImages.empty()) 
	{
		return false;
	}

	using SpacesType = rectpack2D::empty_spaces<false>;
	using RectType = rectpack2D::output_rect_t<SpacesType>;

	std::vector<RectType> Rects;

	for(const auto& Image: aImages)
	{
		Rects.push_back({ 0, 0, Image.Width + aPadding * 2, Image.Height + aPadding * 2 });
	}
	
	bool InsertionFailed = false;

	const auto HandleSuccessfulInsertion = [](auto&) {
		bool InsertionFailed = false;
		return rectpack2D::callback_result::CONTINUE_PACKING;
	};

	const auto HandleUnsuccessfulInsertion = [&InsertionFailed](auto&) {
		InsertionFailed = true;
		return rectpack2D::callback_result::CONTINUE_PACKING;
	};

	const auto FinderInput = rectpack2D::make_finder_input(
		aAtlasSize,
		1,
		HandleSuccessfulInsertion,
		HandleUnsuccessfulInsertion,
		rectpack2D::flipping_option::DISABLED
	);

	rectpack2D::find_best_packing<SpacesType>(Rects, FinderInput);

	if(InsertionFailed)
	{
		return false;
	}

	for (size_t Index = 0; Index < Rects.size(); ++Index)
	{
		aImages[Index].Position.x = Rects[Index].x + aPadding;
		aImages[Index].Position.y = Rects[Index].y + aPadding;
	}

	return true;
}