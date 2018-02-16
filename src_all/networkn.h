#pragma once
#include "include\event.h"
#include "include\event2\bufferevent.h"
#include "protobuf_client.h"
#include <string>
#include <qobject.h>
#include <thread.h>
#include <qthread.h>
using namespace std;
class protobuf_client;
class protobuf_callback;		
class networkn:public QObject
{
	Q_OBJECT
public:
	networkn();
	~networkn();
	void exit_network();
	static void write(string data);
	void handle_udp_message(string data);
	static void recvfromclient(void*);
	//0Ϊ������Ƶ��Ƶ,1Ϊ������Ƶrecv
	void directSendFriend(string address, int port, int type, int is_ok);
	void begin_thread(void *);
	//Ĭ��iΪ0����Ĭ�Ͻ�����ͨ�ļ�����i��Ϊ0ʱ����download�ļ�
	void file_recive(int i = 0);
	void send_file();
	void start(string data, string data_1);
	static void read_event(struct bufferevent *bev, void *ct);
	static void read_event1(void*);
	static void init_tcp_socket(void *);
	void start_connect(string data);
	public slots:
	void udp_ack_();

};

