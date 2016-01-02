#ifndef NUMPAD_H
#define NUMPAD_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include "NumButton.h"

class NumPad : public QWidget
{
	Q_OBJECT
private:
	NumButton *mNumButton1;
	NumButton *mNumButton2;
	NumButton *mNumButton3;
	NumButton *mNumButton4;
	NumButton *mNumButton5;
	NumButton *mNumButton6;
	NumButton *mNumButton7;
	NumButton *mNumButton8;
	NumButton *mNumButton9;
	NumButton *mNumButton0;
	NumButton *mNumButton00;
	NumButton *mNumButtonClear;
	NumButton *mNumButtonCancel;
	NumButton *mNumButtonOK;

public:
	NumPad(QWidget *parent = 0);
	void setGeometry(int x, int y, int w, int h);
signals:
	void clicked(NUM_BUTTON num_button);


};

#endif // NUMPAD_H
