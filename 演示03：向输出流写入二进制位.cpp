// 演示如何向输出流中写入二进制位
//
#include <iostream>
#include <string>
using namespace std;

struct BitOStream
{
    ostream *ostr;      // 指向目标输出流实例，为了避免C++语法的过多使用，这里用了指针。更合理的做法应该是用引用，在构造函数进行初始化。
    int bytebuffer;     // 字节缓冲，准备写入流的位要先写到字节缓冲中，当字节缓冲填满8个bit后，才将一个字节写入目标流中
    int bitmask;        // 位写入屏蔽字，准备写入bytebuffer的对应位为1，其他位为0
};

// 初始化指定的位输出流
int Init(BitOStream &bstr, ostream *ostr)
{
    bstr.ostr = ostr;
    bstr.bytebuffer = 0;
    bstr.bitmask = 0x80; // 从高位向低位写入，屏蔽字初始时字节最高位置1
    return 0;
}

// 向位输出流中写入一个bit
int Put(BitOStream &bstr, int bit)
{
    if (bit)
        bstr.bytebuffer |= bstr.bitmask; // 将1写入bytebuffer
    bstr.bitmask >>= 1;  // 屏蔽位右移到下一位
    if (bstr.bitmask == 0)
    {
        // 已填满一个字节，将字节写入目标流中，重置字节缓冲和屏蔽字
        bstr.ostr->put(bstr.bytebuffer);
        bstr.bytebuffer = 0;
        bstr.bitmask = 0x80;
    }
    return 0;
}

// 结束向位输出流中写入
int Over(BitOStream &bstr)
{
    if (bstr.bitmask != 0x80)
    {
        // 将未填满的最后一个字节写入目标流中
        bstr.ostr->put(bstr.bytebuffer);
    }
    return 0;
}

int main()
{
    BitOStream bstr;
    Init(bstr, &cout);   // 当向文件流输入时，将cout替换为文件流实例即可。
    
    // 演示向位输出流写出一组bit的过程
    string aBitString{"010000000100000101000010010000110100"};
    for(char ch:aBitString)
    {
        Put(bstr, ch == '1');
    }
    Over(bstr);
    
    return 0;
}