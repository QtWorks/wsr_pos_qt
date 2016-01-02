#include "SettingItemWidget.h"

SettingItemWidget::SettingItemWidget(QWidget* parent, QList<Item*> item_list) : QWidget(parent)
{
	mParent = parent;
	mItemList = item_list;
    mSettingItemButtonList = new QList<SettingItemButton*>();

    for(unsigned int i = 0 ; i < COL ; i++)
    {
        for(unsigned int j = 0 ; j < ROW ; j++)
        {
            Item* item = NULL;
            SettingItemButton *item_button;

            for(int k = 0 ; k < mItemList.size() ; k++)
            {
                if(mItemList.at(k)->getPositionY() == (i + 1) && mItemList.at(k)->getPositionX() == (j + 1))
                {
                    item = mItemList.at(k);
                    break;
                }
            }

            if(item != NULL)
            {
                item_button = new SettingItemButton(this, item);
            }
            else
            {
				Item* temp_item = new Item();
				temp_item->setPositionX(j + 1);
				temp_item->setPositionY(i + 1);
				item_button = new SettingItemButton(this, temp_item);
            }

            mSettingItemButtonList->append(item_button);
			connect(item_button, SIGNAL(clicked(Item*)), this, SIGNAL(itemSelected(Item*)));
			connect(this, SIGNAL(itemSelected(Item*)), item_button, SLOT(checkClicked(Item*)));
        }
	}
}


SettingItemWidget::~SettingItemWidget()
{

}

void SettingItemWidget::setGeometry(int x, int y, int w, int h)
{
    QWidget::setGeometry(x, y, w, h);

    int item_gap_horizontal = ((w - (PADDING_HORIZONTAL * 2)) / ROW) - ITEM_BUTTON_WIDTH;
    int item_gap_vertical = ((h - (PADDING_VERTICAL * 2)) / COL) - ITEM_BUTTON_HEIGHT;

    for(int i = 0 ; i < COL ; i++)
    {
        for(int j = 0 ; j < ROW ; j++)
        {
            int button_x = PADDING_HORIZONTAL + ((ITEM_BUTTON_WIDTH + item_gap_horizontal) * j);
            int button_y = PADDING_VERTICAL + ((ITEM_BUTTON_HEIGHT + item_gap_vertical) * i);
            mSettingItemButtonList->at(j + (i * ROW))->setGeometry(button_x, button_y, ITEM_BUTTON_WIDTH, ITEM_BUTTON_HEIGHT);
            qDebug("%d %d, %d", (j + (i * ROW)), button_x, button_y);
        }
    }
}

void SettingItemWidget::paintEvent(QPaintEvent *)
{
	 QStyleOption opt;
	 opt.init(this);
	 QPainter p(this);
	 style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SettingItemWidget::refresh(QList<Item*> item_list)
{
	mItemList = item_list;

	for(unsigned int i = 0 ; i < COL ; i++)
	{
		for(unsigned int j = 0 ; j < ROW ; j++)
		{
			Item* item = NULL;
			SettingItemButton *item_button = mSettingItemButtonList->at((i * j) + j);

			for(int k = 0 ; k < mItemList.size() ; k++)
			{
				if(mItemList.at(k)->getPositionY() == (i + 1) && mItemList.at(k)->getPositionX() == (j + 1))
				{
					item = mItemList.at(k);
					break;
				}
			}

			item_button->refresh(item);
		}
	}
}
