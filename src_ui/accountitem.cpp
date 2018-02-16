#include "accountitem.h"


AccountItem::AccountItem(QWidget *parent)
	: QWidget(parent)
{
	mouse_press = false;
	account_number = new QLabel();
	delede_button = new QPushButton();
	QPixmap pixmap("delete");
	delede_button->setIcon(pixmap);
	delede_button->setIconSize(pixmap.size());
	delede_button->setStyleSheet("background:transparent;");
	connect(delede_button, SIGNAL(clicked()), this, SLOT(removeAccount1()));
	QHBoxLayout *main_layout = new QHBoxLayout();
	main_layout->addWidget(account_number);
	main_layout->addStretch();
	main_layout->addWidget(delede_button);
	main_layout->setContentsMargins(5, 5, 5, 5);
	main_layout->setSpacing(5);
	this->setLayout(main_layout);
}
AccountItem::~AccountItem()
{

}

void AccountItem::setAccountNumber(QString account_text)
{
	account_number->setText(account_text);
}
QString AccountItem::getAccountNumber()
{
	QString account_number_text = account_number->text();
	return account_number_text;
}
void AccountItem::removeAccount1()
{
	QString account_number_text = account_number->text();
	emit sigRemoveAccount(account_number_text);
}
void AccountItem::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		mouse_press = true;
	}
}
void AccountItem::mouseReleaseEvent(QMouseEvent *event)
{
	if (mouse_press)
	{
		emit sigShowAccount(account_number->text());
		mouse_press = false;
	}
}