#include "messages.h"
#include <cstdio>
#include <fstream>
#include <qdir.h>
extern struct _my_information my_information;
extern map<string, friend_information*> friend_detail;
extern map<QString, widget_*>widges_friend;
extern map<QString, widget_*>widges_stranger;
extern map<QString, widget_*>widges_balack;
extern map<QString, widget_*>group_message_;
extern map<QString, widget_*>system_message;
map<QString, widget_*>widges_friend_message;
map<QString, widget_*>widges_stranger_mesage;
map<QString, widget_*>widges_balack_message;
map<QString, widget_*>widges_group_message;
messages *messag;
messages::messages(QWidget *parent)
	: QWidget(parent)
{
	this->setFixedSize(283, 350);
	groupbox = new QGroupBox(this);
	friend_layout = new QVBoxLayout(groupbox);
	friend_layout->addStretch();
	messag = this;
}

messages::~messages()
{

}
//有错误name形参
void messages::handle_group_message(string time___ ,widget_ *wi, string name_, int type, string sender, string text, string imag, string image_name, string group_name)
{
	//忘了指针了*
	if (*(wi->chatisopen))
	{
		if (type == 2)
		{
			string in = "friend_sound/" + image_name;
			wi->chatt->set_sound_file(imag, image_name);
			wi->chatt->send_sound(time___, 1, QString::fromStdString(image_name), name_);
			return;
		}
		wi->chatt->set_messagefrom_friend(text, imag, image_name, name_);
		wi->chatt->show();
	}
	else {
		if ((widges_group_message.find(QString::fromStdString(group_name)) == widges_group_message.end()))
		{
			widget_ *wi = new widget_(0, 0, group_name);
			//出现错误不细心把group_name写成sender
			wi->chatt = group_message_.find(QString::fromStdString(group_name))->second->chatt;
			wi->pi = group_message_.find(QString::fromStdString(group_name))->second->pi;
			wi->name = group_message_.find(QString::fromStdString(group_name))->second->name;
			wi->get_image_and_text(wi->pi, QString::fromStdString(wi->name));
			wi->chatisopen = group_message_.find(QString::fromStdString(group_name))->second->chatisopen;
			widges_group_message[QString::fromStdString(group_name)] = wi;
			wi->lp = (group_message_.find(QString::fromStdString(group_name)))->second->lp;
			wi->set_is_group();
			friend_layout->insertWidget(0, wi);
		}
		else
		{
			auto at = widges_group_message.find(QString::fromStdString(group_name));
			at->second->lp = group_message_.find(QString::fromStdString(group_name))->second->lp;
		}
	}
}

//此函数作用在于定义一个widget其余交给chattext实现，通过sender找到widget,callback已经判断过是否chattext已经打开因此不需要再额外判断
void messages::message_text_image_com(string sender)
{
	if (isexitinwidgetofmessage(sender))
		return;
	auto iter = widges_friend.find(QString::fromStdString(sender));
	if (iter == widges_friend.end())
	{
		iter = widges_stranger.find(QString::fromStdString(sender));
		if (iter == widges_stranger.end())
		{
			iter == widges_balack.find(QString::fromStdString(sender));
			if (iter == widges_balack.end())
			{
				QMessageBox::critical(NULL, "数据异常", NULL);
			}
			else
			{
				if ((widges_balack_message.find(QString::fromStdString(sender)) == widges_friend_message.end()))
				{
					widget_ *wi = new widget_(0, 0, sender);
					wi->chatt = widges_balack.find(QString::fromStdString(sender))->second->chatt;
					wi->pi = widges_balack.find(QString::fromStdString(sender))->second->pi;
					wi->name = widges_balack.find(QString::fromStdString(sender))->second->name;
					wi->id__ = widges_balack.find(QString::fromStdString(sender))->second->id__;
					wi->get_image_and_text(wi->pi, QString::fromStdString(wi->name));
					wi->chatisopen = widges_balack.find(QString::fromStdString(sender))->second->chatisopen;
					widges_balack_message[QString::fromStdString(sender)] = wi;
					wi->lp.swap(widges_balack.find(QString::fromStdString(sender))->second->lp);
					friend_layout->insertWidget(0, wi);
				}
				else
				{
					auto at = widges_balack_message.find(QString::fromStdString(sender));
					//at->second->lp = widges_friend.find(QString::fromStdString(sender))->second->lp;
					at->second->lp.swap(widges_balack.find(QString::fromStdString(sender))->second->lp);
					at->second->setStyleSheet("QFrame{ background-color:red; border-radius:4px;padding:1px;}#hello{ border:1px solid blue }"
						"QFrame:hover{ background:yellow; }");
					friend_layout->insertWidget(0, at->second);
				}
			}
		}
		else
		{
			if ((widges_stranger_mesage.find(QString::fromStdString(sender)) == widges_friend_message.end()))
			{
				widget_ *wi = new widget_(0, 0, sender);
				wi->chatt = widges_stranger.find(QString::fromStdString(sender))->second->chatt;
				wi->pi = widges_stranger.find(QString::fromStdString(sender))->second->pi;
				wi->name = widges_stranger.find(QString::fromStdString(sender))->second->name;
				wi->id__ = widges_stranger.find(QString::fromStdString(sender))->second->id__;
				wi->get_image_and_text(wi->pi, QString::fromStdString(wi->name));
				wi->chatisopen = widges_stranger.find(QString::fromStdString(sender))->second->chatisopen;
				widges_stranger_mesage[QString::fromStdString(sender)] = wi;
				wi->lp.swap(widges_stranger.find(QString::fromStdString(sender))->second->lp);
				friend_layout->insertWidget(0, wi);
			}
			else
			{
				auto at = widges_stranger_mesage.find(QString::fromStdString(sender));
				//at->second->lp = widges_friend.find(QString::fromStdString(sender))->second->lp;
				at->second->lp.swap(widges_stranger.find(QString::fromStdString(sender))->second->lp);
				at->second->setStyleSheet("QFrame{ background-color:red; border-radius:4px;padding:1px;}#hello{ border:1px solid blue }"
					"QFrame:hover{ background:yellow; }");
				friend_layout->insertWidget(0, at->second);
			}
		}
	}
	else
	{
		if ((widges_friend_message.find(QString::fromStdString(sender)) == widges_friend_message.end()))
		{
			widget_ *wi = new widget_(0, 0, sender);
			wi->chatt = widges_friend.find(QString::fromStdString(sender))->second->chatt;
			wi->pi = widges_friend.find(QString::fromStdString(sender))->second->pi;
			wi->name = widges_friend.find(QString::fromStdString(sender))->second->name;
			wi->id__ = widges_friend.find(QString::fromStdString(sender))->second->id__;
			wi->get_image_and_text(wi->pi, QString::fromStdString(wi->name));
			wi->chatisopen = widges_friend.find(QString::fromStdString(sender))->second->chatisopen;
			wi->lp = (widges_friend.find(QString::fromStdString(sender)))->second->lp;
			widges_friend_message[QString::fromStdString(sender)] = wi;
			friend_layout->insertWidget(0, wi);
		}
		else
		{
			auto at = widges_friend_message.find(QString::fromStdString(sender));
			at->second->lp = widges_friend.find(QString::fromStdString(sender))->second->lp;
			//friend_layout->insertWidget(0, at->second);
		}
	}
}
bool messages::isexitinwidgetofmessage(const string keyName)
{
	return (message_come.find(keyName) != message_come.end());
}
void messages::insert_widget_handle(int type, string sender)
{
}