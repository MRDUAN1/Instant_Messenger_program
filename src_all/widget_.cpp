#include "widget_.h"
#include "look_all_friend.h"
#include <qmessagebox.h>
#include <qdir.h>
#include "protobuf_callback.h"
extern protobuf_client *pro;
extern map<string, friend_information*> friend_detail;
extern struct _my_information my_information;
//extern map<chattext*, widget_*>chat_with_widget;
extern map<string, chattext*>chat_with;
extern map<QString, widget_*>widges_friend;
extern map<QString, widget_*>widges_stranger;
extern map<QString, widget_*>widges_balack;
extern map<QString, widget_*>system_message;
widget_::widget_(int posi, QFrame *parent, string id) : QFrame(parent)
{
	QDir *temp1 = new QDir;
	bool exist = temp1->exists("friend_message_image");
	if (!exist)
		bool ok = temp1->mkdir("friend_message_image");
	bool exist1 = temp1->exists("chat_record");
	if (!exist1)
		bool ok1 = temp1->mkdir("chat_record");
	
	posit = posi;
	id__ = id;
	mymaxim_text = new QLabel(this);
	if_group = false;
	look_information = new QAction(this);
	tool = (toolbox*)parent;
	chatisopen = new bool;
	*chatisopen = false;
	menu = new QMenu(this);
	sendtext = new QAction(this);
	detail_information = new QAction(this);
	delete_name = new QAction(this);
	move = new QAction(this);
	move_balack = new QAction(this);
	move_friend = new QAction(this);
	
	move_stranger = new QAction(this);
	this->setObjectName("hello");
	this->setFixedSize(275, 50);
	this->setStyleSheet("QFrame{background-color:rgb(232,245,252); }"
		"QFrame:hover{ background-color:rgb(253,235,167); }");
	chatt = new chattext(id__, client__, this);
	//chatt->set_file_record(chat_record_file);
}
void widget_::enterEvent(QEvent * event)
{
	label_text->setStyleSheet("background-color:rgb(253, 235, 167)");
	mymaxim_text->setStyleSheet("background-color:rgb(253, 235, 167)");
}
void widget_::leaveEvent(QEvent *)
{
	if (is_context == 1) return;
	label_text->setStyleSheet("background-color:rgb(232, 245, 252);");
	mymaxim_text->setStyleSheet("background-color:rgb(232, 245, 252);");
}
void widget_::focusInEvent(QFocusEvent *)
{
	label_text->setStyleSheet("background-color:rgb(253, 235, 167)");
	mymaxim_text->setStyleSheet("background-color:rgb(232, 245, 252);");
}
void widget_::focusOutEvent(QFocusEvent *)
{
	//label_text->setStyleSheet("background - color:rgb(232, 245, 252);");
	//mymaxim_text->setStyleSheet("background - color:rgb(232, 245, 252);");
}
void widget_::mousePressEvent(QMouseEvent *)
{
	label_text->setStyleSheet("background-color:rgb(253, 235, 167)");
	mymaxim_text->setStyleSheet("background-color:rgb(253, 235, 167)");
}
widget_*& widget_::operator =(widget_ *&wi)
{
	widget_ *wp = new widget_;
	wp->posit = wi->posit;
	wp->id__ = wi->id__;
	wp->chatt = wi->chatt;
	wp->chatisopen = wi->chatisopen;
	wp->lp = wi->lp;
	wp->group_member = wi->group_member;
	wp->pi = wi->pi;
	wp->name = wi->name;
	exit(0);
	return wp;
}
void widget_::set_is_group()
{
	if_group = true;
	chatt->if_is_group(true, id__);
}
void widget_::set_isonline(string isonline__)
{
	QPixmap pix;
	if (strcmp(isonline__.data(), "0")) 
	{
		pix.load(head_image);
		
		pix = pix.scaled(40, 50);
		if (pix.isNull())
		{
			cout << "hello";
		}
		if_exist = true;
		label_icon->setPixmap(pix);
	}
	else
	{
		pix.load(head_image_gray);
		pix = pix.scaled(40, 50);
		label_icon->setPixmap(pix);
		if_exist = false;
	}
}
widget_::~widget_()
{
	
}
void widget_::set_group_member(string member)
{
	group_member.push_back(member);
}
void widget_::get_image_and_text(QPixmap _pix, QString _text)
{
	QHBoxLayout *hlayout = new QHBoxLayout(this);
	pi = _pix;
	string il = friend_detail[id__]->picture_name;
	if (il.empty()) il = "./image/qq";
	if (strcmp(il.data(), "0"))
	{
		head_image = "friend_head/" + QString::fromStdString(il);
		head_image_gray = "friend_head/gray_" + QString::fromStdString(il);
	}
	else
	{
		head_image = "friend_head/qq";
		head_image_gray = "friend_head/gray_qq";
	}
	QString mymaximi = QString::fromStdString(friend_detail[id__]->mymaxim);
	if (mymaximi.isEmpty()) mymaximi = "0";
	mymaxim_text->setText(mymaximi);
	label_text = new QLabel(this); label_icon = new QLabel(this);
	QPalette pal;
	pal.setColor(QPalette::ButtonText, QColor(0, 0, 0));
	label_text->setPalette(pal);
	QPixmap pix = _pix;
	pix = pix.scaled(40, 50);
	QString text = _text;
	this->name = text.toStdString();
	label_icon->setFixedSize(40, 50);
	QIcon ic(pix);
	label_text->setText(text);
	label_icon->setPixmap(pix);
	//hlayout->addWidget(label_icon);
	label_icon->setContentsMargins(0, 0, 0, 0);
	//hlayout->addStretch();
	//hlayout->addWidget(label_text);
	//this->setLayout(hlayout);
	label_icon->move(0, 0);
	label_text->move(50, -5);
	mymaxim_text->move(50, 19);
	QPalette pal2;
	pal2.setColor(QPalette::ButtonText, QColor(150, 153, 196));
	mymaxim_text->setPalette(pal2);
	label_text->setStyleSheet("QFrame{background-color:rgb(232,245,252) }"
		"QFrame:hover{ background-color:rgb(253,235,167); }");
}
void widget_::contextMenuEvent(QContextMenuEvent *event)
{
	is_context = 1;
	label_text->setStyleSheet("background-color:rgb(253, 235, 167);");
	connect(detail_information, SIGNAL(triggered()), this, SLOT(detail_information_show()));
	menu->addAction(sendtext);
	menu->setStyleSheet("QMenu {background-color: rgb(255, 255, 255);border: 1px solid black;}"
		"QMenu::item {background-color: transparent;}"
		"QMenu::item:selected { background-color:rgb(0, 170, 255);}");
	sendtext->setText("发送消息");
	connect(sendtext, SIGNAL(triggered()), this, SLOT(send_text_handle()));
	menu->addAction(delete_name);
	if (!if_group)
	{
		delete_name->setText("删除该好友"); //退出群组
		connect(delete_name, SIGNAL(triggered()), this, SLOT(delete_handle()));
	}
	else
	{
		delete_name->setText("退出群组");
		connect(delete_name, SIGNAL(triggered()), this, SLOT(exit_group()));
	}
	
	if (!if_group)
	{
		menu->addAction(move);
		move->setText("移动到其他组"); //查看群成员
		QMenu *menu_move = new QMenu(this);
		menu_move->addAction(move_friend);
		move_friend->setText("移动至好友");
		move_stranger->setText("移动至陌生人");
		move_balack->setText("移动至黑名单");
		menu->addAction(detail_information);
		detail_information->setText("好友详情");
		menu_move->addAction(move_stranger);
		menu_move->addAction(move_balack);
		move->setMenu(menu_move);
		connect(move_balack, SIGNAL(triggered()), this, SLOT(move_balack_handle()));
		connect(move_friend, SIGNAL(triggered()), this, SLOT(move_friend_handle()));
		connect(move_stranger, SIGNAL(triggered()), this, SLOT(move_stranger_handle()));
		menu->exec(QCursor::pos());
		is_context = 0;
		return;
	}
	if (if_group)
	{
		menu->addAction(look_information);
		look_information->setText("查看群友");
		connect(look_information, SIGNAL(triggered()), this, SLOT(show_group_firend_information()));
	}
	
	menu->exec(QCursor::pos());
	is_context = 0;
}
void widget_::exit_group()
{
	QMessageBox::StandardButton button = QMessageBox::question(this, "消息", "确认要退出该群？");
	if (button == QMessageBox::StandardButton::Yes)
	{
		tool->remove_widget(3, this);
		pro->change_(id__, 4);
	}
	else
	{
		return;
	}
}
void widget_::show_group_firend_information()
{
	look_all_friend *lo = new look_all_friend;
	int i = group_member.size();
	for (int h = 0; h < i; h++)
	{
		lo->insert_listwidgetitem(QString::fromStdString(group_member[h]));
	}
	lo->show();
}
void widget_::delete_handle()
{
	tool->remove_widget(posit, this);
	
}
void widget_::move_balack_handle()
{
	if (posit == 2) return;
	tool->move_widget(posit, 2, this);
	posit = 2;
}
void widget_::move_friend_handle()
{
	if (posit == 0) return;
	tool->move_widget(posit, 0, this);
	posit = 0;
}
void widget_::move_stranger_handle()
{
	if (posit == 1) return;
	tool->move_widget(posit, 1, this);
	posit = 1;
	
}
void widget_::send_text_handle()
{
	clicked_me_handle();
}

