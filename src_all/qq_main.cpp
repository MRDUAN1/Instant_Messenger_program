#include "qq_main.h"
#include "system_tray.h"
#include "menu_add.h"
#include "accountitem.h"
#include "tool_widget.h"
#include "find_backcode.h"
#include <qmatrix.h>
#include <qlistwidget.h>
using namespace std;
system_tray *s_tt;
map<QString, QString>mp;
protobuf_client *protobuf_;
qq_main *me;
static QSettings setting("config.ini", QSettings::IniFormat);
static QSettings settingbox("combox.ini", QSettings::IniFormat);
# pragma execution_character_set("utf-8")
extern map<string, friend_information*> friend_detail;
extern struct _my_information my_information;
qq_main::qq_main(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	
	list_widget = new QListWidget();
	protobuf_ = new protobuf_client;
	if (setting.contains(tr("auto_login"))&&setting.contains(tr("save_code")))
	{
		auto_login_is_checked = setting.value(tr("auto_login")).toBool();
		save_code_if_true = setting.value(tr("save_code")).toBool();	
	}
	else
	{
		setting.setValue(tr("auto_login"), false);
		setting.setValue(tr("save_code"), false);
	}
	//centerWindow = new QWidget;
	//this->setCentralWidget(centerWindow);
	this->setFixedSize(400, 350);
	createui();
	setui();
	make_style_sheet();
	menu_add *menu = new menu_add(this);
	//menu->setStyleSheet("background:red");
	menu->setGeometry(95, 257, menu->width(), menu->height());
	tool_widget *tool_hp = new tool_widget(this);
	tool_hp->setGeometry(284, 0, tool_hp->width(), tool_hp->height());	
	setconnect();
	me = this;
	QStringList li = settingbox.allKeys();
	int lenn = li.size();
	if (li.isEmpty())
	{
		settingbox.setValue("begin", 0);
	}
	else
	{
		for (int i = 0; i < lenn - 1; i++)
		{
			QString iff = li[i];
			//QString ip = settingbox.value(iff);
			QString igf = settingbox.value(iff).toString();
			//int ig = settingbox.value(iff).toDouble();
			if (!iff.isEmpty()) mp[iff] = igf;
			insert_combox(iff, igf);
		}
	}
	if (save_code_if_true)
	{
		showAccount(li[1]);
	}
	if (auto_login_is_checked)
	{
		login_click();
	}
	system_tray *st = new system_tray;
	s_tt = st;
}

qq_main::~qq_main()
{

}
void qq_main::createui()
{
	use = new QComboBox(this);
	passwd = new QLineEdit(this);
	save = new QCheckBox(this);
	autologin = new QCheckBox(this);
	login = new QPushButton(this);
	background = new QWidget(this);
	findback = new QPushButton(this);
	findback->setText("找回密码");
	findback->setFocusPolicy(Qt::NoFocus);
	findback->setFlat(true);
	register_name = new QPushButton(this);
	register_name->setText("注册账户");
	register_name->setStyleSheet("color:blue");
	register_name->setFlat(true);
	qq_image = new QLabel(this);
	qq_image_2 = new QLabel(this);
	pix.load("./image/qq.png");
	qq_image->resize(100, 110);
	pix = pix.scaled(100, 110, Qt::KeepAspectRatioByExpanding);
	qq_image->setPixmap(pix);
	pix_2.load("./image/head1.jpg");
	qq_image_2->resize(80, 80);
	pix_2 = pix_2.scaled(80, 80);
	qq_image_2->setPixmap(pix_2);

}
void qq_main::setui()
{
	background->setGeometry(0, 0, this->width(), this->height() / 2);
	
	use->setFixedSize(200, 33);
	passwd->setFixedSize(200, 33);
	use->move(this->width() / 2 - 80, this->height() / 2 + 20);
	passwd->move(this->width() / 2 - 80, this->height() / 2 + 58);
	login->setText("登录");
	QRect rect_((this->width() / 2 - use->width() / 2 + 20), this->height() / 2 + 30 + 2 * use->height(), use->width(), login->height());
	save->setText(tr("保存密码"));
	save->setGeometry((this->width() / 2 - use->width() / 2 + 20), this->height() / 2 + 22 + 2 * use->height(), save->width(), save->height());
	if (auto_login_is_checked == true) autologin->setChecked(true);
	if (save_code_if_true == true) save->setChecked(true);
	autologin->setText("自动登录");
	autologin->setGeometry((this->width() / 2 - use->width() / 2 + 40) + use->width() / 2, this->height() / 2 + 22 + 2 * use->height(), save->width(), save->height());
	login->setGeometry((this->width() / 2 - use->width() / 2 + 20), this->height() / 2 + 50 + 2 * use->height(), use->width(), login->height());
	findback->setGeometry(this->width() / 2 + use->width() / 2 + 5, this->height() / 2 + 23, findback->width(), findback->height());
	register_name->setGeometry(this->width() / 2 + use->width() / 2 +5, this->height() / 2 + 57, findback->width(), findback->height());
	qq_image->setGeometry(150, 20, qq_image->width(), qq_image->height());
	qq_image_2->setGeometry(28, 195, qq_image_2->width(), qq_image_2->height());
}

