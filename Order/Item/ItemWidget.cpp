#include "ItemWidget.h"

ItemWidget::ItemWidget(QWidget* parent, QList<Item*> item_list) : QWidget(parent)
{
	mParent = parent;
	mItemList = item_list;
	mItemButtonList = new QList<ItemButton*>();

	for(int i = 0 ; i < mItemList.size() ; i++)
	{
		ItemButton *item_button = new ItemButton(this, mItemList.at(i));
		mItemButtonList->append(item_button);
		connect(item_button,SIGNAL(clicked(Item*)),this,SIGNAL(itemSelected(Item*)));
	}
}


ItemWidget::~ItemWidget()
{

}

void ItemWidget::setGeometry(int x, int y, int w, int h)
{
    QWidget::setGeometry(x, y, w, h);

    int item_gap_horizontal = ((w - (PADDING_HORIZONTAL * 2)) / ROW) - ITEM_BUTTON_WIDTH;
    int item_gap_vertical = ((h - (PADDING_VERTICAL * 2)) / COL) - ITEM_BUTTON_HEIGHT;

    for(int i = 0 ; i < mItemList.size() ; i++)
    {
        Item* item = mItemList.at(i);

        int button_x = PADDING_HORIZONTAL + ((ITEM_BUTTON_WIDTH + item_gap_horizontal) * (item->getPositionX() - 1));
        int button_y = PADDING_VERTICAL + ((ITEM_BUTTON_HEIGHT + item_gap_vertical) * (item->getPositionY() - 1));
        mItemButtonList->at(i)->setGeometry(button_x, button_y, ITEM_BUTTON_WIDTH, ITEM_BUTTON_HEIGHT);
        qDebug("%d %d, %d", i, button_x, button_y);
    }
}

void ItemWidget::paintEvent(QPaintEvent *)
{
	 QStyleOption opt;
	 opt.init(this);
	 QPainter p(this);
	 style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

