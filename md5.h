#ifndef MD5_H
#define MD5_H

#include <string>
using std::string;

class md5
{
public:
    md5();
    void mainLoop(unsigned int M[]);
    unsigned int* add(string str);
    string changeHex(int a);
    string getMD5(string source);//对psd进行md5加密
};

#endif // MD5_H