void qq_main::make_style_sheet()
{
	save->setStyleSheet("QCheckBox::indicator{width:15px;height:15px}"
		"QCheckBox{color:gray}");
	autologin->setStyleSheet("QCheckBox::indicator{width:15px;height:15px}"
		"QCheckBox{color:gray}");
	findback->setStyleSheet("QPushButton{color:rgb(39, 134, 228);border:none}"
		"QPushButton:press{color:rgb(98, 180, 247);border:none}"
		"QPushButton:hover{color:rgb(98, 180, 247);border:none}");
	findback->setCursor(QCursor(Qt::PointingHandCursor));
	register_name->setStyleSheet("QPushButton{color:rgb(39, 134, 228);border:none}"
		"QPushButton:press{color:rgb(98, 180, 247);border:none}"
		"QPushButton:hover{color:rgb(98, 180, 247);border:none}");
	register_name->setCursor(QCursor(Qt::PointingHandCursor));
	background->setStyleSheet("background-color:rgb(74, 153, 255);");
	login->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;"
		"background-color:blue"
		);
	QPalette pal;
	pal.setColor(QPalette::ButtonText, QColor(255, 255, 255));
	login->setPalette(pal);
	use->setEditable(true);
	use->lineEdit()->setMaxLength(40);
	use->setContextMenuPolicy(Qt::NoContextMenu);
	use->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 8px;padding: 1px 18px 1px 3px;"
		"QComboBox::drop-down{ min-width: 100px; }"
		"QComboBox::hover{ border:1.5px solid rgb(85, 170, 255); })"
		"QComboBox::QAbstractItemView::item{height:100px;min-height:100px;");
	
	use->setModel(list_widget->model());
	use->setView(list_widget);
	use->setEditable(true); //设置QComboBox可编辑
	passwd->setStyleSheet("QLineEdit {border: 1px solid gray;border-radius: 3px;padding: 0 8px;selection - background - color: darkgray;}");
}
void qq_main::insert_combox(QString id, QString passwd)
{
	AccountItem *account_item = new AccountItem(this);
	account_item->setAccountNumber(id);
	connect(account_item, SIGNAL(sigShowAccount(QString)), this, SLOT(showAccount(QString)));
	connect(account_item, SIGNAL(sigRemoveAccount(QString)), this, SLOT(removeAccount(QString)));
	QListWidgetItem *list_item = new QListWidgetItem(list_widget);
	list_item->setSizeHint(QSize(200, 32));
	list_widget->setItemWidget(list_item, account_item);
}
void qq_main::change_combox(QString id, QString pa)
{
	remove_it(id);
	insert_combox(id, pa);
	showAccount(id);
}
void qq_main::showAccount(QString str)
{
	QString code;
	use->setEditText(str);
	if (save_code_if_true)
	{
		code = mp[str];
		passwd->setText(code);
	}
	use->hidePopup();
}
void qq_main::remove_it(QString str)
{
	int list_count = list_widget->count();
	for (int i = 0; i < list_count; i++)
	{
		QListWidgetItem *item = list_widget->item(i);
		AccountItem *account_item = (AccountItem *)(list_widget->itemWidget(item));
		QString account_number = account_item->getAccountNumber();
		if (str == account_number)
		{
			list_widget->takeItem(i);
			delete item;
			break;
		}
		mp.erase(account_number);
	}
}
void qq_main::removeAccount(QString str)
{
	use->hidePopup();
	QMessageBox::StandardButton button = QMessageBox::question(this, tr("remove account"), tr("are you sure to remove account?"));
	if (button == QMessageBox::StandardButton::Yes)
	{
		remove_it(str);
	}
	else
	{
	}
	use->showPopup();
}
void qq_main::paintEvent(QPaintEvent *event)
{
	QBitmap bitmap(this->size());
	QPainter painter(&bitmap);
	painter.fillRect(bitmap.rect(), Qt::white);
	painter.setBrush(QColor(0, 0, 0));
	painter.setRenderHint(QPainter::Antialiasing);//平滑
	painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap,
		Qt::RoundJoin));
	painter.drawRoundedRect(this->rect(), 10, 10);
	this->setMask(bitmap);//可设置不同的形	
}
void qq_main::mousePressEvent(QMouseEvent *event)
{
	this->windowPos = this->pos();                // 获得部件当前位置
	this->mousePos = event->globalPos();     // 获得鼠标位置
	this->dPos = mousePos - windowPos;       // 移动后部件所在的位置
}

