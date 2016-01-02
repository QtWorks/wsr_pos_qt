#include "DataManager.h"

static DataManager *mDataManager = NULL;

DataManager::DataManager()
{
	mCategoryList = QList<Category*>();

	mCategoryList.append(new Category(0, QString("수상스키류")));
	mCategoryList.append(new Category(1, QString("물놀이류")));
	mCategoryList.append(new Category(2, QString("패키지")));
#if 0
	mItemList = QList<Item*>();

	mItemList.append(new Item(0, 0, "수상스키", "", 25000, true, true, false, 1, 1));
	mItemList.append(new Item(0, 1, "웨이크보드", "", 25000, true, true, false, 2, 1));
	mItemList.append(new Item(0, 2, "수상스키 (초보)", "", 60000, true, true, false, 1, 2));
	mItemList.append(new Item(0, 3, "웨이크보드 (초보)", "", 60000, true, true, false, 2, 2));

	mItemList.append(new Item(1, 4, "보팅 (A코스)", "", 150000, true, true, false, 4, 1));
	mItemList.append(new Item(1, 5, "보팅 (B코스)", "", 100000, true, true, false, 5, 1));
	mItemList.append(new Item(1, 6, "보팅 (C코스)", "", 50000, true, true, false, 6, 1));
	mItemList.append(new Item(1, 7, "바나나", "", 20000, true, true, false, 4, 2));
	mItemList.append(new Item(1, 8, "마블", "", 20000, true, true, false, 5, 2));
	mItemList.append(new Item(1, 9, "더블땅콩", "", 20000, true, true, false, 6, 2));
	mItemList.append(new Item(1, 10, "밴드웨곤", "", 20000, true, true, false, 4, 3));
	mItemList.append(new Item(1, 11, "디스코팡팡", "", 20000, true, true, false, 5, 3));
	mItemList.append(new Item(1, 12, "헥사곤", "", 20000, true, true, false, 6, 3));
	mItemList.append(new Item(1, 13, "밴드웨곤", "", 20000, true, true, false, 4, 4));
	mItemList.append(new Item(1, 14, "날으는 바나나", "", 25000, true, true, false, 5, 4));

	mItemList.append(new Item(2, 15, "패키지 #1", "", 28000, true, true, false, 8, 1));
	mItemList.append(new Item(2, 16, "패키지 #2", "", 30000, true, true, false, 9, 1));
	mItemList.append(new Item(2, 17, "패키지 #3", "", 45500, true, true, false, 10, 1));
	mItemList.append(new Item(2, 18, "패키지 #4", "", 59500, true, true, false, 8, 2));
	mItemList.append(new Item(2, 19, "들꽃 (대)", "", 10000, true, true, false, 9, 2));
	mItemList.append(new Item(2, 20, "들꽃 (소)", "", 5000, true, true, false, 10, 2));
	mItemList.append(new Item(2, 21, "c-7", "", 700, true, true, false, 8, 3));
	mItemList.append(new Item(2, 22, "c-8", "", 800, true, true, false, 9, 3));
	mItemList.append(new Item(2, 23, "c-9", "", 800, true, true, false, 10, 3));
	mItemList.append(new Item(2, 24, "c-10", "", 800, true, true, false, 8, 4));
#else
    createDB();
    createItemList();
#endif
}

DataManager* DataManager::getInstance()
{
	if(mDataManager == NULL)
	{
		mDataManager = new DataManager();
	}

	return mDataManager;
}

bool DataManager::createDB()
{
    mDB = QSqlDatabase::addDatabase("QSQLITE");
    mDB.setDatabaseName( "D:\\jenire\\pos.db3");

    if (mDB.open())
    {
        QSqlQuery query(mDB);

        query.exec(CATEGORY_TABLE_CREATION_COMMAND);
        query.exec(ITEM_TABLE_CREATION_COMMAND);

        return true;
    }

    return false;
}

void DataManager::createCategoryList()
{
    QSqlQuery query(mDB);

    query.prepare("SELECT * FROM category WHERE enable=1;");
    query.exec();

    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();

        mCategoryList.append(new Category(id, name));
    }
}

void DataManager::createItemList()
{
    QSqlQuery query(mDB);

    query.prepare("SELECT * FROM item WHERE enable=1;");
    query.exec();

    while (query.next())
    {
        int category_id = query.value(0).toInt();
        int id = query.value(1).toInt();
        QString name = query.value(2).toString();
		QString hint = query.value(3).toString();
		int price = query.value(4).toInt();
		bool discount = query.value(5).toBool();
		bool print = query.value(6).toBool();
		bool print_together = query.value(7).toBool();
		int position_x = query.value(8).toInt();
		int position_y = query.value(9).toInt();
		int color = query.value(10).toInt();
        //QList<ITEM_ID> sub_item_list =

		mItemList.append(new Item(category_id, id, name, hint, price, discount, print, print_together, position_x, position_y, color));
    }
}

QList<Category*> DataManager::getCategoryList()
{
	return mCategoryList;
}