void widget_::detail_information_show()
{
	_detail = new detailfriendss();
	
	friend_information *frid = friend_detail[id__];
	QString ing = QString::fromStdString(id__);
	QString birthday_  = QString::fromStdString(frid->birthday);
	QString telephone_ = QString::fromStdString(frid->telephone);
	QString name_ = QString::fromStdString(frid->name);
	QString mymaxim_ = QString::fromStdString(frid->mymaxim);

	//_detail->change_(name_, telephone_, birthday_, mymaxim_, "0", ing);
	_detail->show();
}
//删除某一个好友通过他的id
int widget_::remove_friend(QString str)
{
	
	auto iter = widges_friend.find(str);
	if (iter == widges_friend.end())
	{
		iter = widges_stranger.find(str);
		if (iter == widges_stranger.end())
		{
			iter == widges_balack.find(str);
			if (iter == widges_balack.end())
			{
				QMessageBox::critical(this, "数据异常", NULL);
			}
		}
		else
		{
			tool->remove_widget(1, iter->second);
		}
	}
	else
	{
		tool->remove_widget(0, iter->second);
	}
	return 1;
}
void widget_::mouseDoubleClickEvent(QMouseEvent * event)
{
	clicked_me_handle();
}
//作用是给chattext显示东西，刚点开chattext后有没有东西显示
void widget_::set_message_for_chattext(int type_, string time, string text_, string image, string name, string id_, string id_name)
{
	/*normal = 1;
 sound = 2;
 video = 3;
 unknown = 4;
 system_ = 5;
 query_friend = 6;
 query_friend_ack = 7;
 group = 8;
 file_message = 9;*/
	hpp hp;
	hp.type = type_;
	hp.text = text_;
	hp.image = image;
	hp.name = name;
	hp.name_ = id_name;
	hp.id = id_;
	hp.time___ = time;
	lp.push_back(hp);
}
//有问题
void widget_::clicked_me_handle()
{
	this->setStyleSheet("QFrame{background-color:rgb(232,245,252); }"
		"QFrame:hover{ background-color:rgb(253,235,167); }");
	if (!*chatisopen)
	{
		if (chat_with.find(id__) == chat_with.end()) chat_with[id__] = chatt;
		chatt = chat_with.find(id__)->second;
		chatt->show();
		*chatisopen = true;
		//chat_with_widget[chatt] = this;
		for (auto iter = lp.begin(); iter != lp.end(); iter++)
		{
			if ((iter)->type == 1 || (iter)->type == 5)
			{
				if (if_group)
				chatt->set_messagefrom_friend(iter->time___ ,iter->text, iter->image, iter->name, iter->name_);
				else chatt->set_messagefrom_friend(iter->time___, iter->text, iter->image, iter->name);
			}
			else if (iter->type == 2)
			{
				string in = "friend_sound/" + iter->name;
				chatt->set_sound_file(iter->image, iter->name);
				if (if_group)
				chatt->send_sound(iter->time___, 1 ,QString::fromStdString(iter->name), iter->name_);
				else chatt->send_sound(iter->time___, 1, QString::fromStdString(iter->name));
				
			}
		}
	}
	else chat_with[id__]->show();
}
