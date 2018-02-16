#ifndef MENU_ADD_H
#define MENU_ADD_H

#include <QLabel>
#include <qmenu.h>
#include <qaction.h>
#include <qpushbutton.h>

class menu_add : public QPushButton
{
	Q_OBJECT

public:
	menu_add(QWidget *parent);
	~menu_add();
public slots:
void set_menu();
void leave_triggered();
void online_triggered();
void steathy_triggered();

private:
	QAction *leave;
	QAction *online;
	QAction *steathy;
	
};

#endif // MENU_ADD_H
