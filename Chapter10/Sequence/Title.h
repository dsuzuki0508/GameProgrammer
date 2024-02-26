#ifndef SEQUENCEC_TITLE_H
#define SEQUENCEC_TITLE_H
#include <memory>
#include "Image.h"
#include "Sequence/Child.h"
namespace Sequence {
	class Title: public Child
	{
	public:
		Title();
		Base* update(Parent* const parent);
	private:
		std::unique_ptr<TitleImage> mTitleImagePtr;
		unsigned mSelectedMode;
	};
}

#endif // SEQUENCEC_TITLE_H