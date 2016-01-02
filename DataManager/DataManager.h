#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QtSql/QtSql>
#include "Category.h"
#include "Item.h"

#define CATEGORY_TABLE_CREATION_COMMAND "create table if not exists category \
(id integer primary key autoincrement not null unique,\
name text,\
create_time text,\
delete_time text,\
enable integer);"

#define ITEM_TABLE_CREATION_COMMAND "create table if not exists item \
(category_id integer,\
id integer primary key autoincrement not null unique,\
name text,\
hint text,\
price integer,\
discount integer,\
print integer,\
print_together integer,\
position_x integer,\
position_y integer,\
color integer,\
sub_item_list text,\
create_time text,\
delete_time text,\
enable integer);"

typedef struct _BUTTON_COLOR
{
	QString name;
	unsigned int r;
	unsigned int g;
	unsigned int b;
} BUTTON_COLOR;

class DataManager
{
private:
    QSqlDatabase mDB;
	QList<Category*> mCategoryList;
	QList<Item*> mItemList;
	DataManager();

    bool createDB();
    void createCategoryList();
    void createItemList();
public:
	static DataManager* getInstance();
	QList<Category*> getCategoryList();
    QList<Item*> getItemList();
	QList<BUTTON_COLOR> getColorList();
	QList<Item*> getItemListByCategory(uint category_id);

    bool insertCategory(Category *category);
    bool insertItem(Item *item);
    bool deleteItem(Item *item);
};

#endif // DATAMANAGER_H
