#ifndef QQ_MAIN_H
#define QQ_MAIN_H

#include <QtWidgets/QMainWindow>
#include "ui_qq_main.h"
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qboxlayout.h>
#include <qrect.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <qbitmap.h>
#include <qevent.h>
#include <qbytearray.h>
#include <qmessagebox.h>
#include <qsettings.h>
#include <qlistwidget.h>
#include "protobuf_client.h"
#include "register_dialog.h"
class qq_main : public QWidget
{
	Q_OBJECT

public:
	qq_main(QWidget *parent = 0);
	~qq_main();
	

private:
	void createui();
	void setui();
	void make_style_sheet();
	void paintEvent(QPaintEvent *event);
	void change_combox(QString id, QString pa);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void setconnect();
	void insert_combox(QString id, QString passwd);
	int check_num_is_legal(QString);
	Ui::qq_mainClass ui;
	
	bool auto_login_is_checked;
	bool save_code_if_true;
	QWidget* centerWindow;
	QComboBox *use;
	QListWidget *list_widget;
	QLineEdit *passwd;
	QWidget *background;
	QCheckBox *save, *autologin;
	QPushButton *login;
	QPushButton *findback, *register_name;
	QLabel *qq_image, *qq_image_2;
	QPixmap pix, pix_2;
	QPoint windowPos, mousePos, dPos;
	int account_number, string_passwd;
	register_dialog *register_dialog_;
	void remove_it(QString str);
	public slots:
	void sava_check();
	void autologin_check();
	void login_click();
	void findback_click();
	void register_clicked();
	void showAccount(QString);
	void removeAccount(QString);

};

#endif // QQ_MAIN_H
