#include <iostream>

#include <boost/locale.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <algorithm>

using namespace std;

string GetChineseString(wchar_t hex)
{
    char str[12] = {0};
    wchar_t wstr[] = {0, 0};
    wstr[0] = hex;
    setlocale(LC_ALL, "");
    wcstombs(str, wstr, sizeof(str)/sizeof(char));
    // printf("%s\n", str);
    string stp = str;
    // cout << stp << stp.size() << endl;

    return stp;
}


void Utf8TranferToGB2312(string src_string, string & dec_string)
{
    dec_string = boost::locale::conv::from_utf(src_string, "GB2312");
}

void GB2312TranferToUtf8(string src_string, string & dec_string)
{
    dec_string = boost::locale::conv::to_utf<char>(src_string, "GB2312");
}


std::string strToHex(std::string str, std::string separator = "")
{
    const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;
 
    for (std::string::size_type i = 0; i < str.size(); ++i)
        ss << hex[(unsigned char)str[i] >> 4] << hex[(unsigned char)str[i] & 0xf] << separator;
        // ss << hex[(unsigned char)str[i] & 0xf] << hex[(unsigned char)str[i] >> 4] << separator;

    std::string hex_str = ss.str();
    transform(hex_str.begin(), hex_str.end(), hex_str.begin(), ::tolower);

    return hex_str;
}

void GetSendString(string src_str, string &des_str)
{
    long long hex_val;
    des_str.clear();
    string tmp = strToHex(src_str);

    for (unsigned int i = 0; i < tmp.size() / 4; ++i) {
        string hex_str = tmp.substr(i * 4, 4);
        cout << hex_str << endl;
        string hex_h_str = hex_str.substr(2, 2);
        string hex_l_str = hex_str.substr(0, 2);
        string new_hex_str = hex_h_str + hex_l_str;
        cout << new_hex_str << endl;

        try {
            hex_val = strtoull(new_hex_str.c_str(), nullptr, 16);
            cout << hex_val << endl;
        } catch (...) {
            cout << "Get Send String failed" << endl;
            des_str = "";
            return;
        }

        if (hex_val > 20080) {
            des_str.append("f");
        } else {
            char tmp_buf[32];
            sprintf(tmp_buf, "%c", hex_val);
            string char_str = tmp_buf;
            des_str.append(char_str);
        }
    }

    return;
}




// int main(int argc, char const *argv[])
// {
//     // string text = "中国你好";
//     // string dec_string;
//     // cout << text << endl;
//     // Utf8TranferToGB2312(text, dec_string);
//     // cout << dec_string << endl;
//     // string tmp_dec_string;
//     // GB2312TranferToUtf8(dec_string, tmp_dec_string);
//     // cout << tmp_dec_string << endl;
//     // string mystr = "Tm氀";
//     // string un_str = "\\u" + strToHex(tmp);
//     // string fx = "\u4F60";

//     // printf("%X\n", '`');
//     // printf("%X\n", 'O');
//     // printf("%X\n", '}');
//     // printf("%X\n", 'Y');
//     // printf("%X\n", '`');
//     // printf("%X\n", 'O');
//     // printf("%X\n", '-');

    
//     // cout <<  mystr.size()  << " : " << strToHex(mystr) << endl;

//     // string myabc = "abcd";

//     // cout << myabc.size() << " : " << strToHex(myabc) << endl;
    
//     // std::cout << "\u4F60" << std::endl;
//     // string tp;
//     // char buf[32];
//     // sprintf(buf, "%S", fx.c_str());
//     // tp = buf;
//     // cout << tp << endl;

//     // wchar_t tmp = 0x4f60;

//     // cout << tmp << endl;

//     // char str[12];
//     // wchar_t wstr[] = { 0x4f60, 0x597d, 0x61, 0x4f60, 0 };
//     // // wchar_t wstr[] = { 0x5750, 0 };
//     // // wstr[0] = tmp;
//     // setlocale(LC_ALL, "");
//     // wcstombs(str, wstr, sizeof(str)/sizeof(char));
//     // // printf("%s\n", str);
//     // string stp = str;
//     // cout << stp << endl;

//     // string mystr = "*/jfiejfe";
    
//     // auto *buf = mystr.c_str();
//     // string pri_str;
//     // for (unsigned int i = 0; i < mystr.size(); ++i) {
//     //     pri_str.clear();
//     //     pri_str = buf[i];
//     //     cout << pri_str << endl;
//     // }

//     // string item_src_val = "PWޘ:gۓ";
//     // cout << item_src_val.size() << endl;

//     // string cn;
//     // string tmp_item_src_val;
//     // wchar_t myhex = 0x0;
//     // auto *buf = item_src_val.c_str();
//     // for (int i = 0; i < (item_src_val.size() / 2); i++) {
//     //     printf("HEX: %X HEX: %X ", buf[2*i], buf[2*i+1]);
//     //     myhex = (buf[2*i+1] & 0xff) << 8 | (buf[2*i] & 0xff);
//     //     printf(" %x ", myhex);

//     //     cn.append(GetChineseString(myhex));
//     // }
//     // printf("\n");
    
//     // cout << "Chinese: " << cn << endl;


//     // cout << strToHex(item_src_val) << endl;

//     // string arr1 = "ۓ";
//     // string arr2 = strToHex(arr1);
//     // cout << std::hex << arr2 << endl;

//     // char a = 0x32;

//     // cout << a << std::hex << endl;

//     // string f = "W";
//     // string m = "P";
//     // char a[1];
//     // char b[1];
//     // strcpy(a, f.c_str());
//     // strcpy(b, m.c_str());

//     // string tmp = "坐";
//     // printf("%x\n", tmp.c_str());
//     // cout << std::hex << tmp << endl;

    

//     return 0;
// }

int main(int argc, char const *argv[])
{
    // string str = "a\u0000b\u0000c\u0000d\u0000";

    // string des_str;
    // GetSendString(str, des_str);

    // cout << des_str << endl;

    // printf("%c\n", 0xbd4e);

    map<string, string> abc;
    abc["4e0b"] = "下";
    string mp = "4e0b";
    string tmp = abc[mp];
    cout << tmp << endl;

    return 0;
}
