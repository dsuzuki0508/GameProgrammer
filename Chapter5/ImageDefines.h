#ifndef IMAGE_DEFINES_H
#define IMAGE_DEFINES_H
#include <map>

namespace image_defines {
	struct Plot {
		unsigned y;
		unsigned x;
		unsigned heigth;
		unsigned width;
	};
	class Cells {
	public:
		enum class Id {
			IMG_SPACE,
			IMG_WALL,
			IMG_BLOCK,
			IMG_GOAL,
			IMG_PLAYER,
			IMG_UNKNOWN,
		};
		const std::map<Id, Plot> plots = {
			{Id::IMG_SPACE,   { 0,   0, 32, 32}},
			{Id::IMG_WALL,    { 0,  32, 32, 32}},
			{Id::IMG_BLOCK,   { 0,  64, 32, 32}},
			{Id::IMG_GOAL,    { 0,  96, 32, 32}},
			{Id::IMG_PLAYER,  { 0, 128, 32, 32}},
			{Id::IMG_UNKNOWN, {32, 160,  0,  0}},
		};
	};
	class Clear {
	public:
		enum class Id {
			IMG_CLEAR,
			IMG_UNKNOWN,
		};
		const std::map<Id, Plot> plots = {
			{Id::IMG_CLEAR,   {  0,   0, 240, 320}},
			{Id::IMG_UNKNOWN, {240, 320,   0,   0}},
		};
	};
	class Loading {
	public:
		enum class Id {
			IMG_LOADING,
			IMG_UNKNOWN,
		};
		const std::map<Id, Plot> plots = {
			{Id::IMG_LOADING, {  0,   0, 240, 320}},
			{Id::IMG_UNKNOWN, {240, 320,   0,   0}},
		};
	};
	class Menu {
	public:
		enum class Id {
			IMG_MENU,
			IMG_UNKNOWN,
		};
		const std::map<Id, Plot> plots = {
			{Id::IMG_MENU,    {  0,   0, 240, 320}},
			{Id::IMG_UNKNOWN, {240, 320,   0,   0}},
		};
	};
	class StageSelect {
	public:
		enum class Id {
			IMG_STAGE_SELECT,
			IMG_UNKNOWN,
		};
		const std::map<Id, Plot> plots = {
			{Id::IMG_STAGE_SELECT, {  0,   0, 240, 320}},
			{Id::IMG_UNKNOWN,      {240, 320,   0,   0}},
		};
	};
	class Title {
	public:
		enum class Id {
			IMG_TITLE,
			IMG_UNKNOWN,
		};
		const std::map<Id, Plot> plots = {
			{Id::IMG_TITLE,   {  0,   0, 240, 320}},
			{Id::IMG_UNKNOWN, {240, 320,   0,   0}},
		};
	};
}

#endif // IMAGE_DEFINES_H
