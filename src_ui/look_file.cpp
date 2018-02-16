#include "look_file.h"
#include <qmap.h>
#include "protobuf_client.h"
#include <qlabel.h>
#include <qpushbutton.h>
#include <qpixmap.h>
#include <string>
#include <qprogressbar.h>
QEvent::Type download_size;
QEvent::Type download_num;
int download_num_;
int download_all;
look_file *file_dow;
extern protobuf_client *pro;
string file_download_name;
using namespace std;
static QListWidgetItem *it1;
QProgressBar *ba;
int now_num;
static QMap<QPushButton*, QListWidgetItem*>li;
extern bool recv_flag, send_flag;
look_file::look_file(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("我的文件");
	recv_flag = false;
	send_flag = false;
	ui.listWidget->setStyleSheet("QListWidget{background-color:yellow;show-decoration-selected: 1;}"
		"QListWidget::item:alternate {background: #EEEEEE;}"
		"QListWidget::item:selected:!active{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #ABAFE5, stop: 1 #8588B2);}"
		"QListWidget::item:selected:active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #6a6ea9, stop: 1 #888dd9);}"
		"QListWidget::item:hover {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FAFBFE, stop: 1 #DCDEF1);}"
		"QListWidget::item:alternate {background: #EEEEEE;}");
	file_dow = this;
	download_all = 0;
	download_num_ = 0;
	now_num = 0;
	download_size = (QEvent::Type)5004;
	download_num = (QEvent::Type)5005;;
}
void look_file::insert_listwidgetitem(QString sender, QString file_name)
{
	QListWidgetItem *it = new QListWidgetItem(ui.listWidget);
	
	
	it->setSizeHint(QSize(241, 40));
	QWidget *wi = new QWidget;
	wi->setFixedSize(241, 40);
	QProgressBar *bar = new QProgressBar(wi);
	bar->setGeometry(0, 0, 241, 40);
	bar->setStyleSheet("QProgressBar{background:transparent;border-radius: 5px;} QProgressBar::chunk{background-color:rgb(210,233,247,180);}");
	QString st = file_name + "\n" + "发送人:" + sender;
	it->setText(st);
	QPushButton *pt = new QPushButton(wi);
	pt->setStyleSheet("QPushButton{border-image:url(./image/download_normal.png);}"
		"QPushButton:press{border-image:url(./image/download_down.png);}"
		"QPushButton:hover{border-image:url(./image/download_hover.png);}");
	pt->setGeometry(210, 5, 30, 30);
	ui.listWidget->setItemWidget(it, wi);
	connect(pt, SIGNAL(clicked()), this, SLOT(download()));
	li[pt] = it;
}
look_file::~look_file()
{

}

void look_file::download()
{
	if (recv_flag)
	{
		QMessageBox::warning(this, "警告", "正在下载文件");
		return;
	}
	recv_flag = true;
	QPushButton *bu = (QPushButton *)sender();
	if (li.find(bu) == li.end())
	{
		QMessageBox::warning(this, "警告", "数据异常");
		return;
	}
	QListWidgetItem *it = li[bu];
	QString st = it->text();
	string in = st.toStdString();
	int h = in.find('\n', 0);
	file_download_name = in.substr(0, h);
	pro->change_(file_download_name, 8);
	it1 = it;
}
void look_file::customEvent(QEvent *event)
{

	if (event->type() == download_size)
	{
		if (download_all != 0)
		{
			QWidget *wi = ui.listWidget->itemWidget(it1);
			QObjectList children = wi->children();
			for (auto it = children.begin(); it != children.end(); it++)
			{
				QObject *g = *it;
				if (g->inherits("QProgressBar"))
				{
					ba = (QProgressBar*)g;
					ba->setMinimum(0);  // 最小值
					ba->setMaximum(download_all);  // 最大值
					ba->setValue(0);
					ba->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
				}
			}
		}
	}
	else if (event->type() == download_num)
	{
		
		ba->setValue(now_num);
		if (now_num >= download_all)
		{
			ba->setValue(download_all);
			QMessageBox::information(this, "提示", "下载成功");
			now_num = 0;
			download_all = 0;
			recv_flag = false;
		}
		else
		{
			cout << "hdgf";
		}
	}
	
}

