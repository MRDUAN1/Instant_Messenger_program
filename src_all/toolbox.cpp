#include "toolbox.h"
#include "qmainstackwidget.h"
#include <qmessagebox.h>
# pragma execution_character_set("utf-8")
extern protobuf_client *pro;
toolbox *too;
int first, second, third;
int login_first, login_second, login_third;
extern map<string, friend_information*> friend_detail;
extern struct _my_information my_information;
extern map<QString, widget_*>widges_friend;
extern map<QString, widget_*>widges_stranger;
extern map<QString, widget_*>widges_balack;
extern map<QString, widget_*>system_message;
extern map<QString, widget_*>group_message_;
toolbox::toolbox(QWidget *parent)
: QToolBox(parent)
{
	first = 0;
	second = 0;
	third = 0;
	too = this;
	this->setFixedSize(280, 350);
	this->setContentsMargins(0, 0, 0, 0);
	
	my_friend = new QGroupBox;
	my_friend->setStyleSheet("background-color:rgb(232, 245, 252)");
	/*my_friend->setStyleSheet("QGroupBox {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E0E0E0, stop: 1 #FFFFFF);border: 2px solid gray;border-radius: 5px;margin-top: 1ex;}"
		"QGroupBox::indicator {width: 13px;height: 13px; }"
		"QGroupBox::title {subcontrol-origin: margin; subcontrol-position: top center; padding: 0 3px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FF0ECE, stop: 1 #FFFFFF);}");*/

	stranger = new QGroupBox;
	stranger->setStyleSheet("background-color:rgb(232, 245, 252)");
	balacklist = new QGroupBox;
	balacklist->setStyleSheet("background-color:rgb(232, 245, 252)");
	group_ = new QGroupBox;
	group_->setStyleSheet("background-color:rgb(232, 245, 252)");
	_group = new QVBoxLayout(group_);
	friend_layout = new QVBoxLayout(my_friend);
	friend_layout->setContentsMargins(0, 0, 0, 0);
	friend_layout->setSpacing(0);
	stranger_layout = new QVBoxLayout(stranger);
	stranger_layout->setContentsMargins(0, 0, 0, 0);
	stranger_layout->setSpacing(0);
	balacklist_layout = new QVBoxLayout(balacklist);
	balacklist_layout->setContentsMargins(0, 0, 0, 0);
	balacklist_layout->setSpacing(0);
	friend_layout->addStretch();
	balacklist_layout->addStretch();
	stranger_layout->addStretch();
	_group->addStretch();
	_group->setContentsMargins(0, 0, 0, 0);
	_group->setSpacing(0);
	this->addItem((QWidget*)my_friend, tr("我的好友"));
	this->addItem((QWidget*)stranger, tr("陌生人"));
	this->addItem((QWidget*)balacklist, tr("黑名单"));
	this->addItem((QWidget*)group_, tr("群组"));
	this->setStyleSheet("QToolBox::tab {background:rgb(232, 245, 252);color: rgb(21, 127, 252);}"
		"QToolBox::tab:selected {font: italic;color: blue;}"
		"QToolBox{ border-width:1px; border-style:rgb(232, 245, 252); border-top-color:rgb(217, 223, 226); }");


}
void toolbox::add_widget(QPixmap _pix, QString _text, string id________, int palce ,string isonline)
{
	QPixmap pix = _pix;
	QString text = _text;
	widget_ *widge = new widget_(0, this, id________);
	widge->id__ = id________;
	if (palce == 0)
	{
		widge->posit = 0;
		
		widge->get_image_and_text(pix, text);
		if (strcmp(isonline.data(), "0"))
		{
			friend_layout->insertWidget(0, widge);
			first++;
		}
		else friend_layout->insertWidget(0, widge);
		widges_friend[QString::fromStdString(id________)] = widge;
		widge->set_isonline(isonline);
	}
	if (palce == 1)
	{
		//if (item1) delete item1;
		widge->posit = 1;
		widge->get_image_and_text(pix, text);
		if (strcmp(isonline.data(), "0"))
		{
			stranger_layout->insertWidget(0, widge);
		}
		else stranger_layout->insertWidget(0, widge);
		widges_stranger[QString::fromStdString(id________)] = widge;
		widge->set_isonline(isonline);
	}
	if (palce == 2)
	{
		widge->posit = 2;
		widge->get_image_and_text(pix, text);
		if (strcmp(isonline.data(), "0"))
		{
			balacklist_layout->insertWidget(0, widge);
		}
		else balacklist_layout->insertWidget(0, widge);
		widges_balack[QString::fromStdString(id________)] = widge;
		widge->set_isonline(isonline);
	}
	if (palce == 3)
	{
		widge->posit = 3;
		widge->get_image_and_text(pix, text);
		_group->insertWidget(0, widge);
		group_message_[text] = widge;
		widge->set_is_group();
	}
}
//1为登录0为登出
void toolbox::renovate_loin_exit(string id, int i)
{
	if (widges_friend.find(QString::fromStdString(id)) == widges_friend.end())
	{
		if (widges_balack.find(QString::fromStdString(id)) == widges_balack.end())
		{
			if (widges_stranger.find(QString::fromStdString(id)) == widges_stranger.end())
			{
				QMessageBox::warning(NULL, "改变登录位置失败", NULL);
			}
			else
			{
				widget_ *w = widges_stranger[QString::fromStdString(id)];
				if (i == 1)
					w->set_isonline("1");
				else if (i == 0)
					w->set_isonline("0");
			}
		}
		else
		{
			widget_ *w = widges_balack[QString::fromStdString(id)];
			if (i == 1)
				w->set_isonline("1");
			else if (i == 0)
				w->set_isonline("0");
		}
	}
	else
	{
		widget_ *w = widges_friend[QString::fromStdString(id)];
		if (i == 1)
			w->set_isonline("1"); //1在线
		else if (i == 0)
			w->set_isonline("0"); //0登出
	}
}
/*当h有值且不为0时,只是移动,当h无值时是删除*/
void toolbox::remove_widget(int i, QWidget *wid, int h)
{
	//QMessageBox::warning(NULL, "JFHGJF", "DHGHGHD");
	switch (i){
		friend_layout->removeWidget(wid);
		if (!h)
		{
			wid->deleteLater();
			widget_ *wid__ = (widget_*)wid;
			QString str = QString::fromStdString(wid__->id__);
			widges_friend[str] = wid__;
			widges_friend.erase(str);
			pro->change_(str.toStdString(), 1);
			return;
		}
		break;
	case 1:
		stranger_layout->removeWidget(wid);
		if (!h)
		{
			wid->deleteLater();
			widget_ *wid__ = (widget_*)wid;
			QString str = QString::fromStdString(wid__->id__);
			widges_stranger[str] = wid__;
			widges_stranger.erase(str);
			pro->change_(str.toStdString(), 1);
			return;
		}
		break;
	case 2:
		balacklist_layout->removeWidget(wid);
		if (!h)
		{
			wid->deleteLater();
			widget_ *wid__ = (widget_*)wid;
			QString str = QString::fromStdString(wid__->id__);
			widges_balack[str] = wid__;
			widges_balack.erase(str);
			pro->change_(str.toStdString(), 1);
			return ;
		}
		break;
	case 3:
		_group->removeWidget(wid);
		wid->deleteLater();
		widget_ *wid__ = (widget_*)wid;
		QString str = QString::fromStdString(wid__->id__);
		group_message_[str] = wid__;
		group_message_.erase(str);
		return;
	}
}
void toolbox::move_widget(int i, int j, QWidget*wid)
{
	remove_widget(i, wid, 1);
	switch (j)
	{
	case 0:
	{
			  friend_layout->insertWidget(0, wid);
			  widget_ *wid__ = (widget_*)wid;
			  QString str = QString::fromStdString(wid__->id__);
			  widges_friend[str] = wid__;
			  string t = str.toStdString();
			  pro->move_group(t, j);
			  break;
	}
	case 1:
	{
			  stranger_layout->insertWidget(0, wid);
			  widget_ *wid__ = (widget_*)wid;
			  QString str = QString::fromStdString(wid__->id__);
			  widges_stranger[str] = wid__;
			  string t = str.toStdString();
			  pro->move_group(t, j);
			  break;
	}
	case 2:
	{
			  balacklist_layout->insertWidget(0, wid);
			  widget_ *wid__ = (widget_*)wid;
			  QString str = QString::fromStdString(wid__->id__);
			  widges_balack[str] = wid__;
			  string t = str.toStdString();
			  pro->move_group(t, j);
			  break;
	}
	}
}
