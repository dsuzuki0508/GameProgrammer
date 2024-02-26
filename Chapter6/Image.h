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
	void drawImage(unsigned y, unsigned x, typename T::Id image_id, bool use_color = false, unsigned color=0xffffff);
	void drawImage(unsigned y, unsigned x, const image_defines::Plot& p, bool use_color = false, unsigned color = 0xffffff);
	void fill(unsigned color = 0);

protected:
	unsigned mHeight;
	unsigned mWidth;
	std::vector<std::vector<unsigned >> mImage;
};

class FontImage :public Image<image_defines::Font> {
public:
	void drawString(unsigned row, unsigned column, std::string, bool use_color = false, unsigned color = 0xffffff);
	void drawChar(unsigned row, unsigned column, char c, bool use_color = false, unsigned color = 0xffffff);
	static FontImage& instance();
private:
	FontImage(const std::string& filepath);
	FontImage(const FontImage&);
	~FontImage();
};

using CellsImage       = Image<image_defines::Cells>;
using ClearImage       = Image<image_defines::Clear>;
using LoadingImage     = Image<image_defines::Loading>;
using MenuImage        = Image<image_defines::Menu>;
using StageSelectImage = Image<image_defines::StageSelect>;
using TitleImage       = Image<image_defines::Title>;



#endif // IMAGE_H
