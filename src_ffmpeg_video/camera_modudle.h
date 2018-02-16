#pragma once
class camera_modudle
{
public:
	camera_modudle();
	char* out_path;
	int exit_thread;
	int start();
	~camera_modudle();
};

