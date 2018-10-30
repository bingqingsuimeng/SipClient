#include "Demuxer2.h"
#include <fstream>

int CDemuxer2::find_next_hx_str(unsigned char* source, int source_length, unsigned char* seed, int seed_length)
{
    if (source && seed)
    {
    }
    else
    {
        //failure
        return 0;
    }

    unsigned char* pHeader = source + seed_length;

    int total_length = source_length;
    int processed_length = 0;

    int src_offset = 0;
    while (total_length - processed_length >= seed_length)
    {
        for (int i = 0; i < seed_length && (pHeader[i] == seed[i]); i++)
        {
            if (seed_length - 1 == i)
            {
                //find ok
                return seed_length + processed_length;
            }
        }

        processed_length++;
        pHeader = source + seed_length + processed_length;
    }

    return 0;
}


int CDemuxer2::deal_ps_packet(unsigned char * packet, int length)
{
    int ps_packet_header_stuffed_size;
    int pes_system_header_header_length;
    int pes_program_stream_map_length;
    int pes_video_h264_packet_size;
    int pes_video_h264_packet_stuffed_size;

    int packet_total_length = length;
    int packet_processed_length = 0;

    ps_packet_header* ps_head = NULL;
    pes_system_header_packet_header_t* pes_system_header;
    pes_program_stream_map_packet_header_t* pes_psm_header;
    pes_media_packet_header_t* pes_video_h264_packet_header;
    pes_media_packet_header_t* pes_audio_packet_header;

    unsigned char* next_pes_packet = NULL;

    littel_endian_size_u tmp_size;

    // deal with ps packet header.
    if (packet[0] == 0x00
        && packet[1] == 0x00
        && packet[2] == 0x01
        && packet[3] == 0xba)
    {
        //ps_head = (ps_packet_header_t*)packet;
        //从ps包头第14个字节的最后3位获取头部填充数据的长度
        ps_packet_header_stuffed_size = packet[13] & 0x07;

        //+14的原因是表示填充数据的长度位是PS包头部的第14个字节的后3位说明。
        //不使用sizeof计算PS包头部长度的原因是结构体内部会发生自动对齐，导致该结果不准确。
        packet_processed_length += 14 + ps_packet_header_stuffed_size;

        next_pes_packet = packet + packet_processed_length;

        while (next_pes_packet && (packet_total_length - packet_processed_length >= 0))
        {
            if (next_pes_packet
                && next_pes_packet[0] == 0x00
                && next_pes_packet[1] == 0x00
                && next_pes_packet[2] == 0x01
                && next_pes_packet[3] == 0xbb)
            {
                //this pes packet is system_header or psm, which data is not usefull for es_h264
                pes_system_header = (pes_system_header_packet_header_t*)next_pes_packet;

                littel_endian_size_u tmp_size;
                tmp_size.byte[0] = pes_system_header->header_length.byte[1];
                tmp_size.byte[1] = pes_system_header->header_length.byte[0];

                pes_system_header_header_length = tmp_size.length;

                // +6的原因是pes_packet_header_t中长度字节之前还有6个字节
                packet_processed_length += (6 + pes_system_header_header_length);

                next_pes_packet = packet + packet_processed_length;
            }
            else if (next_pes_packet
                && next_pes_packet[0] == 0x00
                && next_pes_packet[1] == 0x00
                && next_pes_packet[2] == 0x01
                && next_pes_packet[3] == 0xbc)
            {
                //this pes packet is program stream map, which data is not usefull for es_h264
                pes_psm_header = (pes_program_stream_map_packet_header_t*)next_pes_packet;


                tmp_size.byte[0] = pes_psm_header->program_stream_map_length.byte[1];
                tmp_size.byte[1] = pes_psm_header->program_stream_map_length.byte[0];

                pes_program_stream_map_length = tmp_size.length;

                // +6的原因是pes_packet_header_t中自动填充数据之前有6个字节
                packet_processed_length += 6 + pes_program_stream_map_length;

                next_pes_packet = packet + packet_processed_length;
            }

            else if (next_pes_packet
                && next_pes_packet[0] == 0x00
                && next_pes_packet[1] == 0x00
                && next_pes_packet[2] == 0x01
                && next_pes_packet[3] == 0xe0)
            {
                //contain video es stream
                pes_video_h264_packet_header = (pes_media_packet_header_t*)next_pes_packet;

                //littel_endian_size_u tmp_size;
                tmp_size.byte[0] = pes_video_h264_packet_header->packet_size.byte[1];
                tmp_size.byte[1] = pes_video_h264_packet_header->packet_size.byte[0];

                pes_video_h264_packet_size = tmp_size.length;
                pes_video_h264_packet_stuffed_size = pes_video_h264_packet_header->PES_header_data_length;

                // +9 的原因是pes_video_h264_packet_stuffed_size之前还有9个字节的头部数据
                // +6 的原因是pes包的总长度是在头部之后第6个字节处得到的。
                write_media_data_to_file(dst_es_video_filename,
                    next_pes_packet + 9 + pes_video_h264_packet_stuffed_size,
                    pes_video_h264_packet_size + 6 - 9 - pes_video_h264_packet_stuffed_size);

                packet_processed_length += 6 + pes_video_h264_packet_size;
                next_pes_packet = packet + packet_processed_length;
            }

            else if (next_pes_packet
                && next_pes_packet[0] == 0x00
                && next_pes_packet[1] == 0x00
                && next_pes_packet[2] == 0x01
                && next_pes_packet[3] == 0xc0)
            {
                //contain audio es stream
                pes_audio_packet_header = (pes_media_packet_header_t*)next_pes_packet;
            }
            else
            {
                // bad data
                break;
            }
            if (packet_total_length - packet_processed_length < 0)
            {
                LOG("error, please check if src ps file formate is right\n");
                return packet_total_length;
            }
        }

    }
    else
    {
        return 0;
    }

    return packet_processed_length;
}

