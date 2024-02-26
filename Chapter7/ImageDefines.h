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
			IMG_PLAYER1,
			IMG_PLAYER2,
			IMG_ITEM_BOMB,
			IMG_ITEM_POWER,
			IMG_HORIZONTAL_BLAST,
			IMG_VERTICAL_BLAST,
			IMG_ENEMY,
			IMG_WALL,
			IMG_BRICK,
			IMG_SPACE,
			IMG_BOMB,
			IMG_CROSSED_BLAST,
			IMG_UNKNOWN,
		};
		const std::map<Id, Plot> plots = {
			{Id::IMG_PLAYER1,          { 0,   0, 16, 16}},
			{Id::IMG_PLAYER2,          { 0,  16, 16, 16}},
			{Id::IMG_ITEM_BOMB,        { 0,  32, 16, 16}},
			{Id::IMG_ITEM_POWER,       { 0,  48, 16, 16}},
			{Id::IMG_HORIZONTAL_BLAST, { 16,  0, 16, 16}},
			{Id::IMG_VERTICAL_BLAST,   { 16, 16, 16, 16}},
			{Id::IMG_ENEMY,            { 16, 32, 16, 16}},
			{Id::IMG_WALL,             { 16, 48, 16, 16}},
			{Id::IMG_BRICK,            { 32,  0, 16, 16}},
			{Id::IMG_SPACE,            { 32, 16, 16, 16}},
			{Id::IMG_BOMB,             { 32, 32, 16, 16}},
			{Id::IMG_CROSSED_BLAST,    { 32, 48, 16, 16}},
			{Id::IMG_UNKNOWN,          { 48, 48, 16, 16}},
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
	class Font {
	public:
		enum class Id {
			IMG_UNKNOWN,
		};
		const std::map<Id, Plot> plots = {
			{Id::IMG_UNKNOWN, {80, 120,   16,   8}},
		};
	};
}

#endif // IMAGE_DEFINES_H
