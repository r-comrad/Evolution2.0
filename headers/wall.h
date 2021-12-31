#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class Object
{
public:
	enum ObjectType { NUN = 0, BOT = 1};

	Object(ObjectType aType = NUN);
	ObjectType getType();

private:
	ObjectType mType;
};

#endif //OBJECT_H