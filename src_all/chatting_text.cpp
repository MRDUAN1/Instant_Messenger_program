#include "chatting_text.h"
#include "sound_record.h"
#include "camera_recv.h"
#include "camera_modudle.h"
#include <qmessagebox.h>
#include <qcolor.h>
#include <qfiledialog.h>
#include <qimagereader.h>
#include <qdatetime.h>
#include <qdir.h>
#include <qimage.h>
#include <qevent.h>
#include <QFile>
#include <process.h>
#include <qdesktopwidget.h>
extern string id_new;
bool recv_flag, send_flag;
extern networkn *net;
string send_tcp_file_name;
long size_;
extern HANDLE send_send, send_recv, recv_send, recv_recv;
extern QString in;
extern camera_recv *send_send_, *recv_send_;
extern camera_modudle *send_recv_, *recv_recv_;
int camera_file; //0����ͷ��1�����ļ�
sound_record *rec;
extern struct _my_information my_information;
//extern map<chattext*, widget_*>chat_with_widget;
extern map<string, chattext*>chat_with;
extern map<string, friend_information*> friend_detail;
extern protobuf_client *pro;

/*person�к���messagenormal�а�����ͼƬ���֣�������Ϊ���ֵ���*/
chattext::chattext(string id ,protobuf_client *protob, QWidget *parent)
{
	ui.setupUi(this);
	string chat_record_file_name = "chat_record/" + id_new + "_" + id + ".txt";
	file_record = fopen(chat_record_file_name.data(), "a+");
	wj = (widget_ *)parent;
	tool = new tool_widget(this);
	tool->setGeometry(this->width() - tool->width() - 30, 0, tool->width(), tool->height());
	this_id = id;
	get_my_information();
	if_group = false;
	protobuf_ = pro;
	is_image = 0;
	this->setFixedSize(570, 475);
	this->setStyleSheet("background-color:rgb(232, 235, 247);");
	
	create_button();
	set_button();
	layout_button();
	set_connect();
}

chattext::~chattext()
{
}
void chattext::closeEvent(QCloseEvent *event)
{
	//fclose(file_record);
	chat_with[this_id]->hide();
	*(wj->chatisopen) = false;
}
void chattext::paintEvent(QPaintEvent *event)
{
	QBitmap bitmap(this->size());
	QPainter painter(&bitmap);
	painter.fillRect(bitmap.rect(), Qt::white);
	painter.setBrush(QColor(0, 0, 0));
	painter.setRenderHint(QPainter::Antialiasing);//ƽ��
	painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap,
		Qt::RoundJoin));
	painter.drawRoundedRect(this->rect(), 20, 10);
	this->setMask(bitmap);//�����ò�ͬ����
}
//215,217,228
void chattext::create_button()
{
	//click_record = new QPushButton(this);
	textedit = new QTextBrowser(this);
	textedit->setFont(QFont("Timers", 15, QFont::Bold));
	textedit_input = new QTextEdit(this);
	textedit->setLineWrapMode(QTextEdit::WidgetWidth);
	textedit_input->setLineWrapMode(QTextEdit::WidgetWidth);
	front = new QPushButton(this);
	front->setText("����");
	look = new QPushButton(this);
	picture = new QPushButton(this);
	sound = new QPushButton(this);
	sound_top = new QPushButton(this);
	camera = new QPushButton(this);
	camera_end = new QPushButton(this);
	grap_picture = new QPushButton(this);
	send_file = new QPushButton(this);
	//chatroom = new QPushButton(this);
	close_button = new QPushButton(this);
	send_message = new QPushButton(this);
	image_head = new QPushButton(this);
	name_ = new QLabel(this);
	mymaxim_ = new QLabel(this);
	textedit->setReadOnly(true);
}
void chattext::mousePressEvent(QMouseEvent *event)
{
	this->windowPos = this->pos();                // ��ò�����ǰλ��
	this->mousePos = event->globalPos();     // ������λ��
	this->dPos = mousePos - windowPos;       // �ƶ��󲿼����ڵ�λ��
}

