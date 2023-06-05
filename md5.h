#ifndef MD5_H
#define MD5_H

#include <string>
using std::string;

class md5
{
public:
    //构造函数，用于初始化类的成员变量
    md5();

    /*MD5主循环函数，用于处理每个512位的分组。
    根据索引 i 的不同值，选择不同的运算方式，并更新临时变量。*/
    void mainLoop(unsigned int M[]);

    unsigned int* add(string str);//填充函数，将输入的字符串填充为64字节的整数倍，并添加长度信息。

    string changeHex(int a);//将整数转换为16进制字符串表示。

    /*计算给定字符串的MD5哈希值。初始化临时变量并调用 add 函数对输入字符串进行填充，
    然后通过 mainLoop 处理每个512位分组，最后将结果转换为16进制字符串形式并返回。*/
    string getMD5(string source);
};

#endif // MD5_H
