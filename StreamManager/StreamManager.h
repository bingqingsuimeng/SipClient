#ifndef __STREAMMANAGER_H__
#define __STREAMMANAGER_H__

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE (8)

#define LOG(fmt, ...) fprintf(stdout, "[DEBUG] %s\n%s:%d:" fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

class CStreamManager
{
public:
    CStreamManager();
    ~CStreamManager();

    /**
    *   description:
    *       read length of data to buffer.
    */
    int read_data(void* op, unsigned char* buffer, int length);

    /**
    *   description:
    *       write data.
    */
    int write_data(unsigned char* data, int length);
private:
    unsigned char* m_stream_data_buffer;
    int m_stream_start_point;
    int m_stream_end_point;
    int m_capacity;
    int m_data_length;
};

#endif // !__STREAMMANAGER_H__

