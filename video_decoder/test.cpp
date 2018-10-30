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

SwsContext*		 m_pSwsCtx;
AVCodec*		 p_av_codec; //½âÂëÆ÷
AVCodecContext*  p_av_codec_context;

#define LOG(fmt, ...) fprintf(stdout, "[DEBUG] %s:%s:%d: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

int InitDecoder()
{
    int nError;
    p_av_codec = avcodec_find_decoder(AV_CODEC_ID_H264);

    if (p_av_codec == NULL)
    {
        return -1;
    }

    p_av_codec_context = avcodec_alloc_context3(p_av_codec);
    if (NULL == p_av_codec_context)
    {
        return -1;
    }

    nError = avcodec_open2(p_av_codec_context, p_av_codec, NULL);

    if (nError != 0)
    {
        avcodec_close(p_av_codec_context);
        avcodec_free_context(&p_av_codec_context);
        p_av_codec_context = NULL;
    }
    return 0;
}

int test(int argc, char* argv[])
{
        AVOutputFormat *ofmt_a = NULL;
        AVOutputFormat *ofmt_v = NULL;
    
        AVFormatContext *ifmt_ctx = NULL;
        AVFormatContext *ofmt_ctx = NULL;
        AVFormatContext *ofmt_ctx_a = NULL;
        AVFormatContext *ofmt_ctx_v = NULL;
    
        AVPacket pkt;
    
        int ret = 0;
        int i = 0;
        int videoindex = -1;
        int audioindex = -1;
        int frame_index = 0;
    
        AVStream *in_stream = NULL;
        AVStream *out_stream = NULL;
    
        char *in_filename = "E://tmp1.ps"; // Input file URL
        char *out_filename_v = "E://tmp1.h264"; // Output file URL
        char *out_filename_a = "E://output.aac";
    
        av_register_all();
    
        // Input
        if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0)) < 0) 
        {
            LOG("Open input file failed.");
            goto end;
        }
    
        if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) 
        {
            LOG("Retrieve iniput stream info failed.");
            goto end;
        }
    
        // Output
        avformat_alloc_output_context2(&ofmt_ctx_v, NULL, NULL, out_filename_v);
        if (!ofmt_ctx_v) 
        {
            LOG("Create output context failed.");
            ret = AVERROR_UNKNOWN;
            goto end;
        }
        ofmt_v = ofmt_ctx_v->oformat;
    
        avformat_alloc_output_context2(&ofmt_ctx_a, NULL, NULL, out_filename_a);
        if (!ofmt_ctx_a) 
        {
            LOG("Create output context failed.");
            ret = AVERROR_UNKNOWN;
            goto end;
        }
        ofmt_a = ofmt_ctx_a->oformat;
    
        for (i = 0; i < ifmt_ctx->nb_streams; ++i) 
        {
            // Create output AVStream according to input AVStream
            in_stream = ifmt_ctx->streams[i];
    
            if (AVMEDIA_TYPE_VIDEO == ifmt_ctx->streams[i]->codec->codec_type) 
            {
                videoindex = i;
                out_stream = avformat_new_stream(ofmt_ctx_v, in_stream->codec->codec);
                ofmt_ctx = ofmt_ctx_v;
            }
            else if (AVMEDIA_TYPE_AUDIO == ifmt_ctx->streams[i]->codec->codec_type) 
            {
                audioindex = i;
                out_stream = avformat_new_stream(ofmt_ctx_a, in_stream->codec->codec);
                ofmt_ctx = ofmt_ctx_a;
            }
            else 
            {
                break;
            }
    
            if (!out_stream) 
            {
                LOG("Allocating output stream failed.");
                ret = AVERROR_UNKNOWN;
                goto end;
            }
    
            // Copy the settings of AVCodecContext
            if (avcodec_copy_context(out_stream->codec, in_stream->codec) < 0) 
            {
                LOG("Copy context from input to output stream codec context.");
                goto end;
            }
    
            out_stream->codec->codec_tag = 0;
    
            if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER) 
            {
                //out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
            }
        }
    
        // Dump Format
        LOG("Input Video Start!");
        av_dump_format(ifmt_ctx, 0, in_filename, 0);
        LOG("Output Video Start!");
        av_dump_format(ofmt_ctx_v, 0, out_filename_v, 1);
        LOG("Output Audio Start!");
        av_dump_format(ofmt_ctx_a, 0, out_filename_a, 1);
        LOG("Dump End");
    
        // Open output file
        if (!(ofmt_v->flags & AVFMT_NOFILE))
        {
            if (avio_open(&ofmt_ctx_v->pb, out_filename_v, AVIO_FLAG_WRITE) < 0) 
            {
                LOG("Could not open output file '%s'", out_filename_v);
                goto end;
            }
        }
    
        if (!(ofmt_a->flags & AVFMT_NOFILE))
        {
            if (avio_open(&ofmt_ctx_a->pb, out_filename_a, AVIO_FLAG_WRITE) < 0)
            {
                LOG("Could not open output file '%s'", out_filename_a);
                goto end;
            }
        }
    
        // Write file header
        if (avformat_write_header(ofmt_ctx_v, NULL) < 0)
        {
            LOG("Error occurred when opening video output file.");
            goto end;
        }
    
        if (avformat_write_header(ofmt_ctx_a, NULL) < 0)
        {
            LOG("Error occurred when opening audio output file.");
            goto end;
        }
    
    #if USE_H264BSF
        AVBitSreamFilterContext* h264bsfc = av_bitstream_filter_init("h264_mp4toannexb");
    #endif
    
        frame_index = 0;
    
        while (1)
        {
            // Get an AVPacket
            if (av_read_frame(ifmt_ctx, &pkt) < 0) 
            {
                break;
            }
    
            in_stream = ifmt_ctx->streams[pkt.stream_index];
    
            if (videoindex == pkt.stream_index)
            {
                out_stream = ofmt_ctx_v->streams[0];
                ofmt_ctx = ofmt_ctx_v;
                LOG("Write Video Packet. size: %d\t pts: %d\n", pkt.size, pkt.pts);
    #if USE_H264BSF
                av_bitstream_filter_filter(h264bsfc, in_stream->codec, NULL, &pkt.data, &pkt.size, pkt.data, pkt.size, 0);
    #endif
            }
            else if (audioindex == pkt.stream_index) 
            {
                out_stream = ofmt_ctx_a->streams[0];
                ofmt_ctx = ofmt_ctx_a;
                LOG("Write Audio Packet. size: %d\t pts: %d\n", pkt.size, pkt.pts);
            }
            else 
            {
                continue;
            }
    
            // Copy Packet
            // Convert PTS/DTS
            pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
            pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
            pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
            pkt.pos = -1;
            pkt.stream_index = 0;
    
            // Write
            if (av_interleaved_write_frame(ofmt_ctx, &pkt) < 0) 
            {
                LOG("Error muxing packet.");
                break;
            }
    
            LOG("Write %8d frames to output file.", frame_index);
            av_free_packet(&pkt);
            ++frame_index;
        }
    
    #if USE_H264BSF
        av_bitstream_filter_close(h264bsfc);
    #endif
    
        // Write file trailer
        av_write_trailer(ofmt_ctx_a);
        av_write_trailer(ofmt_ctx_v);
    
    end:
        avformat_close_input(&ifmt_ctx);
    
        // close output
        if (ofmt_ctx_a && !(ofmt_a->flags & AVFMT_NOFILE))
        {
            avio_close(ofmt_ctx_a->pb);
        }
    
        if (ofmt_ctx_v && !(ofmt_v->flags & AVFMT_NOFILE))
        {
            avio_close(ofmt_ctx_v->pb);
        }
    
        avformat_free_context(ofmt_ctx_a);
        avformat_free_context(ofmt_ctx_v);
    
        if (ret < 0 && ret != AVERROR_EOF) 
        {
            LOG("Error occurred.");
            return -1;
        }
    
        return 0;
}