#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

typedef uint CATEGORY_ID;

class Category
{
private:
	CATEGORY_ID mId;
	QString mName;

public:
	Category(CATEGORY_ID id = 0, QString name = QString());
	~Category();

	QString getName();
	uint getId();
};

#endif // CATEGORY_H
