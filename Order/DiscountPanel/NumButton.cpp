#include "NumButton.h"
#include "StyleSheet.h"

NumButton::NumButton(QWidget *parent, NUM_BUTTON num_button) :
	QPushButton(parent)
{
	mNumButton = num_button;

	switch(mNumButton)
	{
		case BUTTON_1:
		{
			setText(QString("1"));
			break;
		}
		case BUTTON_2:
		{
			setText(QString("2"));
			break;
		}
		case BUTTON_3:
		{
			setText(QString("3"));
			break;
		}
		case BUTTON_4:
		{
			setText(QString("4"));
			break;
		}
		case BUTTON_5:
		{
			setText(QString("5"));
			break;
		}
		case BUTTON_6:
		{
			setText(QString("6"));
			break;
		}
		case BUTTON_7:
		{
			setText(QString("7"));
			break;
		}
		case BUTTON_8:
		{
			setText(QString("8"));
			break;
		}
		case BUTTON_9:
		{
			setText(QString("9"));
			break;
		}
		case BUTTON_0:
		{
			setText(QString("0"));
			break;
		}
		case BUTTON_00:
		{
			setText(QString("00"));
			break;
		}
		case BUTTON_CLEAR:
		{
			setText(QString("삭제"));
			break;
		}
		case BUTTON_CANCEL:
		{
			setText(QString("취소"));
			break;
		}
		case BUTTON_OK:
		{
			setText(QString("확인"));
			break;
		}
	}

	QFont font;
	font.setFamily(QString("맑은 고딕"));
	font.setPointSize(25);
	setFont(font);

	//setStyleSheet("background-color:#"GREY_800";color:#"GREY_200";qproperty-alignment:'AlignCenter';");
	setStyleSheet(ITEM_BUTTON_STYLE_SHEET_10(GREY_800, GREY_600, GREY_700, GREY_200));
	connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}

void NumButton::onClicked()
{
	emit clicked(mNumButton);
}
