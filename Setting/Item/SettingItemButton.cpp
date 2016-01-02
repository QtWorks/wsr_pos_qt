#include "SettingItemButton.h"
#include <QFont>
#include "StyleSheet.h"
#include <QDateTime>

#define WIDTH	100
#define HEIGHT	100

#define LABEL_NAME_W	100
#define LABEL_NAME_H	30
#define LABEL_NAME_X	((WIDTH - LABEL_NAME_W) / 2)
#define LABEL_NAME_Y	(((WIDTH / 2 ) - LABEL_NAME_H) / 2)

#define LABEL_PRICE_W	LABEL_NAME_W
#define LABEL_PRICE_H	LABEL_NAME_H
#define LABEL_PRICE_X	LABEL_NAME_X
#define LABEL_PRICE_Y	LABEL_NAME_Y + LABEL_NAME_H

SettingItemButton::SettingItemButton(QWidget *parent, Item *item) : QPushButton(parent), mItem(item)
{
	setFixedSize(WIDTH, HEIGHT);

	if(mItem->getName().isEmpty() == true)
	{
		setText("없음");
		setStyleSheet(ITEM_BUTTON_STYLE_SHEET_1(GREY_500, GREY_700));
	}
	else
	{
		setText(mItem->getName() + "\n" + QLocale(QLocale::Korean).toString(mItem->getPrice()));
		setStyleSheet(ITEM_BUTTON_STYLE_SHEET_1(PETER_RIVER, PETER_RIVER_DARK));
	}

	QFont font;
	font.setFamily(QString("맑은 고딕"));
	font.setPointSize(12);
	setFont(font);

	connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}

SettingItemButton::~SettingItemButton()
{

}

void SettingItemButton::refresh(Item *item)
{
	if(mItem->getName().isEmpty() == true)
	{
		setText("없음");
		setStyleSheet(ITEM_BUTTON_STYLE_SHEET_1(GREY_500, GREY_700));
	}
	else
	{
		setText(mItem->getName() + "\n" + QLocale(QLocale::Korean).toString(mItem->getPrice()));
		setStyleSheet(ITEM_BUTTON_STYLE_SHEET_1(PETER_RIVER, PETER_RIVER_DARK));
	}
}

void SettingItemButton::onClicked()
{
#if 0
	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName( "D:\\jenire\\pos.db3");

	QString current_time;
	QString date = QDateTime::currentDateTime().date().toString("yyyy/MM/dd(ddd)");
	QString time = QDateTime::currentDateTime().time().toString("HH:mm:ss");
	current_time = date + " " + time;

	if (db.open())
	{
		QSqlQuery query(db);

		query.prepare("SELECT * FROM item WHERE position_x=:position_x AND position_y=:position_y AND enable=1;");
		query.bindValue(":position_x", mItem->getPositionX());
		query.bindValue(":position_y", mItem->getPositionY());
		query.exec();

		int query_size;
		if ((db).driver()->hasFeature(QSqlDriver::QuerySize))
		{
			query_size = query.size();
		}
		else
		{
			// this can be very slow
			query.last();
			query_size = query.at() + 1;
		}

		if(query_size > 0)
		{
			query.prepare("UPDATE item SET enable=0, delete_time=:delete_time WHERE position_x=:position_x AND position_y=:position_y AND enable=1;");
			query.bindValue(":delete_time", current_time);
			query.bindValue(":position_x", mItem->getPositionX());
			query.bindValue(":position_y", mItem->getPositionY());
			query.exec();
		}

		query.prepare("INSERT INTO item (category_id, name, price, discount, print, print_together, position_x, position_y, create_time, enable) "
					  "VALUES (:category_id, :name, :price, :discount, :print, :print_together, :position_x, :position_y, :create_time, :enable)");
		query.bindValue(":category_id", mItem->getCategoryId());
		query.bindValue(":name", mItem->getName());
		query.bindValue(":price", mItem->getPrice());
		query.bindValue(":discount", mItem->supportDiscountItem());
		query.bindValue(":print", mItem->supportPrint());
		query.bindValue(":print_together", mItem->supportPrintTogether());
		query.bindValue(":position_x", mItem->getPositionX());
		query.bindValue(":position_y", mItem->getPositionY());
		query.bindValue(":create_time", current_time);
		query.bindValue(":enable", 1);
		query.exec();
	}

	db.close();
#endif
	emit clicked(mItem);
}

void SettingItemButton::checkClicked(Item *item)
{
	if(mItem == item)
	{
		setStyleSheet(ITEM_BUTTON_STYLE_SHEET_1(SUN_FLOWER, SUN_FLOWER_DARK));
	}
	else
	{
		if(mItem->getName().isEmpty() == true)
		{
			setStyleSheet(ITEM_BUTTON_STYLE_SHEET_1(GREY_500, GREY_700));
		}
		else
		{
			setStyleSheet(ITEM_BUTTON_STYLE_SHEET_1(PETER_RIVER, PETER_RIVER_DARK));
		}
	}
}
