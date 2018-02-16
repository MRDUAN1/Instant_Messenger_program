#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include <QWidget>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qevent.h>

class AccountItem : public QWidget
{
	Q_OBJECT

public:
	AccountItem(QWidget *parent);
	~AccountItem();
	

private:
	int mouse_press;
	QLabel *account_number;
	QPushButton *delede_button;
	public slots:
	void setAccountNumber(QString account_text);
	QString getAccountNumber();
	void removeAccount1();
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

signals:
	void sigShowAccount(QString);
	void sigRemoveAccount(QString);
	
	
	
	
};

#endif // ACCOUNTITEM_H
