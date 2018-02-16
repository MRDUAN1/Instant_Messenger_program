#include "look_all_friend.h"
#include "create_group_.h"
#include <qsize.h>
# pragma execution_character_set("utf-8")
look_all_friend::look_all_friend(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QSize s(40, 50);
	ui.listWidget->setIconSize(s);
	QString st("qq.png");
	pix.load(st);
	pix = pix.scaled(40, 50);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok_clicked()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(cancle_clicked()));
}
void look_all_friend::cancle_clicked()
{
	this->close();
}
void look_all_friend::insert_listwidgetitem(QString str)
{
	QListWidgetItem *it = new QListWidgetItem(QIcon(pix), str, ui.listWidget);
	
	it->setSizeHint(QSize(241, 50));
	connect(ui.listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(selectclicked()));
}

look_all_friend::~look_all_friend()
{

}
void look_all_friend::selectclicked()
{
	QListWidgetItem *li = ui.listWidget->currentItem();
	str = li->text();
}
void look_all_friend::ok_clicked()
{
	if (str.isEmpty()) return;
	create_group_ *cr = new create_group_("Ìí¼ÓºÃÓÑ", 3);
	cr->set_account(str);
	cr->show();
}