void chattext::mouseMoveEvent(QMouseEvent *event)
{
	this->move(event->globalPos() - this->dPos);
}
void chattext::set_button()
{
	//lineedit->setStyleSheet("background-color:rgb(232, 235, 247);");
	QPalette palette = textedit->palette();
	palette.setBrush(QPalette::Background, Qt::red);
	setPalette(palette);
	textedit->setGeometry(0, 90, 570, 290);
	front->setFlat(true);
	front->setFixedSize(60, 30);
	front->setStyleSheet("QPushButton{background:rgb(170, 255, 255);border: 2px solid rgb(85, 255, 0);border-radius: 6px;}");
	QIcon icon_front("aio_quickbar_font");
	//front->setIcon(icon_front);
	look->setFlat(true);
	look->setText("����ͼƬ");
	look->setFixedSize(60, 30);
	look->setStyleSheet("QPushButton{background:rgb(255, 255, 127);border: 2px solid rgb(85, 255, 0);border-radius: 6px;};");
	
	/*"QPushButton{border-color:rgb(0, 255, 255); border: 2px solid rgb(85, 255, 0);border-radius: 6px; border:none};"
		"QPushButton:press{background:rgb(170, 255, 255)};"*/
	picture->setFlat(true);
	picture->hide();
	picture->setFixedSize(30, 30);
	picture->setStyleSheet(
		"QPushButton{background:rgb(85, 255, 0)};}");
	QPixmap pix;
	pix.load("send.png");
	pix = pix.scaled(30, 30);
	sound->setFlat(true);
	sound->setFixedSize(60, 30);
	sound->setStyleSheet(
		"QPushButton{background:rgb(170, 255, 255);border: 2px solid rgb(85, 255, 0);border-radius: 6px;}");
	sound_top->setFlat(true);
	sound_top->setFixedSize(60, 30);
	sound_top->setStyleSheet(
		"QPushButton{background:rgb(255, 255, 127);border: 2px solid rgb(85, 255, 0);border-radius: 6px;};");
	QIcon icon_sound_top("sound.jpg");
	grap_picture->setFlat(true);
	grap_picture->setFixedSize(60, 30);
	grap_picture->setStyleSheet(
		"QPushButton{background:rgb(255, 170, 255);border: 2px solid rgb(85, 255, 0);border-radius: 6px;};");
	grap_picture->setText("���ͽ���");
	grap_picture->move(210, 378);
	connect(grap_picture, SIGNAL(clicked()), this, SLOT(grap_picture_()));
	sound_top->setIcon(icon_sound_top);
	//sound_top->setIcon(icon_sound);
	camera->setFlat(true);
	camera->setFixedSize(60, 30);
	camera->setStyleSheet(
		"QPushButton{background:rgb(85, 255, 0);border: 2px solid rgb(85, 255, 0);border-radius: 6px;};");
	camera_end->setFlat(true);
	camera_end->setFixedSize(60, 30);
	camera_end->setStyleSheet(
		"QPushButton{background:rgb(255, 170, 255);border: 2px solid rgb(85, 255, 0);border-radius: 6px;};");
	camera_end->setText("ֹͣ");
	QIcon icon_camera("camera.jpg");
	camera->setIcon(icon_sound_top);
	send_file->setFlat(true);
	send_file->setFixedSize(60, 30);
	send_file->setStyleSheet(
		"QPushButton{background:rgb(85, 255, 0);border: 2px solid rgb(85, 255, 0);border-radius: 6px;};");
	QIcon icon_send_file("fileassitant_icon_40.png");
	send_file->setIcon(icon_camera);
	//chatroom->setFlat(true);
	//chatroom->setFixedSize(30, 30);
	//chatroom->setStyleSheet(
	//	"QPushButton{background:rgb(232, 235, 247);}");
	QIcon icon_chatroom("chatroom.jpg");
	//chatroom->setIcon(icon_chatroom);
	textedit_input->setGeometry(0, 380, this->width(), 90);
	close_button->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;color:rgb(255, 255, 255)"
		"background-color:rgb(6, 157, 213)");
	close_button->setGeometry(475, 445, 90, 25);
	close_button->setText("�رմ���");
	send_message->setGeometry(375, 445, 90, 25);
	send_message->setText("������Ϣ");
	send_message->setStyleSheet("background:rgb(6, 157, 213);color:rgb(255, 255, 255)");
	image_head->setGeometry(3, 3, 50, 50);
	string hppp;
	if (strcmp(friend_detail[this_id]->picture_name.data(), "0"))
		hppp = friend_detail[this_id]->picture_name;
	else hppp = "qq.png";
	QString ini = "./friend_head/" + QString::fromStdString(hppp);
	QPixmap pixx(ini);
	pixx = pixx.scaled(50, 50);
	QIcon ic(pixx);
	image_head->setFlat(true);
	image_head->setIconSize(QSize(50, 50));
	image_head->setIcon(ic);
	
}
void chattext::grap_picture_()
{
	QPixmap fullScreenPixmap;
	fullScreenPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
	fullScreenPixmap.save("./sound_re/fullScreen.jpg", "JPG");
	file = "./sound_re/fullScreen.jpg";
	send_pictures("./sound_re/fullScreen.jpg");
}
void chattext::layout_button()
{
	hp = new QPushButton(this);

	hp->move(507, 378);
	//QPushButton *front, *look, *picture, *sound, *sound_top, *camera, *send_file, *chatroom;
	front->move(5, 378);
	look->move(70, 378);
//	picture->move(70, 378);
	sound->move(0, 60);
	sound->setText("����");
	sound_top->move(70, 60);
	sound_top->setText("ֹͣ");
	camera->move(140, 60);
	camera_end->move(210, 60);
	camera->setText("��Ƶ");
	send_file->move(140, 378);
	send_file->setText("�ļ�");
	hp->setFlat(true);
	hp->setText("�����¼");
	hp->setFixedSize(60, 30);
	hp->setStyleSheet(
		"QPushButton{background:rgb(255, 170, 255);border: 2px solid rgb(85, 255, 0);border-radius: 6px;};");
	//570,475
	hp->move(507, 378);
	name_->setText(QString::fromStdString(_information.name));
	mymaxim_->setText(QString::fromStdString(_information.mymaxim));
	name_->move(57, 10);
	mymaxim_->move(57, 40);
}
void chattext::set_connect()
{
	QObject::connect(front, SIGNAL(clicked()), this, SLOT(front_trigger()));
	QObject::connect(look, SIGNAL(clicked()), this, SLOT(look_trigger()));
	QObject::connect(picture, SIGNAL(clicked()), this, SLOT(picture_trigger()));
	QObject::connect(sound, SIGNAL(clicked()), this, SLOT(sound_trigger()));
	QObject::connect(sound_top, SIGNAL(clicked()), this, SLOT(sound_top_trigger()));
	QObject::connect(camera, SIGNAL(clicked()), this, SLOT(camera_trigger()));
	QObject::connect(send_file, SIGNAL(clicked()), this, SLOT(send_file_trigger()));
	//QObject::connect(chatroom, SIGNAL(clicked()), this, SLOT(chatroom_trigger()));
	QObject::connect(send_message, SIGNAL(clicked()), this, SLOT(send_message_handle()));
	QObject::connect(close_button, SIGNAL(clicked()), this, SLOT(close_widget()));
	QObject::connect(textedit, SIGNAL(anchorClicked(const QUrl)), this, SLOT(handle_sound(const QUrl)));
	QObject::connect(camera_end, SIGNAL(clicked()), this, SLOT(handle_camera_end()));
	QObject::connect(hp, SIGNAL(clicked()), this, SLOT(handle_click_record()));
	//connect(textedit, SIGNAL(sourceChange(const QUrl&)), this, SLOT(handle_sound(const QUrl)));
}
void chattext::set_file_record(FILE *file)
{
	file_record = file;
}
void chattext::handle_click_record()
{
	//���+text+ͼƬ����+\n
	//�˴����ڷ���,�������100�ֽڵļ�¼
	textedit->clear();
	char buf[300] = { '\0' };
	fseek(file_record, 0, 0);
	
	while (1)
	{
		char *u = fgets(buf, 100, file_record);
		if (u == NULL) break;
		
		string bt(buf);
		char a = *(bt.begin());
		string at(buf + 1);
		int j = atoi(&a);
		if (j == 1)
		{
			//tex += ";" + image_name + "$" + time______ + "#" + name + "\n";
			int pos = at.find(';', 0);
			int pas = at.find('$', 0);
			int pass = at.find('#', 0);
			string text = at.substr(0, pos);
			string image_or = at.substr(pos + 1, pas - pos - 1);
			string time_ = at.substr(pas + 1, pass - pas - 1);
			string name = at.substr(pass + 1);
			this->set_messagefrom_friend(time_, text, "0", image_or, name, true);

		}
		else if (j == 2)
		{
			int pos = at.find('$', 0);
			int pas = at.find('%', 0);
			int pass = at.find('*', 0);
			string sound_path = at.substr(0, pos);
			string tim = at.substr(pos + 1, pas - pos - 1);
			string isgroup = at.substr(pas + 1, pass - pas - 1);
			string is_my = at.substr(pass + 1);
			if (strcmp(is_my.data(), "1"))
			this->send_sound(tim, 1, QString::fromStdString(sound_path), isgroup, true, false);
			else this->send_sound(tim, 1, QString::fromStdString(sound_path), isgroup, true, true);
		}
	}
	fseek(file_record, 0, 0);
}
void chattext::handle_camera_end()
{
	pro->change_(this_id, 7);
	//һ��ֻ��һ��ƥ��
	if (send_send && send_send_)
	{
		TerminateThread(send_send, 0);
		delete send_send_;
	}
	if (send_recv && send_recv_)
	{
		//TerminateThread(send_recv, 0);
		send_recv_->exit_thread = 1;
		delete send_recv_;
	}
	if (recv_send && recv_send_)
	{
		TerminateThread(recv_send, 0);
		delete send_recv_;
	}
	if (recv_recv && recv_recv_)
	{
		//TerminateThread(recv_recv, 0);
		recv_recv_->exit_thread = 1;
		delete recv_recv_;
	}
}
void chattext::close_widget()
{
	this->hide();
}
bool find_http_back(char c)
{
	return c == ':';
}
void chattext::handle_sound(const QUrl h)
{
	QUrl ur = h;
	if (ur.isEmpty())
		exit(0);
	QString st1 = h.fileName();
	string hppp = st1.toStdString();
	
	string::iterator it = find_if(hppp.begin(), hppp.end(), find_http_back);
	string ap = string(it + 1, hppp.end() - 2);
	string hpp(ap.begin() + 1, ap.end());
	if (*ap.begin() == 'M')
		play_sound(QString::fromStdString(hpp), 0);
	else 
		play_sound(QString::fromStdString(hpp), 1);
}
void chattext::play_sound(QString str, int i)
{
	//����,¼����sound_re�����ܲ���
	QString str1;
	if (i == 0)
		str1 = "sound_re/" + str;
	else str1 = "friend_sound/" + str;
	string st = str1.toStdString();
	
	char buf[100] = { '\0' };
	memcpy(buf, st.data(), st.size());
	WCHAR wszClassName[256];
	memset(wszClassName, 0, sizeof(wszClassName));
	MultiByteToWideChar(CP_ACP, 0, buf, st.size(), wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
	PlaySound(wszClassName, NULL, SND_FILENAME | SND_ASYNC);
}

void chattext::front_trigger()
{
	fontDialog = new QFontDialog(this);
	fontDialog->setCurrentFont(textedit_input->font());
	fontDialog->setModal(true);
	if (QDialog::Accepted == fontDialog->exec())
	{
		//saveFile.font = fontDialog->currentFont();
		textedit_input->setFont(fontDialog->currentFont());
		
		//saveFontColor();
	}
}
void chattext::look_trigger()
{
	if (is_image)
	{
		QMessageBox::warning(this, "��ʾ", "һ��ֻ�ܷ���һ��ͼƬ");
		return;
	}
	is_image = 1;
	
	QString file_full, file_name;
	QString slcStr;
	QString fileName;
	fileName = QFileDialog::getOpenFileName(this,
		tr("PNG(*.png);;JPG(*.jpg);;BMP(*.bmp)"));
	if (slcStr.left(3) == "JPG")
	{
		if (fileName.right(4).toLower() != ".jpg")
		{
			fileName += ".jpg";
		}
	}
	if (slcStr.left(3) == "PNG")
	{
		if (fileName.right(4).toLower() != ".png")
		{
			fileName += ".png";
		}
	}
	if (slcStr.left(3) == "BMP")
	{
		if (fileName.right(4).toLower() != ".bmp")
		{
			fileName += ".bmp";
		}
	}
	file = fileName;
	send_pictures(file);
}
void chattext::send_pictures(QString file)
{
	QUrl Uri(QString("%1").arg(file));
	uri = Uri;
	QImage image = QImageReader(file).read();
	image_ = image;
	QTextDocument * textDocument = textedit_input->document();
	textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(image));
	QTextCursor cursor = textedit_input->textCursor();
	QTextImageFormat imageFormat;

	if (image.width() > 100)
	{
		image = image.scaled(100, textedit_input->height());
	}
	if (image.height() > textedit_input->height())
	{
		image = image.scaled(30, textedit_input->height());
	}
	imageFormat.setWidth(image.width());
	imageFormat.setHeight(image.height());
	imageFormat.setName(Uri.toString());
	cursor.insertImage(imageFormat);
}
void chattext::picture_trigger()
{

}
void chattext::sound_trigger()
{
	if (rec != NULL)
	{
		QMessageBox::warning(this, "����", "����¼��");
		return;
	}
	if_speech = true;
	rec = new sound_record;
	rec->start_();
}
void chattext::sound_top_trigger()
{
	if (!if_speech) return;
	rec->end_();
	delete rec;
	rec = NULL;
	QString str = getCurrentDateTime();
	//QString sound_ = "M" + in;
	send_sound(str.toStdString(), 0, in, "0", false, true);
}