void CDemuxer2::write_media_data_to_file(char* file_name, void* pLog, int nLen)
{
    FILE* m_pLogFile = NULL;
    if (pLog != NULL && nLen > 0)
    {
        if (NULL == m_pLogFile && strlen(file_name) > 0)
        {
            //一定要以二进制方式打开文件，不然在Windows平台输出文件时会将“换行”转换成“回车+换行”，导致文件出错
            ::fopen_s(&m_pLogFile, file_name, "ab+");
        }

        if (m_pLogFile != NULL)
        {
            ::fwrite(pLog, nLen, 1, m_pLogFile);
            ::fflush(m_pLogFile);
            ::fclose(m_pLogFile);
            m_pLogFile = NULL;
        }
    }
}

int CDemuxer2::do_demux()
{
    int buffer_capacity = MAX_BUFFER_SIZE;      //buffer 总容量
    int buffer_size = 0;                        //buffer 中当前数据大小
    int processed_size = 0;                     //已经解析完的缓存数据大小
    int buffer_left_size = MAX_BUFFER_SIZE;     //缓存区剩余大小
    int read_size = 0;
    int next_ps_packet_offset = 0;              //缓存中下一个ps包的位移

    int ps_packet_length = 0;                   //ps包长度

    bool is_end_of_file = false;

    unsigned char* stream_data_buf = NULL;
    unsigned char* tmp_data_buf = NULL;

    stream_data_buf = (unsigned char*)malloc(MAX_BUFFER_SIZE);
    memset(stream_data_buf, 0x00, MAX_BUFFER_SIZE);

    tmp_data_buf = (unsigned char*)malloc(MAX_BUFFER_SIZE);
    memset(tmp_data_buf, 0x00, MAX_BUFFER_SIZE);

    unsigned char ps_packet_start_code[4];
    ps_packet_start_code[0] = 0x00;
    ps_packet_start_code[1] = 0x00;
    ps_packet_start_code[2] = 0x01;
    ps_packet_start_code[3] = 0xba;

    //buffer_left_size = MAX_BUFFER_SIZE;

    do {
        ps_packet_length = find_next_hx_str(stream_data_buf + next_ps_packet_offset,
            MAX_BUFFER_SIZE - next_ps_packet_offset,
            ps_packet_start_code, 4);

        if (0 != ps_packet_length)
        {
            //查找PS包成功, 开始处理
            processed_size += deal_ps_packet(stream_data_buf + next_ps_packet_offset, ps_packet_length);

            next_ps_packet_offset += ps_packet_length;
            //buffer_left_size = processed_size;
        }
        else
        {
            //查找失败
            if (0 == processed_size && (buffer_size == buffer_capacity))
            {
                //缓冲区太小
                LOG("buffer is too small.\n");
                return -1;
            }
            else 
            {
                //缓冲区足够，缓冲区中剩余的数据不足一整个PS packet， 需要重新读取文件
                if (is_end_of_file)
                {
                    //处理最后缓存中的数据, 如果不做处理则丢失最后一个PS包数据
                    deal_ps_packet(stream_data_buf + processed_size, MAX_BUFFER_SIZE - processed_size);
                    break;
                }

                //查找失败，但文件未读完，则继续读文件
                //第一步：将缓存中剩余数据移动到缓存最前端；
                memset(tmp_data_buf, 0x00, MAX_BUFFER_SIZE);
                memcpy(tmp_data_buf, stream_data_buf + processed_size, MAX_BUFFER_SIZE - processed_size);

                memset(stream_data_buf, 0x00, MAX_BUFFER_SIZE);
                memcpy(stream_data_buf, tmp_data_buf, MAX_BUFFER_SIZE - processed_size);

                next_ps_packet_offset = 0;
                buffer_left_size += processed_size;
                processed_size = 0;

                //第二步：读取文件数据将缓存区填满。
                read_size = ::fread_s(stream_data_buf + (MAX_BUFFER_SIZE - buffer_left_size), buffer_left_size, 1, buffer_left_size, m_pf_ps_file);
                buffer_size = read_size;

                buffer_left_size -= read_size;
                if (buffer_left_size > 0)
                {
                    LOG("end of file.\n");
                    is_end_of_file = true;
                    continue;
                }
            }
        }
    } while (true);

    //release memory
    if (NULL != stream_data_buf)
    {
        free(stream_data_buf);
    }

    if (NULL != tmp_data_buf)
    {
        free(tmp_data_buf);
    }

    return 0;
}

