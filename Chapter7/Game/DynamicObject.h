#ifndef GAME_DYNAMICOBJECT_H
#define GAME_DYNAMICOBJECT_H
#include <memory>
#include "Image.h"
class DynamicObject
{
public:
	enum class Type {
		TYPE_1P,
		TYPE_2P,
		TYPE_ENEMY,
		TYPE_UNKNOWN,
	};
	DynamicObject(unsigned y, unsigned x, Type type);
//	DynamicObject(const DynamicObject& o);
	void draw( const std::unique_ptr<CellsImage>& cells_image_ptr) const;
	void update();
private:
	Type mType;
	unsigned mY;
	unsigned mX;
};

#endif // GAME_DYNAMICOBJECT_H
