#ifndef __DEMUXER_H__
#define __DEMUXER_H__

#include "stdio.h"

#define __STDC_CONSTANT_MACROS

#ifdef _WIN32
//Windows
extern "C"
{
#include "libswscale/swscale.h"
#include "libavutil/opt.h"
#include "libavutil/imgutils.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include <libavformat/avio.h>
#include <libavutil/file.h>
#include <libavutil/mathematics.h>
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#ifdef __cplusplus
};
#endif
#endif

#define LOG(fmt, ...) fprintf(stdout, "[DEBUG] %s:\n%s:%d: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define MAX_FILE_NAME_LENGTH 60

//回调函数，使用ffmpeg解复用网络PS流时，ffmpeg需要通过该函数获取网络流。
typedef int(*callback_get_network_stream_fp)(void *opaque, uint8_t *buf, int buf_size);

/**
*   demux ps stream to es stream, using ffmpeg.
*/

class CDemuxer
{
public:
    CDemuxer() {}
    ~CDemuxer() {}

    void set_input_ps_file(char* file_name);
    void set_output_es_video_file(char* file_name);
    void set_output_es_audio_file(char* file_name);

    /**
    *   
    */
    bool demux_ps_to_es();

    bool demux_ps_to_es_network();

    static void setup_callback_function(callback_get_network_stream_fp func);
    static callback_get_network_stream_fp callback_get_network_stream;

private:
    char m_input_ps_file_name[MAX_FILE_NAME_LENGTH];
    char m_output_es_video_file_name[MAX_FILE_NAME_LENGTH];
    char m_output_es_audio_file_name[MAX_FILE_NAME_LENGTH];
};

#endif // !__DEMUXER_H__

