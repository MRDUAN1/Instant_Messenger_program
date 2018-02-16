#pragma once
#include <Windows.h>
extern "C"
{
#include "libavutil/opt.h"
#include "libavutil/time.h"
#include "libavutil/mathematics.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavutil/audio_fifo.h"
#include "include\sdl\SDL.h"
};
#pragma comment(lib, "lib/avutil.lib")
#pragma comment(lib, "lib/avcodec.lib")
#pragma comment(lib, "lib/avformat.lib")

#pragma comment(lib, "lib/avdevice.lib")
#pragma comment(lib, "lib/swresample.lib")

#pragma comment(lib, "lib/avfilter.lib")
#pragma comment(lib, "lib/SDL.lib")
#pragma comment(lib, "lib/swscale.lib")
class camera_recv
{
public:
	camera_recv();
	char *buff;
	int start_();
	~camera_recv();
private:
#define SFM_REFRESH_EVENT  (SDL_USEREVENT + 1)
#define SFM_BREAK_EVENT  (SDL_USEREVENT + 2)
	uint8_t *out_buffer;
	int screen_w, screen_h;
	
	struct SwsContext *img_convert_ctx;
	AVFrame	 *pFrameYUV;
	int got_picture;
	unsigned char samples[192000 * 3 / 2];
	SDL_AudioSpec wanted_spec;
	unsigned char *buf;
	
	
private:
	void init_sdl(AVCodecContext*pVideoCodecCtx);
	static void  fill_audio(void *udata, Uint8 *stream, int len);
	static int sfp_refresh_thread(void *opaque);
};

