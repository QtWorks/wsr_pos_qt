#include "TabButton.h"

TabButton::TabButton(QWidget *parent, QString name, TYPE type) : QPushButton(parent)
{
	mType = type;
	mLabelText = new QLabel(name, this);
	mLabelSelection = new QLabel(this);

	QFont font("맑은 고딕", 14, QFont::Bold);
	mLabelText->setFont(font);

	setNormal();
	connect(this, SIGNAL(clicked()), this, SLOT(onClick()));
}

void TabButton::setNormal()
{
	mLabelText->setStyleSheet("background-color: #"BLUE_600";color:#"BLUE_200";qproperty-alignment: AlignCenter;");
	mLabelSelection->setStyleSheet("background-color: #"BLUE_200";color:#"BLUE_200";");
}

void TabButton::setSelect()
{
	mLabelText->setStyleSheet("background-color: #"BLUE_600";color:#"WHITE";qproperty-alignment: AlignCenter;");
	mLabelSelection->setStyleSheet("background-color: #"WHITE";color:#"WHITE";");
}

void TabButton::onClick()
{
	emit click(mType);
}

void TabButton::setGeometry(int x, int y, int w, int h)
{
	QPushButton::setGeometry(x, y, w, h);

	mLabelText->setGeometry(0, 0, w, h - 5);
	mLabelSelection->setGeometry(0, h - 5, w, 5);
}
