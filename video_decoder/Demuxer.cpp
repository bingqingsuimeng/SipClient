#include "Demuxer.h"

void CDemuxer::set_input_ps_file(char* file_name)
{
    memset(input_ps_file_name, 0x00, MAX_FILE_NAME_LENGTH);
    if (strlen(file_name) > 0)
    {
        sprintf_s(input_ps_file_name, MAX_FILE_NAME_LENGTH, "%s", file_name);
    }
}
void CDemuxer::set_output_es_video_file(char* file_name)
{
    memset(output_es_video_file_name, 0x00, MAX_FILE_NAME_LENGTH);
    if (strlen(file_name) > 0)
    {
        sprintf_s(output_es_video_file_name, MAX_FILE_NAME_LENGTH, "%s", file_name);
    }
}

void CDemuxer::set_output_es_audio_file(char* file_name)
{
    memset(output_es_audio_file_name, 0x00, MAX_FILE_NAME_LENGTH);
    if (strlen(file_name) > 0)
    {
        sprintf_s(output_es_audio_file_name, MAX_FILE_NAME_LENGTH, "%s", file_name);
    }
}

bool CDemuxer::demux_ps_to_es()
{
    AVInputFormat * av_input_formate = NULL;
    AVOutputFormat *av_output_formate = NULL;

    AVFormatContext *av_formate_context_input;
    AVFormatContext *av_formate_context_out_video = NULL;
    AVFormatContext *av_formate_context_out_audio = NULL;

    AVPacket av_packet;

    AVStream *in_stream_ps = NULL;
    AVStream *out_stream_es_video = NULL;
    AVStream *out_stream_es_audio = NULL;

    int videoindex = -1;
    int audioindex = -1;
    int frame_index = 0;

    int i_ret;

    av_formate_context_input = avformat_alloc_context();

    //打开一个输入流，并读取头信息。
    i_ret = avformat_open_input(&av_formate_context_input, input_ps_file_name, 0, NULL);
    if (i_ret < 0)
    {
        LOG("Open input file failed.");
        return false;
    }

    //获取媒体流信息
    i_ret = avformat_find_stream_info(av_formate_context_input, NULL);
    if (i_ret < 0)
    {
        LOG("Retrieve iniput stream info failed.");
        return false;
    }

    // 获取输出文件格式信息
    avformat_alloc_output_context2(&av_formate_context_out_video, NULL, NULL, output_es_video_file_name);
    if (!av_formate_context_out_video)
    {
        LOG("Create output context failed.");
        return false;
    }
    else
    {
        av_output_formate = av_formate_context_out_video->oformat;
    }

    // Open output file
    if (!(av_output_formate->flags & AVFMT_NOFILE))
    {
        if (avio_open(&av_formate_context_out_video->pb, output_es_video_file_name, AVIO_FLAG_WRITE) < 0)
        {
            LOG("Could not open output file '%s'", output_es_video_file_name);
            return false;
        }
    }

    //打开输出流
    out_stream_es_video = avformat_new_stream(av_formate_context_out_video, av_formate_context_out_video->video_codec);

    if (!out_stream_es_video)
    {
        LOG("Allocating output stream failed.");
        return false;
    }

    // Write file header
    if (avformat_write_header(av_formate_context_out_video, NULL) < 0)
    {
        LOG("Error occurred when opening video output file.");
        return false;
    }

    //获取视频流索引
    for (int i = 0; i < av_formate_context_input->nb_streams; ++i)
    {
        in_stream_ps = av_formate_context_input->streams[i];

        if (AVMEDIA_TYPE_VIDEO == in_stream_ps->codecpar->codec_type)
        {
            videoindex = i;
        }
        else
        {
            break;
        }
    }

    frame_index = 0;

    while (1)
    {
        // Get an AVPacket
        if (av_read_frame(av_formate_context_input, &av_packet) < 0)
        {
            LOG("end of file!\n");
            break;
        }

        if (videoindex == av_packet.stream_index)
        {
            out_stream_es_video = av_formate_context_out_video->streams[0];
            LOG("Write Video Packet. size: %d\t pts: %d\n", av_packet.size, av_packet.pts);
        }
        else
        {
            continue;
        }

        // Write
        if (av_interleaved_write_frame(av_formate_context_out_video, &av_packet) < 0)
        {
            LOG("Error when write_frame.");
            break;
        }

        LOG("Write %8d frames to output file.", frame_index);

        av_packet_unref(&av_packet);

        ++frame_index;
    }

    avformat_free_context(av_formate_context_out_video);
    avformat_free_context(av_formate_context_input);

    return true;
}