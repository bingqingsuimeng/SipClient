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

private:
    char input_ps_file_name[MAX_FILE_NAME_LENGTH];
    char output_es_video_file_name[MAX_FILE_NAME_LENGTH];
    char output_es_audio_file_name[MAX_FILE_NAME_LENGTH];
};

#endif // !__DEMUXER_H__