void chattext::camera_trigger()
{
	pro->change_(this_id, 6);
	camera_file = 0; //0Ϊ����ͷ
}
void chattext::send_file_trigger()
{
	if (send_flag)
	{
		QMessageBox::warning(this, "����", "���ڷ����ļ�");
		return;
	}
	send_flag = true;
	QString in = QFileDialog::getOpenFileName(this, tr("Open File"));
	send_tcp_file_name = in.toStdString();
	QFileInfo info;
	QString s_tr;
	info = QFileInfo(in);
	s_tr = info.fileName();
	size_ = info.size();

	
	net->send_file();
	pro->handle_send_file(this_id, s_tr.toStdString(), size_);
}
void chattext::chatroom_trigger()
{

}
void chattext::if_is_group(bool if_group_, string group_name_)
{
	//����д��if_group_
	if_group = true;
	group_name = group_name_;
}
//i==1Ϊ���ѷ��͵�����i==0Ϊ�Լ����͵�����
void chattext::send_sound(string time___ ,int i, QString str, string isgroup, bool is_record, bool is_my)
{
	QString ing;
	ing = str;
	QString temp;
	
		if (!is_record)
		{
			char buff[10] = { '\0' };
			itoa(2, buff, 10);
			int i = strlen(buff);
			fwrite(buff, 1, strlen(buff), file_record);
			char bf[1024] = { 0 };
			string tex;
			if (is_my)
			tex = ing.toStdString() + "$" + time___ + "%" + isgroup + "*" + "1" + "\n";
			else tex = ing.toStdString() + "$" + time___ + "%" + isgroup + "*" + "0" + "\n";
			fwrite(tex.data(), 1, tex.size(), file_record);
			fflush(file_record);
		}
	QString dateTime = getCurrentDateTime();
	if (strcmp(time___.data(), "0"))
		time___ = dateTime.toStdString();
	string ii;
	if (i == 0)
	{
		if (strcmp(isgroup.data(), "0"))
			ii = str.toStdString();
		else ii = this_id;
		temp = QString("<font size=\"4\" color=blue>%1    %2: </font>")
			.arg(QString::fromStdString(this_id)).arg(dateTime);
	}
	else temp = QString("<font size=\"4\" color=blue>%1    %2: </font>")
		.arg("��").arg(QString::fromStdString(time___));
	
	textedit->append(temp);
	temp = "<a href=";
	temp += "\\\"";
	if (is_my)
	temp += "http:M" + ing;
	else temp += "http:O" + ing;
	temp += "\\\"";
	temp += ">������Ϣ";
	temp += "</a>";
	QTextCursor cursor1 = textedit->textCursor();
	cursor1.movePosition(QTextCursor::End);
	textedit->setTextCursor(cursor1);
	textedit->append(temp);
	if (i == 0)
	{
		QString lp = "sound_re/" + ing;
		handle_send_image(lp.toStdString());
	}	
}
void chattext::set_sound_file(string ing, string nam)
{
	string j = "./friend_sound/" + nam;
	ofstream fd(j, std::ios::out | std::ios::binary);
	fd.write(ing.data(), ing.size());
	fd.close();
}
void chattext::send_message_handle()
{
	//tex += ";" + image_name + "$" + time______ + "#" + name + "\n";
	/*����Ĵ���*/
	char buff[10] = { '\0' };
	itoa(1, buff, 10);
	int i = strlen(buff);
	fwrite(buff, 1, strlen(buff), file_record);
	char bf[1024] = { 0 };
	//���+text+ͼƬ����+ʱ��\n
	
	QString dateTime = getCurrentDateTime();
	QString temp = QString("<font size=\"4\" color=blue>%1    %2: </font>")
		.arg("��").arg(dateTime);
	textedit->append(temp);
	QString str = textedit_input->toPlainText();
	str_ = str.toStdString();
	if (uri.isEmpty())
	{
		QTextCharFormat fmt;
		fmt.setForeground(Qt::black);
		QTextCursor cursor1 = textedit->textCursor();
		cursor1.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
		cursor1.mergeCharFormat(fmt);
		textedit->mergeCurrentCharFormat(fmt);
		textedit->append(QString::fromStdString(str_));

		string tex = str_;
		tex += ";0$" +  dateTime.toStdString() + "#" + "��" + "\n";
		fwrite(tex.data(), 1, tex.size(), file_record);
		fflush(file_record);

		int i = cursor1.position();
		textedit->setTextCursor(cursor1);
		textedit_input->clear();
		if (if_group)
		protobuf_->send_normal_message(this_id, str_, "0", "0", group_name);
		else protobuf_->send_normal_message(this_id, str_);
		return;
	}
	QFileInfo in(file); string im_name = in.fileName().toStdString();
	handle_send_image();
	string tex = str_;
	tex = ";" + file.toStdString() + "$" + dateTime.toStdString() + "#" + "��" + "\n";
	fwrite(tex.data(), 1, tex.size(), file_record);
	fflush(file_record);
	if (image_.width() > textedit->width())
	{
		image_ = image_.scaled(textedit->width() / 3 * 2, image_.height());
	}
	if (image_.height() > textedit->height())
	{
		image_ = image_.scaled(image_.width(), textedit->height() / 4 * 3);
	}
	QTextDocument * textDocument = textedit->document();
	textDocument->addResource(QTextDocument::ImageResource, uri, QVariant(image_));
	//QTextDocument * textDocument = lineedit_input->document();
	//textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(image));
	QTextCursor cursor = textedit->textCursor();
	QTextImageFormat imageFormat;
	imageFormat.setWidth(image_.width());
	imageFormat.setHeight(image_.height());
	QString st = uri.toString();
	imageFormat.setName(uri.toString());
	cursor.insertImage(imageFormat);
	
	textedit->append(str);
	QTextCursor cursor1 = textedit->textCursor();
	cursor1.movePosition(QTextCursor::End);
	textedit->setTextCursor(cursor1);
	textedit_input->clear();
	uri.clear();
	is_image = 0;
	file.clear();
}
QString chattext::getCurrentDateTime()
{
	QTime time = QTime::currentTime();
	QDate date = QDate::currentDate();

	return QString("%1  %2").arg(date.toString(Qt::ISODate))
		.arg(time.toString(Qt::ISODate));
}
void chattext::handle_send_image(string hp)
{
	QString fi;
	string image___;
	if (!strcmp(hp.data(), "0"))
		fi = file;
	else fi = QString::fromStdString(hp);
		if (fi.isEmpty())
			return;

		FILE *file1;
		char buf[1024] = { '\0' };
		//memcpy(buf, file.toStdString().data(), file.toStdString().size());
		//image___.append(buf, 50);
		memset(buf, 0, 1024);
		if ((file1 = fopen(fi.toStdString().data(), "rb")) == NULL)
		{
			perror("file open");
			QMessageBox::warning(this, "����ͼƬʧ��", "ͼƬ�ļ�����������");
			return;
		}
		while (!feof(file1))
		{
			int len_ = fread(buf, 1, 1024, file1);
			image___.append(buf, sizeof(buf));
			memset(buf, 0, 1024);
		}
		fclose(file1);
		//ֻ�����ļ����Ѿ��Ե�ַת��Ϊ�ļ���

		QFileInfo info;
		QString s_tr;
		info = QFileInfo(file);
		s_tr = info.fileName();
		if (!strcmp(hp.data(), "0"))
		{
			if (if_group)
			protobuf_->send_normal_message(this_id, str_, image___, s_tr.toStdString(), group_name);
			else protobuf_->send_normal_message(this_id, str_, image___, s_tr.toStdString());
		}
		else
		{
			if (if_group)
			protobuf_->send_sound_message(this_id, image___, in.toStdString(), group_name);
			else protobuf_->send_sound_message(this_id, image___, in.toStdString());
			
		}
		image___.clear();
}
int chattext::set_messagefrom_friend(string time______, string text, string _image, string image_name, string name, bool is_record, bool is_my)
{
	if (!is_record)
	{
		char buff[10] = { '\0' };
		itoa(1, buff, 10);
		int i = strlen(buff);
		fwrite(buff, 1, strlen(buff), file_record);
		char bf[1024] = { 0 };
		//���+text+ͼƬ����+ʱ��\n
		string tex = text;
		if (if_group)
			tex += ";" + image_name + "$" + time______ + "#" + name + "\n";
		else
			tex += ";" + image_name + "$" + time______ + "#" + friend_detail[this_id]->name + "\n";
		fwrite(tex.data(), 1, tex.size(), file_record);
		fflush(file_record);
	}
	QString str;
	//��friend_detail��ȡ����
	if (!strcmp(name.data(), "0"))
	str = QString::fromStdString(friend_detail[this_id]->name);
	else
	str = QString::fromStdString(name);
	QString temp = QString("<font size=\"4\" color=blue>%1    %2: </font>")
		.arg(str).arg(QString::fromStdString(time______));
	QTextCharFormat fmt;
	fmt.setForeground(Qt::black);
	QTextCursor cursor1 = textedit->textCursor();
	cursor1.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
	cursor1.mergeCharFormat(fmt);
	textedit->mergeCurrentCharFormat(fmt);
	textedit->append(temp);
	QString str_ = QString::fromStdString(text);
	if (!strcmp(image_name.data(), "0"))
	{
		if (str_.isEmpty())
			return 0;
		//textedit->setTextBackgroundColor(Qt::black);
		textedit->append(str_);
		QTextCursor cursor1 = textedit->textCursor();
		cursor1.movePosition(QTextCursor::End);
		textedit->setTextCursor(cursor1);
		return 1;
	}
	string file_name__;
	if (strcmp(name.data(), "��\n"))
	{
		//string file_name__�������¶���һ��file_name
		file_name__ = "friend_message_image/" + image_name;
	}
	else
		file_name__ = image_name;
	if (!is_record)//���is_recordΪtrue
	{
		ofstream fd(file_name__, std::ios::out | std::ios::binary);
		fd.write(_image.data(), _image.size());
	}
	QUrl urr(QString::fromStdString(file_name__));
	QImage image = QImageReader(QString::fromStdString(file_name__)).read();
	if (image.width() > textedit->width())
	{
		image = image.scaled(textedit->width() / 3 * 2, image.height());
	}
	if (image.height() > textedit->height())
	{
		image = image.scaled(image.width(), textedit->height());
	}
	QTextDocument * textDocument = textedit->document();
	textDocument->addResource(QTextDocument::ImageResource, urr, QVariant(image));
	//QTextDocument * textDocument = lineedit_input->document();
	//textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(image));
	QTextCursor cursor = textedit->textCursor();
	QTextImageFormat imageFormat;
	imageFormat.setWidth(image.width());
	imageFormat.setHeight(image.height());
	imageFormat.setName(urr.toString());
	cursor.insertImage(imageFormat);

	textedit->append(QString::fromStdString(text));
	QTextCursor cursor2 = textedit->textCursor();
	cursor2.movePosition(QTextCursor::End);
	textedit->setTextCursor(cursor2);
	textedit_input->clear();
	urr.clear();
	is_image = 0;
	return 1;
}
void chattext::get_my_information()
{
	_information.birthday = friend_detail[this_id]->birthday;
	_information.is_online_ = friend_detail[this_id]->is_online_;
	_information.telephone = friend_detail[this_id]->telephone;
	_information.name = friend_detail[this_id]->name;
	_information.picture = friend_detail[this_id]->picture;
	_information.mymaxim = friend_detail[this_id]->mymaxim;
}




