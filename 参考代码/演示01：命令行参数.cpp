// 演示如何使用命令行参数
//
#include <iostream>
#include <cstring>
using namespace std;

// 显示使用说明
int ShowHelp()
{
    cout << "Usage: demo01 [-z|-x] sourcefile destfile" << endl;
    cout << "    -z means zip sourcefile to destfile, -x means extract sourcefile to destfile." << endl;
    return 0;
}

// 带命令行参数的main函数
int main(int argc, char *argv[])
{
    cout << "命令行参数：" << endl;
    for (int i = 0; i < argc; i++)
    {
        cout << "arg[" << i << "]: " << argv[i] << endl;
    }

    // 检查命令行参数，如果没有读到所需要的命令行参数，提示使用说明
    if (argc != 4)
    {
        ShowHelp();
    }
    else if (stricmp(argv[1], "-z") == 0)
    {
        cout << "Zip " << argv[2] << " to " << argv[3] << " ..." << endl;
    }
    else if (stricmp(argv[1], "-x") == 0)
    {
        cout << "Extract " << argv[2] << " to " << argv[3] << " ..." << endl;
    }
    else
    {
        ShowHelp();
    }

    return 0;
}