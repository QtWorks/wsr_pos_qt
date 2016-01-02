#-------------------------------------------------
#
# Project created by QtCreator 2014-10-31T09:25:44
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = POS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DataManager/Category.cpp \
    DataManager/DataManager.cpp \
    DataManager/Item.cpp \
    DataManager/OrderItem.cpp \
    Order/DiscountPanel/DiscountPanel.cpp \
    Order/DiscountPanel/NumButton.cpp \
    Order/DiscountPanel/NumPad.cpp \
    Order/DiscountPanel/TabButton.cpp \
    Order/DiscountPanel/TabView.cpp \
    Order/Item/ItemButton.cpp \
    Order/Item/ItemWidget.cpp \
    Order/OrderItem/OrderItemButton.cpp \
    Order/OrderItem/OrderItemWidget.cpp \
	Order/TotalWidget/TotalWidget.cpp \
    Setting/settingwidget.cpp \
    Setting/Item/SettingItemButton.cpp \
    Setting/Item/SettingItemWidget.cpp \
    Setting/Configure/SettingConfigureItemWidget.cpp \
    Setting/Configure/TreeComboBox.cpp \
    Setting/Configure/ConfigureButton.cpp \
    print/printer.cpp

HEADERS  += mainwindow.h \
	DataManager/Category.h \
    DataManager/DataManager.h \
    DataManager/Item.h \
    DataManager/OrderItem.h \
    Order/DiscountPanel/DiscountPanel.h \
    Order/DiscountPanel/NumButton.h \
    Order/DiscountPanel/NumPad.h \
    Order/DiscountPanel/TabButton.h \
    Order/DiscountPanel/TabView.h \
    Order/Item/ItemButton.h \
    Order/Item/ItemWidget.h \
    Order/OrderItem/OrderItemButton.h \
    Order/OrderItem/OrderItemWidget.h \
	Order/TotalWidget/TotalWidget.h \
    StyleSheet.h \
    Setting/settingwidget.h \
    Setting/Item/Settingitembutton.h \
    Setting/Item/SettingItemWidget.h \
    Setting/Configure/SettingConfigureItemWidget.h \
    Setting/Configure/TreeComboBox.h \
    Setting/Configure/ConfigureButton.h \
    print/printer.h

FORMS    += mainwindow.ui