void CDemuxer2::setup_src_ps_file(char* filename)
{
    memset(src_ps_filename, 0x00, MAX_FILENAME_LENGTH);
    if (strlen(filename) > 0)
    {
        sprintf_s(src_ps_filename, MAX_FILENAME_LENGTH, "%s", filename);
    }
}

void CDemuxer2::setup_dst_es_video_file(char* filename)
{
    memset(dst_es_video_filename, 0x00, MAX_FILENAME_LENGTH);
    if (strlen(filename) > 0)
    {
        sprintf_s(dst_es_video_filename, MAX_FILENAME_LENGTH, "%s", filename);
    }
}

void CDemuxer2::setup_dst_es_audio_file(char* filename)
{
    memset(dst_es_audio_filename, 0x00, MAX_FILENAME_LENGTH);
    if (strlen(filename) > 0)
    {
        sprintf_s(dst_es_audio_filename, MAX_FILENAME_LENGTH, "%s", filename);
    }
}

bool CDemuxer2::open_src_ps_file()
{
    //open ps file
    errno_t err;
    err = ::fopen_s(&m_pf_ps_file, src_ps_filename, "rb");
    if (err == 0)
    {
        printf("The file '%s' was opened\n", src_ps_filename);
    }
    else
    {
        printf("The file '%s' was not opened\n", src_ps_filename);
    }
    return (0 == err);
}
bool CDemuxer2::close_src_ps_file()
{
    // close ps file 
    errno_t err = 0;
    if (m_pf_ps_file)
    {
        err = fclose(m_pf_ps_file);
        if (err == 0)
        {
            printf("The file '%s' was closed\n", src_ps_filename);
        }
        else
        {
            printf("The file '%s' was not closed\n", src_ps_filename);
        }
    }
    return (0 == err);
}