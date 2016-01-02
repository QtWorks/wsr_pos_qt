#include "ItemBUtton.h"
#include <QFont>
#include "StyleSheet.h"


ItemButton::ItemButton(QWidget *parent, Item *item) : QPushButton(parent), mItem(item)
{
	setFixedSize(WIDTH, HEIGHT);

	setText(mItem->getName() + "\n" + QLocale(QLocale::Korean).toString(mItem->getPrice()));

	QFont font;
	font.setFamily(QString("맑은 고딕"));
	font.setPointSize(12);
	setFont(font);

	setStyleSheet(ITEM_BUTTON_STYLE_SHEET_1(PETER_RIVER, PETER_RIVER_DARK));

	connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}

ItemButton::~ItemButton()
{

}

void ItemButton::onClicked()
{
	emit clicked(mItem);
}
