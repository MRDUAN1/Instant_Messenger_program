#include "camera_recv.h"
#include <Windows.h>
//视频聊天端口3333，发送方用组播地址udp://234.5.6.7:3333，接收方发送端口5555，接受方组播地址udp://234.5.6.7:5555
#define snprintf _snprintf

SDL_Rect sdlRect;
SDL_Rect rect;
SDL_Surface *screen;
SDL_Overlay *bmp;
SDL_Thread *video_tid;
SDL_Event event;
Uint8  *audio_chunk;
Uint32  audio_len;
Uint8  *audio_pos;
int thread_exit;
void camera_recv::init_sdl(AVCodecContext*pVideoCodecCtx)
{
	out_buffer = (uint8_t *)av_malloc(avpicture_get_size(PIX_FMT_YUV420P, pVideoCodecCtx->width, pVideoCodecCtx->height));
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_YUV420P, pVideoCodecCtx->width, pVideoCodecCtx->height);
	screen_w = pVideoCodecCtx->width;
	screen_h = pVideoCodecCtx->height;

	screen = SDL_SetVideoMode(screen_w, screen_h, 0, 0);
	if (!screen) {
		printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		return;
	}
	bmp = SDL_CreateYUVOverlay(pVideoCodecCtx->width, pVideoCodecCtx->height, SDL_YV12_OVERLAY, screen);
}


void  camera_recv::fill_audio(void *udata, Uint8 *stream, int len){
	if (audio_len == 0)		/*  Only  play  if  we  have  data  left  */
		return;
	len = (len>audio_len ? audio_len : len);	/*  Mix  as  much  data  as  possible  */

	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
	audio_pos += len;
	audio_len -= len;

}
int camera_recv::sfp_refresh_thread(void *opaque){
	thread_exit = 0;
	while (!thread_exit) {
		SDL_Event event;
		event.type = SFM_REFRESH_EVENT;
		SDL_PushEvent(&event);
		SDL_Delay(0);
	}
	thread_exit = 0;
	//Break
	SDL_Event event;
	event.type = SFM_BREAK_EVENT;
	SDL_PushEvent(&event);

	return 0;
}
camera_recv::camera_recv()
{

}


