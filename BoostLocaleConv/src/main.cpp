#include <iostream>

#include <boost/locale.hpp>

using namespace std;


void Utf8TranferToGB2312(string src_string, string & dec_string)
{
    dec_string = boost::locale::conv::from_utf(src_string, "GB2312");
}

void GB2312TranferToUtf8(string src_string, string & dec_string)
{
    dec_string = boost::locale::conv::to_utf<char>(src_string, "GB2312");
}


int main(int argc, char const *argv[])
{
    string text = "中国你好";
    string dec_string;
    cout << text << endl;
    Utf8TranferToGB2312(text, dec_string);
    cout << dec_string << endl;
    string tmp_dec_string;
    GB2312TranferToUtf8(dec_string, tmp_dec_string);
    cout << tmp_dec_string << endl;

    return 0;
}
