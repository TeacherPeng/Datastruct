// 演示如何查看二进制文件中的字节内容
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// 以16字节为一行，输出指定的字节块
int ShowBytes(char *aBytes, int aByteCount, int aOffset)
{
    // 输出列序号行
    cout << "         00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" << endl;

    // 每16个字节输出一行
    for (int i = 0; i < aByteCount; i += 16)
    {
        // 输出行起始偏移量
        cout << hex << setw(8) << setfill('0') << (aOffset + i) << ' ';
        // 输出16个字节
        for (int j = 0; j < 16 && i + j < aByteCount; j++)
        {
            cout << hex << setw(2) << setfill('0') << (unsigned int)(unsigned char)aBytes[i + j] << ' ';
        }
        cout << endl;
    }
    return 0;
}

int ShowHelp()
{
    cout << "Usage: demo04 filename [offset]" << endl;
    cout << "  Example: demo04 test.dat" << endl;
    cout << "  Example: demo04 test.dat 1024" << endl;
    return 0;
}

int main(int argc, char *argv[])
{
    // 分析命令行参数
    if (argc != 2 && argc != 3)
    {
        ShowHelp();
        return 1;
    }

    // 提取命令行参数（目标文件名、读取位置）
    string aFileName{argv[1]};
    int aOffset = argc == 3 ? atoi(argv[2]) : 0;

    // 打开文件
    ifstream istr(aFileName, ios::in | ios::binary);
    if (!istr)
    {
        cerr << "Open file " << aFileName << " failure." << endl;
        return 2;
    }

    // 定位到要读取的位置
    istr.seekg(aOffset);

    // 读取文件中的指定大小字节块
    const int BUFFERSIZE = 320; // 20行*16列
    char aBytes[BUFFERSIZE];
    istr.read(aBytes, BUFFERSIZE);

    // 查询实际读入字节数
    int aByteCount = istr.gcount();

    // 文件流使用完毕要关闭
    istr.close();

    // 显示读入的字节块
    ShowBytes(aBytes, aByteCount, aOffset);

    return 0;
}