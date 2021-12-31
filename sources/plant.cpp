#include "object.h"

Object::Object(ObjectType aType) :
	mType (aType)
{}

Object::ObjectType 
Object::getType()
{
	return mType;
}