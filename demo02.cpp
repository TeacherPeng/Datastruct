#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: demo02 sourcefilename destfilename" << endl;
        return 0;
    }

    // 打开输入文件流
    ifstream instr(argv[1], ios::in | ios::binary);
    if (!instr)
    {
        cerr << "Open " << argv[1] << " failure." << endl;
        return 0;
    }

    // 打开输出文件流
    ofstream outstr(argv[2], ios::out | ios::binary);
    if (!outstr)
    {
        cerr << "Create " << argv[2] << " failure." << endl;
        instr.close();
        return 0;
    }

    // 从输入文件流逐字节读入，并写到输出文件流中
    while (!instr.eof())
    {
        int ch = instr.get();
        if (ch != EOF) outstr.put(ch);
    }

    // 关闭文件流
    instr.close();
    outstr.close();

    return 0;
}