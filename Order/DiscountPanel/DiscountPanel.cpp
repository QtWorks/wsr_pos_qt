#include "DiscountPanel.h"

DiscountPanel::DiscountPanel(QWidget *parent, TYPE type) : QDialog(parent), mType(type), mTabType(TabButton::PRICE), mValue(0)
{
	setModal(true);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	mLabelTitle = new QLabel(this);
	mTabView = new TabView(this);
	mLabelValue = new QLabel(this);
	mNumPad = new NumPad(this);

	setStyle();

	switch(mType)
	{
		case DISCOUNT:
		{
			mLabelTitle->setText("할  인");
			mLabelTitle->setGeometry(0, 0, 450, 40);
			mTabView->setGeometry(0, 40, 450, 50);
			mLabelValue->setGeometry(50, 90, 350, 100);
			mNumPad->setGeometry(0, 190, 450, 400);
			setGeometry(100, 100, 450, 590);
			break;
		}
		case DEPOSIT:
		{
			mLabelTitle->setText("선  금");
			mLabelTitle->setGeometry(0, 0, 450, 40);
			mTabView->hide();
			mLabelValue->setGeometry(50, 40, 350, 100);
			mNumPad->setGeometry(0, 140, 450, 400);
			setGeometry(100, 100, 450, 540);
			break;
		}
		case ENURI:
		{
			mLabelTitle->setText("에 누 리");
			mLabelTitle->setGeometry(0, 0, 450, 40);
			mTabView->hide();
			mLabelValue->setGeometry(30, 40, 350, 100);
			mNumPad->setGeometry(0, 140, 450, 400);
			setGeometry(100, 100, 450, 540);
			break;
		}
	}

	mLabelValue->setText(QString("￦ ") + QLocale(QLocale::Korean).toString(mValue));

	connect(mTabView, SIGNAL(click(TabButton::TYPE)), this, SLOT(onTabTypeChanged(TabButton::TYPE)));
	connect(mNumPad, SIGNAL(clicked(NUM_BUTTON)), this, SLOT(onNumButtonPressed(NUM_BUTTON)));
}

void DiscountPanel::setStyle()
{
	mLabelTitle->setStyleSheet("background-color:#"BLUE_800";color:#"WHITE";qproperty-alignment:'AlignCenter';");
	mLabelTitle->setFont(QFont("맑은 고딕", 15, QFont::Bold));

	mLabelValue->setStyleSheet("background-color:black;color:white;qproperty-alignment:'AlignRight|AlignCenter';");
	mLabelValue->setFont(QFont("맑은 고딕", 40));

	setStyleSheet("background-color:black;color:white;");
}

void DiscountPanel::onTabTypeChanged(TabButton::TYPE type)
{
	mTabType = type;
	onNumButtonPressed(BUTTON_CLEAR);
}

void DiscountPanel::onNumButtonPressed(NUM_BUTTON num_button)
{
	uint temp_value = mValue;

	switch(num_button)
	{
		case BUTTON_1:
		{
			temp_value = temp_value * 10 + 1;
			break;
		}
		case BUTTON_2:
		{
			temp_value = temp_value * 10 + 2;
			break;
		}
		case BUTTON_3:
		{
			temp_value = temp_value * 10 + 3;
			break;
		}
		case BUTTON_4:
		{
			temp_value = temp_value * 10 + 4;
			break;
		}
		case BUTTON_5:
		{
			temp_value = temp_value * 10 + 5;
			break;
		}
		case BUTTON_6:
		{
			temp_value = temp_value * 10 + 6;
			break;
		}
		case BUTTON_7:
		{
			temp_value = temp_value * 10 + 7;
			break;
		}
		case BUTTON_8:
		{
			temp_value = temp_value * 10 + 8;
			break;
		}
		case BUTTON_9:
		{
			temp_value = temp_value * 10 + 9;
			break;
		}
		case BUTTON_0:
		{
			temp_value = temp_value * 10;
			break;
		}
		case BUTTON_00:
		{
			temp_value = temp_value * 100;
			break;
		}
		case BUTTON_CLEAR:
		{
			temp_value = 0;
			break;
		}
		case BUTTON_OK:
		{
			if(mType == DISCOUNT)
			{
				emit discount(mTabType, mValue);
			}
			else
			{
				emit discount(mValue);
			}
		}
		case BUTTON_CANCEL:
		{
			close();
			break;
		}
	}

	if(mTabType == TabButton::PRICE)
	{
		if(temp_value <= 1000000000)
		{
			mValue = temp_value;
			mLabelValue->setText(QString("￦ ") + QLocale(QLocale::Korean).toString(mValue));
		}
	}
	else if(mTabType == TabButton::PERCENT)
	{
		if(temp_value <= 100)
		{
			mValue = temp_value;
			mLabelValue->setText(QString::number(mValue) + QString(" %"));
		}
	}
}