void qq_main::mouseMoveEvent(QMouseEvent *event)
{
	this->move(event->globalPos() - this->dPos);
}
void qq_main::setconnect()
{
	connect(save, SIGNAL(stateChanged(int)), this, SLOT(sava_check()));
	connect(autologin, SIGNAL(stateChanged(int)), this, SLOT(autologin_check()));
	connect(login, SIGNAL(clicked()), this, SLOT(login_click()));
	connect(findback, SIGNAL(clicked()), this, SLOT(findback_click()));
	connect(register_name, SIGNAL(clicked()), this, SLOT(register_clicked()));
	
}
void qq_main::sava_check()
{
	if (Qt::Checked == save->checkState())
	{
		save_code_if_true = true;
		setting.setValue(tr("save_code"), true);
	}
	else if (Qt::Unchecked == save->checkState())
	{
		save_code_if_true = false;
		setting.setValue(tr("save_code"), false);
	}
}
void qq_main::autologin_check()
{
	if (Qt::Checked == autologin->checkState())
	{
		auto_login_is_checked = true;
		setting.setValue(tr("auto_login"), true);
	}
	else if (Qt::Unchecked == autologin->checkState())
	{
		auto_login_is_checked = false;
		setting.setValue(tr("auto_login"), false);
	}
}

void qq_main::login_click()
{
	QString temp_account = use->lineEdit()->text();
	if (!check_num_is_legal(temp_account))
	{
		return;
	}
	QString string_passwd = passwd->text();
	if (string_passwd.isEmpty())
	{
		QMessageBox::warning(this, "密码为空", "密码为空");
		return;
	}
	if (mp.find(temp_account) == mp.end())
	{
		insert_combox(temp_account, string_passwd);
		settingbox.setValue(temp_account, string_passwd);
		mp[temp_account] = string_passwd;
	}
	else
	{
		mp[temp_account] = string_passwd;
		settingbox.setValue(temp_account, string_passwd);
		mp[temp_account] = string_passwd;
		change_combox(temp_account, string_passwd);
	}
	protobuf_->make_login_message(temp_account, string_passwd);
	
}
void qq_main::findback_click()
{
	find_backcode *findback = new find_backcode;
	findback->show();
}
void qq_main::register_clicked()
{
	register_dialog_ = new register_dialog(this);
	
}
int qq_main::check_num_is_legal(QString name)
{
	QByteArray ba = name.toLatin1();
	const char *s = ba.data();
	int num = 0;
	if (name.isEmpty())
	{
		QMessageBox::warning(this, "账号为空", "账号为空");
		use->lineEdit()->clear();
		return 0;
	}
	while (*s && *s >= '0'&& *s <= '9')
	{
		s++;
		num++;
	}
	if (*s)
	{
		QMessageBox::warning(this, "格式错误", "必需全为数字");
		use->lineEdit()->clear();
		return 0;
	}
	if (num != 10)
	{
		QMessageBox::warning(this, "格式错误", "账号位数为10位");
		use->lineEdit()->clear();
		return 0;
	}
	return 1;
}


