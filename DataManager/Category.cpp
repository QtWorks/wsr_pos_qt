#include "Category.h"

Category::Category(CATEGORY_ID id, QString name)
{
	mId = id;
	mName = name;
}

Category::~Category()
{

}

uint Category::getId()
{
	return mId;
}

QString Category::getName()
{
	return mName;
}
