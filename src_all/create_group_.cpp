#include "create_group_.h"
#include "protobuf_client.h"
#include <string>
# pragma execution_character_set("utf-8")
extern protobuf_client *pro;
//i为2加入群组
create_group_::create_group_(QString str, int i,  QWidget *parent, string id___)
	: QWidget(parent)
{
	ui.setupUi(this);
	id = id___;
	h = i;
	this->setWindowTitle(str);
	ui.pushButton->setText("确定");
	ui.pushButton_2->setText("取消");
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok_handle()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(cancle_handle()));
}

create_group_::~create_group_()
{

}
void create_group_::ok_handle()
{
	GroupName = ui.lineEdit->text();
	//pro->send_groupcreate_message(GroupName);
	if (h == 0)
		pro->change_(GroupName.toStdString(), 3);
	else if (h == 1)
		pro->change_(GroupName.toStdString(), 0);
	else if (h == 2)
		pro->change_(GroupName.toStdString(), 5);
	else if (h == 3)
		pro->query_add_friend(account, GroupName);
	else if (h == 4)
		pro->change_passwd_one(id, GroupName.toStdString());
	this->close();
}
void create_group_::cancle_handle()
{
	this->close();
}
