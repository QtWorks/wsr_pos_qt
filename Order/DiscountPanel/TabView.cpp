#include "TabView.h"

TabView::TabView(QWidget* parent) : QWidget(parent)
{
	mButtonPrice= new TabButton(this, "가격", TabButton::PRICE);
	mButtonPercent = new TabButton(this, "퍼센트", TabButton::PERCENT);
	mButtonCustom = new TabButton(this, "기타", TabButton::CUSTOM);

	select(TabButton::PRICE);

	connect(mButtonPrice, SIGNAL(click(TabButton::TYPE)), this, SLOT(onClick(TabButton::TYPE)));
	connect(mButtonPercent, SIGNAL(click(TabButton::TYPE)), this, SLOT(onClick(TabButton::TYPE)));
	connect(mButtonCustom, SIGNAL(click(TabButton::TYPE)), this, SLOT(onClick(TabButton::TYPE)));
}

void TabView::onClick(TabButton::TYPE tab_type)
{
	select(tab_type);

	emit click(tab_type);
}

void TabView::select(TabButton::TYPE tab_type)
{
	mButtonPrice->setNormal();
	mButtonPercent->setNormal();
	mButtonCustom->setNormal();

	switch(tab_type)
	{
		case TabButton::PRICE:
			mButtonPrice->setSelect();
			break;
		case TabButton::PERCENT:
			mButtonPercent->setSelect();
			break;
		case TabButton::CUSTOM:
			mButtonCustom->setSelect();
			break;
	}
}

void TabView::setGeometry(int x, int y, int w, int h)
{
	QWidget::setGeometry(x, y, w, h);

	uint w1 = w / 3;
	uint w2 = w / 3;
	uint w3 = w - w1 - w2;

	mButtonPrice->setGeometry(0, 0, w1, h);
	mButtonPercent->setGeometry(w1, 0, w2, h);
	mButtonCustom->setGeometry(w1 + w2, 0, w3, h);
}