camera_recv::~camera_recv()
{
}
int camera_recv::start_()
{
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (::WSAStartup(sockVersion, &wsaData) != 0)
	{
		exit(0);
	}
	av_register_all();
	AVCodec *pVideoCodec, *pAudioCodec;
	AVCodecContext *pVideoCodecCtx = NULL;
	AVCodecContext *pAudioCodecCtx = NULL;
	AVIOContext * pb = NULL;
	AVInputFormat *piFmt = NULL;
	AVFormatContext *pFmt = NULL;
	
	if (avformat_open_input(&pFmt, buff, NULL, NULL) < 0) {
		fprintf(stderr, "avformat open failed.\n");
		return -1;
	}
	else {
		fprintf(stdout, "open stream success!\n");
	}
	Sleep(100);
	if (avformat_find_stream_info(pFmt, NULL) < 0) {
		fprintf(stderr, "could not fine stream.\n");
		return -1;
	}
	av_dump_format(pFmt, 0, "", 0);
	int videoindex = -1;
	int audioindex = -1;
	for (int i = 0; i < pFmt->nb_streams; i++) {
		if ((pFmt->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) &&
			(videoindex < 0)) {
			videoindex = i;
		}
		if ((pFmt->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) &&
			(audioindex < 0)) {
			audioindex = i;
		}
	}

	if (videoindex < 0 || audioindex < 0) {
		fprintf(stderr, "videoindex=%d, audioindex=%d\n", videoindex, audioindex);
		return -1;
	}

	AVStream *pVst, *pAst;
	pVst = pFmt->streams[videoindex];
	pAst = pFmt->streams[audioindex];

	pVideoCodecCtx = pVst->codec;
	pAudioCodecCtx = pAst->codec;
	//init_AVCodecContext(pVideoCodecCtx);
	//init_AVCodecContext(pAudioCodecCtx);
	pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);
	if (!pVideoCodec) {
		fprintf(stderr, "could not find video decoder!\n");
		return -1;
	}
	if (avcodec_open2(pVideoCodecCtx, pVideoCodec, NULL) < 0) {
		fprintf(stderr, "could not open video codec!\n");
		return -1;
	}

	pAudioCodec = avcodec_find_decoder(pAudioCodecCtx->codec_id);
	if (!pAudioCodec) {
		fprintf(stderr, "could not find audio decoder!\n");
		return -1;
	}
	if (avcodec_open2(pAudioCodecCtx, pAudioCodec, NULL) < 0) {
		fprintf(stderr, "could not open audio codec!\n");
		return -1;
	}
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return -1;
	}
	AVFrame *pframe = av_frame_alloc();
	AVPacket pkt;
	av_init_packet(&pkt);
	pFrameYUV = av_frame_alloc();

	/*audio*/
	uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
	int out_nb_samples = 1024;
	AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
	int out_sample_rate = 44100;
	int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
	//Out Buffer Size
	int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);
	uint8_t *out_buffer1 = (uint8_t *)av_malloc(192000 * 2);

	wanted_spec.freq = out_sample_rate;
	wanted_spec.format = AUDIO_S16SYS;
	wanted_spec.channels = out_channels;
	wanted_spec.silence = 0;
	wanted_spec.samples = out_nb_samples;
	wanted_spec.callback = fill_audio;
	wanted_spec.userdata = pAudioCodecCtx;
	if (SDL_OpenAudio(&wanted_spec, NULL)<0){
		printf("can't open audio.\n");
		return -1;
	}
	int index = 0;
	//FIX:Some Codec's Context Information is missing
	int t = 0;
	video_tid = SDL_CreateThread(sfp_refresh_thread, NULL);
	AVFrame *fra;
	fra = avcodec_alloc_frame();
	int id = 0;
	int ret;
	int b = 0;
	struct SwrContext *au_convert_ctx;
	au_convert_ctx = swr_alloc();
	/*audio*/
	while (1) {
		SDL_WaitEvent(&event);
		if (event.type == SFM_REFRESH_EVENT){
			if (av_read_frame(pFmt, &pkt) >= 0) {
				if (t == 0)
				{
					t++;
					init_sdl(pVideoCodecCtx);
				}
				if (pkt.stream_index == videoindex) {
					avcodec_decode_video2(pVideoCodecCtx, pframe, &got_picture, &pkt);
					img_convert_ctx = sws_getContext(pVideoCodecCtx->width, pVideoCodecCtx->height, pVideoCodecCtx->pix_fmt,
						pVideoCodecCtx->width, pVideoCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
					if (got_picture) {
						sws_scale(img_convert_ctx, (const uint8_t* const*)pframe->data, pframe->linesize, 0, pVideoCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
						//SDL---------------------------
						SDL_LockYUVOverlay(bmp);
						bmp->pixels[0] = pFrameYUV->data[0];
						bmp->pixels[2] = pFrameYUV->data[1];
						bmp->pixels[1] = pFrameYUV->data[2];
						bmp->pitches[0] = pFrameYUV->linesize[0];
						bmp->pitches[2] = pFrameYUV->linesize[1];
						bmp->pitches[1] = pFrameYUV->linesize[2];
						SDL_UnlockYUVOverlay(bmp);
						rect.x = 0;
						rect.y = 0;
						rect.w = screen_w;
						rect.h = screen_h;
						//测试自己填充数据----------------
						SDL_DisplayYUVOverlay(bmp, &rect);
					}
				}
				else if (pkt.stream_index == audioindex) {
					int64_t in_channel_layout = av_get_default_channel_layout(pAudioCodecCtx->channels);

					if (b == 0)
					{

						au_convert_ctx = swr_alloc_set_opts(au_convert_ctx, out_channel_layout, out_sample_fmt, out_sample_rate,
							in_channel_layout, pAudioCodecCtx->sample_fmt, pAudioCodecCtx->sample_rate, 0, NULL);
						swr_init(au_convert_ctx);
						b++;
					}
					int frame_size = 192000 * 3 / 2;
					if (ret = avcodec_decode_audio4(pAudioCodecCtx, fra, &got_picture, &pkt) >= 0) {
						fprintf(stdout, "decode one audio frame!\r");
						swr_convert(au_convert_ctx, &out_buffer1, 192000, (const uint8_t **)fra->data, fra->nb_samples);

						//printf("index:%5d\t pts:%10d\t packet size:%d\n",index,packet->pts,packet->size);

						//FIX:FLAC,MP3,AAC Different number of samples
						if (wanted_spec.samples != fra->nb_samples){
							SDL_CloseAudio();
							out_nb_samples = fra->nb_samples;
							out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);
							wanted_spec.samples = out_nb_samples;
							SDL_OpenAudio(&wanted_spec, NULL);
						}
						index++;
					}
					audio_chunk = (Uint8 *)out_buffer1;
					//Audio buffer length
					audio_len = out_buffer_size;

					audio_pos = audio_chunk;
					//Play
					SDL_PauseAudio(0);
					while (audio_len>0)//Wait until finish
						SDL_Delay(1);
				}
				av_free_packet(&pkt);
			}
		}
	}
	av_free(buf);
	av_free(pframe);
	return 0;
}