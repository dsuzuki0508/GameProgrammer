#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <fstream>
#include <string>
#include <map>

#include "ImageDefines.h"

template <typename T>
class Image:public T {
public:
	Image(const std::string& filepath);
	unsigned width()const;
	unsigned height()const;
	void drawImage(unsigned y, unsigned x, typename T::Id image_id);


private:
		unsigned mHeight;
	unsigned mWidth;
	std::vector<std::vector<unsigned >> mImage;
};

using CellsImage       = Image<image_defines::Cells>;
using ClearImage       = Image<image_defines::Clear>;
using LoadingImage     = Image<image_defines::Loading>;
using MenuImage        = Image<image_defines::Menu>;
using StageSelectImage = Image<image_defines::StageSelect>;
using TitleImage       = Image<image_defines::Title>;



#endif // IMAGE_H
