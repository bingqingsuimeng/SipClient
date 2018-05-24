#ifndef __PSPACKETPARSER_H__
#define __PSPACKETPARSER_H__

/**
*   功能：
*       从RTP负载中解析PS包，将若干个RTP负载中的PS包组成完整的一帧数据，存放在PS包数据仓库中，供后续
*       业务使用。
*/

class CPsPacketParser
{
public:
    CPsPacketParser();
    ~CPsPacketParser();

private:

};

#endif // !__PSPACKETPARSER_H__

