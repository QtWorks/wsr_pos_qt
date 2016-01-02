#ifndef NUMBUTTON_H
#define NUMBUTTON_H

#include <QPushButton>

typedef enum
{
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
	BUTTON_7,
	BUTTON_8,
	BUTTON_9,
	BUTTON_0,
	BUTTON_00,
	BUTTON_CLEAR,
	BUTTON_CANCEL,
	BUTTON_OK,
} NUM_BUTTON;

class NumButton : public QPushButton
{
		Q_OBJECT
	private:
		NUM_BUTTON mNumButton;

	public:
		explicit NumButton(QWidget *parent = 0, NUM_BUTTON num_button = BUTTON_0);
	signals:
		void clicked(NUM_BUTTON num_button);
	public slots:
		void onClicked();

};

#endif // NUMBUTTON_H
