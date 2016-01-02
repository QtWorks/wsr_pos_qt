#include "ConfigureButton.h"

#define WIDTH	160
#define HEIGHT	65

ConfigureButton::ConfigureButton(QWidget *parent) : QPushButton(parent)
{
	setFixedSize(WIDTH, HEIGHT);

	QFont font;
	font.setFamily(QString("맑은 고딕"));
	font.setPointSize(12);
	setFont(font);
}

ConfigureButton::~ConfigureButton()
{

}
