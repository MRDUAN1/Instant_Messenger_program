#include "menu_add.h"
# pragma execution_character_set("utf-8")
extern int status;
//extern map<string, friend_information*> friend_detail;
menu_add::menu_add(QWidget *parent)
	: QPushButton(parent)
{
	QObject::connect(this, SIGNAL(clicked()), this, SLOT(set_menu()));
	QPixmap pix;
	pix.load("./image/9.png");
	this->resize(10, 10);
	pix = pix.scaled(10, 10);
	this->setIcon(pix);
	leave = new QAction(this);
	leave->setText("离开");
	online = new QAction(this);
	online->setText("在线");
	steathy = new QAction(this);
	steathy->setText("隐身");
	connect(leave, SIGNAL(triggered()), this, SLOT(leave_triggered()));
	connect(online, SIGNAL(trggered()), this, SLOT(online_triggered()));
	connect(steathy, SIGNAL(triggered()), this, SLOT(steathy_triggered()));
}
void menu_add::leave_triggered()
{
	status = 2;
}
void menu_add::online_triggered()
{
	status = 0;
}
menu_add::~menu_add()
{

}
void menu_add::steathy_triggered()
{
	status = 1;
}
void menu_add::set_menu()
{
	QMenu *menu = new QMenu;
	menu->setStyleSheet("QMenu {background-color: white;padding: 1px;}"
		"QMenu::item{background-color:transparent;}"
		"QMenu::item:selected{background-color:rgb(234, 243, 253);color:black;}");
	
	menu->addAction(online);
	menu->addSeparator();
	menu->addAction(steathy);
	menu->addSeparator();
	menu->addAction(leave);
	menu->exec(QCursor::pos());
}
