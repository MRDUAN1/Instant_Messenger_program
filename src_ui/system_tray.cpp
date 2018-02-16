#include "system_tray.h"
#include "qq_main.h"
#include "qmainstackwidget.h"
#include <qicon.h>
#include <qsystemtrayicon.h>
#include <qmenu.h>
extern qq_main *me;
extern qmainstackwidget *qmainwidget;
system_tray::system_tray(QWidget *parent)
	: QWidget(parent)
{
	is_login = false;
	QIcon icon = QIcon("./friend_head/gray_qq.png");
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(icon);
	trayIcon->setToolTip(tr("qq"));
	QString titlec = tr("qq");
	QString textc = tr("qq");
	trayIcon->show();
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
	minimizeAction = new QAction(tr("最小化 (&I)"), this);
	connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide_()));
	restoreAction = new QAction(tr("还原 (&R)"), this);
	connect(restoreAction, SIGNAL(triggered()), this, SLOT(show_normal()));
	quitAction = new QAction(tr("退出 (&Q)"), this);
	open_ = new QAction(tr("打开主面板 (&)"), this);
	connect(open_, SIGNAL(triggered()), this, SLOT(show_normal()));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(quit_()));
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(minimizeAction);
	trayIconMenu->addAction(restoreAction);
	trayIconMenu->addAction(open_);

	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);
	trayIcon->setContextMenu(trayIconMenu);
}

system_tray::~system_tray()
{

}
void system_tray::login_success()
{
	is_login = true;
	QIcon icon("./friend_head/qq.png");
	trayIcon->setIcon(icon);
}
void system_tray::exit_success()
{
	is_login = false;
	QIcon icon("./friend_head/gray_qq.png");
	trayIcon->setIcon(icon);
}
void system_tray::trayiconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
		
	case QSystemTrayIcon::DoubleClick:
		//双击托盘图标
		this->showNormal();
		this->raise();
		break;
	default:
		break;
	}
}
void system_tray::show_normal()
{
	if (is_login)
		qmainwidget->showNormal();
	else me->showNormal();
}
void system_tray::quit_()
{
	exit(0);
}
void system_tray::hide_()
{
	if (is_login)
		qmainwidget->showMinimized();
	else me->showMinimized();
}