QList<Item*> DataManager::getItemList()
{
    return mItemList;
}

QList<BUTTON_COLOR> DataManager::getColorList()
{
	QList<BUTTON_COLOR> color_list;

	BUTTON_COLOR red = {"빨강", 255, 0,0};

	color_list.append(red);

	return color_list;
}

QList<Item*> DataManager::getItemListByCategory(uint category_id)
{
	QList<Item*> item_list_by_category;

	for(int i = 0 ; i < mItemList.size() ; i++)
	{
		Item *item = mItemList.at(i);

		if(item->getCategoryId() == category_id)
		{
			item_list_by_category.append(item);
		}
	}
	return item_list_by_category;
}

bool DataManager::insertCategory(Category *category)
{
    return true;
}

bool DataManager::insertItem(Item *item)
{
    QSqlQuery query(mDB);

    QString current_time;
    QString date = QDateTime::currentDateTime().date().toString("yyyy/MM/dd(ddd)");
    QString time = QDateTime::currentDateTime().time().toString("HH:mm:ss");
    current_time = date + " " + time;

//    query.prepare("SELECT * FROM item WHERE position_x=:position_x AND position_y=:position_y AND enable=1;");
//    query.bindValue(":position_x", mItem->getPositionX());
//    query.bindValue(":position_y", mItem->getPositionY());
//    query.exec();
//
//    int query_size;
//    if ((db).driver()->hasFeature(QSqlDriver::QuerySize))
//    {
//        query_size = query.size();
//    }
//    else
//    {
//        // this can be very slow
//        query.last();
//        query_size = query.at() + 1;
//    }

    // 동일한 위치의 아이템은 disable 시킨다.
    query.prepare("UPDATE item SET enable=0, delete_time=:delete_time WHERE position_x=:position_x AND position_y=:position_y AND enable=1;");
    query.bindValue(":delete_time", current_time);
    query.bindValue(":position_x", item->getPositionX());
    query.bindValue(":position_y", item->getPositionY());
    if(query.exec() == false)
    {
        qDebug("Error insertItem - fail to disable same position item");
        return false;
    }

    // 신규 아이템을 추가한다.
    query.prepare("INSERT INTO item (category_id, name, price, discount, print, print_together, position_x, position_y, create_time, enable) "
                   "VALUES (:category_id, :name, :price, :discount, :print, :print_together, :position_x, :position_y, :create_time, :enable)");
    query.bindValue(":category_id", item->getCategoryId());
    query.bindValue(":name", item->getName());
    query.bindValue(":price", item->getPrice());
    query.bindValue(":discount", item->supportDiscountItem());
    query.bindValue(":print", item->supportPrint());
    query.bindValue(":print_together", item->supportPrintTogether());
    query.bindValue(":position_x", item->getPositionX());
    query.bindValue(":position_y", item->getPositionY());
    query.bindValue(":create_time", current_time);
    query.bindValue(":enable", 1);

    if(query.exec() == false)
    {
        qDebug("Error insertItem - fail to insert new item");
    }

    return true;
}

bool DataManager::deleteItem(Item *item)
{
    QSqlQuery query(mDB);

    QString current_time;
    QString date = QDateTime::currentDateTime().date().toString("yyyy/MM/dd(ddd)");
    QString time = QDateTime::currentDateTime().time().toString("HH:mm:ss");
    current_time = date + " " + time;

//    query.prepare("SELECT * FROM item WHERE position_x=:position_x AND position_y=:position_y AND enable=1;");
//    query.bindValue(":position_x", mItem->getPositionX());
//    query.bindValue(":position_y", mItem->getPositionY());
//    query.exec();
//
//    int query_size;
//    if ((db).driver()->hasFeature(QSqlDriver::QuerySize))
//    {
//        query_size = query.size();
//    }
//    else
//    {
//        // this can be very slow
//        query.last();
//        query_size = query.at() + 1;
//    }

    query.prepare("UPDATE item SET enable=0, delete_time=:delete_time \
                    WHERE \
                    category_id=:category_id AND \
                    name=:name AND \
                    price=:price AND \
                    discount=:discount AND \
                    print=:print AND \
                    print_together=:print_together AND \
                    position_x=:position_x AND \
                    position_y=:position_y AND \
                    create_time=:create_time AND \
                    enable=:enable;");

    query.bindValue(":delete_time", current_time);
    query.bindValue(":category_id", item->getCategoryId());
    query.bindValue(":name", item->getName());
    query.bindValue(":price", item->getPrice());
    query.bindValue(":discount", item->supportDiscountItem());
    query.bindValue(":print", item->supportPrint());
    query.bindValue(":print_together", item->supportPrintTogether());
    query.bindValue(":position_x", item->getPositionX());
    query.bindValue(":position_y", item->getPositionY());
    query.bindValue(":create_time", current_time);
    query.bindValue(":enable", 1);

    if(query.exec() == false)
    {
           qDebug("Error delete item - fail to delete item");
        return false;
    }

    return false;
}
