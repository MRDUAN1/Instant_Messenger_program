#include "chatting.h"

chatting::chatting(QWidget *parent)
	: QWidget(parent)
{
	this->setFixedSize(722, 470);
	webView = new QWebEngineView(this);
	webView->setFixedSize(680, 386);
	webView->setGeometry(20, 0, webView->width(), webView->height());
	QFile source(":/style.html");
	source.open(QIODevice::ReadOnly);
	webView->setHtml(QString::fromUtf8(source.readAll().constData()));
	source.close();
	QHBoxLayout *hlayout = new QHBoxLayout;
	QLineEdit *edit = new QLineEdit(this);
	QPushButton *pushbutton = new QPushButton(this);
	connect(pushbutton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
	pushbutton->setFixedSize(44, 35);
	QPushButton *pushbutton_1 = new QPushButton(this);
	pushbutton_1->setFixedSize(88, 35);

	edit->setFixedSize(526, 35);
	hlayout->addWidget(pushbutton);
	pushbutton->show();
	hlayout->addStretch();
	hlayout->addWidget(edit);
	hlayout->addStretch();
	hlayout->addWidget(pushbutton_1);
	QRect rect(20, 400, edit->width() + pushbutton->width() + pushbutton_1->width() + 20, edit->height());
	hlayout->setGeometry(rect);


	m_timer = new QTimer();
	connect(m_timer, SIGNAL(timeout()), this, SLOT(disTime()));
	m_timer->start(6000);
	disFlag = false;
	faceFormFlag = false;
	connect(this, SIGNAL(toBottom()), this, SLOT(toViewBottom()));
}

chatting::~chatting()
{

}


void chatting::on_pushButton_clicked()
{
	sendMsgShow(lineEdit->text());
	if (lineEdit->text() == QString("你好"))
		revMsgShow(QString("您好,有什么可以帮助您！"));
	else if (lineEdit->text() == QString("现在几点")) {

		revMsgShow(QString("现在为北京时间：%1").arg(QTime::currentTime().toString("hh:mm:ss")));
	}

}


void chatting::sendMsgShow(QString msg)
{
	QString html = QString("");
	msg.replace("[smail.png]", "<img src=qrc:/smail.png alt=表情 align=center border=0>");
	msg.replace("[ali.gif]", "<img src=qrc:/ali.gif alt=表情 align=center border=0>");
	
	html.append(QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='triangle-right right'>%1</p></div>\")").arg(msg));
	//   }

	webView->page()->runJavaScript(html);
	disFlag = false;
	m_timer->start(30000);
}

void chatting::revMsgShow(QString msg)
{
	QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='triangle-left left'>%1</p></div>\")").arg(msg);
	webView->page()->runJavaScript(html);
}

void chatting::disTime()
{
	disFlag = true;
	m_timer->stop();
}

void chatting::on_pushButton_2_clicked()
{
	if (faceFormFlag){
		disconnect(m_faceForm, SIGNAL(faceClicked(QString)), this, SLOT(addFace(QString)));
		m_faceForm->deleteLater();
		faceFormFlag = false;
		ui->verticalLayout->setStretch(0, 10);
		return;
	}
	m_faceForm = new faceForm();
	faceFormFlag = true;
	ui->verticalLayout->insertWidget(1, m_faceForm, 4);
	ui->verticalLayout->setStretch(0, 6);
	connect(m_faceForm, SIGNAL(faceClicked(QString)), this, SLOT(addFace(QString)));

}


void chatting::addFace(QString text)
{
	lineEdit->setText(lineEdit->text() + text);
	lineEdit->setFocus();
	disconnect(m_faceForm, SIGNAL(faceClicked(QString)), this, SLOT(addFace(QString)));
	m_faceForm->deleteLater();
	faceFormFlag = false;
	ui->verticalLayout->setStretch(0, 10);

}
