#include "StreamManager.h"

CStreamManager* CStreamManager::m_instance = NULL;

CStreamManager::CStreamManager()
{
    m_capacity = MAX_BUFFER_SIZE;
    m_stream_data_buffer = (unsigned char*)malloc(m_capacity);

    m_data_length = 0;
}

CStreamManager::~CStreamManager()
{
    if (NULL != m_stream_data_buffer)
    {
        free(m_stream_data_buffer);
    }
}

int CStreamManager::read_data(void* op, unsigned char* buffer, int length)
{
    if (NULL == buffer || NULL == m_stream_data_buffer)
    {
        return 0;
    }

    if (length > m_data_length)
    {
        LOG("stream manager don't have enough data.\n");
        return 0;
    }


    int i = 0;
    for (; i < length && 0 < m_data_length; i++)
    {
        buffer[i] = m_stream_data_buffer[m_stream_start_point++];

        m_data_length--;
        m_stream_start_point %= m_capacity;
    }

    return i;
}


int CStreamManager::write_data(unsigned char* data, int length)
{
    if (NULL == data || NULL == m_stream_data_buffer)
    {
        return 0;
    }

    if (length > m_capacity - m_data_length)
    {
        LOG("stream manager don't have enough space.\n");
        return 0;
    }

    int i = 0;
    for (; i < length && m_data_length < m_capacity; i++)
    {
        m_stream_data_buffer[m_stream_end_point++] = data[i];

        m_data_length ++;
        m_stream_end_point %= m_capacity;
    }
}