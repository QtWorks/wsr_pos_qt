#include "NumPad.h"

#define BUTTON_WIDTH	100
#define BUTTON_HEIGHT	100
#define BUTTON_GAP		10

NumPad::NumPad(QWidget *parent) : QWidget(parent)
{
		mNumButton1 = new NumButton(this, BUTTON_1);
		connect(mNumButton1, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButton2 = new NumButton(this, BUTTON_2);
		connect(mNumButton2, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButton3 = new NumButton(this, BUTTON_3);
		connect(mNumButton3, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButton4 = new NumButton(this, BUTTON_4);
		connect(mNumButton4, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButton5 = new NumButton(this, BUTTON_5);
		connect(mNumButton5, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButton6 = new NumButton(this, BUTTON_6);
		connect(mNumButton6, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButton7 = new NumButton(this, BUTTON_7);
		connect(mNumButton7, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButton8 = new NumButton(this, BUTTON_8);
		connect(mNumButton8, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButton9 = new NumButton(this, BUTTON_9);
		connect(mNumButton9, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButton0 = new NumButton(this, BUTTON_0);
		connect(mNumButton0, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButton00 = new NumButton(this, BUTTON_00);
		connect(mNumButton00, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButtonClear = new NumButton(this, BUTTON_CLEAR);
		connect(mNumButtonClear, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButtonCancel = new NumButton(this, BUTTON_CANCEL);
		connect(mNumButtonCancel, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));

		mNumButtonOK = new NumButton(this, BUTTON_OK);
		connect(mNumButtonOK, SIGNAL(clicked(NUM_BUTTON)), this, SIGNAL(clicked(NUM_BUTTON)));
}

void NumPad::setGeometry(int x, int y, int w, int h)
{
	uint width_normal = w / 5;
	uint width_last = w - width_normal * 4;

	uint height_normal = h / 4;
	uint height_last = h - height_normal * 3;

	mNumButton1->setGeometry(width_normal * 0, height_normal * 0, width_normal * 1, height_normal * 1);
	mNumButton2->setGeometry(width_normal * 1, height_normal * 0, width_normal * 1, height_normal * 1);
	mNumButton3->setGeometry(width_normal * 2, height_normal * 0, width_normal * 1, height_normal * 1);
	mNumButton4->setGeometry(width_normal * 0, height_normal * 1, width_normal * 1, height_normal * 1);
	mNumButton5->setGeometry(width_normal * 1, height_normal * 1, width_normal * 1, height_normal * 1);
	mNumButton6->setGeometry(width_normal * 2, height_normal * 1, width_normal * 1, height_normal * 1);
	mNumButton7->setGeometry(width_normal * 0, height_normal * 2, width_normal * 1, height_normal * 1);
	mNumButton8->setGeometry(width_normal * 1, height_normal * 2, width_normal * 1, height_normal * 1);
	mNumButton9->setGeometry(width_normal * 2, height_normal * 2, width_normal * 1, height_normal * 1);
	mNumButton0->setGeometry(width_normal * 0, height_normal * 3, width_normal * 1, height_last * 1);
	mNumButton00->setGeometry(width_normal * 1, height_normal * 3, width_normal * 2, height_last * 1);
	mNumButtonClear->setGeometry(width_normal * 3, height_normal * 0, width_normal + width_last, height_normal * 1);
	mNumButtonCancel->setGeometry(width_normal * 3, height_normal * 1, width_normal + width_last, height_normal * 1);
	mNumButtonOK->setGeometry(width_normal * 3, height_normal * 2, width_normal + width_last, height_normal + height_last);

	QWidget::setGeometry(x, y, w, h);
}
