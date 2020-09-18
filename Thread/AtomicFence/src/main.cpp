#include <iostream>
#include <thread>
#include <exception>
#include <atomic>
#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <vector>

#include "atomic_fence.hpp"
#include "bool_atomic_fence.hpp"


typedef struct _zero_array
{
    uint8_t item_type;
    uint8_t value_type;
    uint8_t id_size;
    uint8_t value_size;
    char value[0];
}__attribute((packed)) ItemContent;

using namespace std;

#define NORCHART_SETPUSHMETHOD_FUNCTION     "SetPushMethod"

#define FLEXEM_PUSH_MODE                    "flexem_push_mode"

std::string IntToHexStr(int w) {
    size_t hex_len = 8;
    if (w == 0) {
        return "0x80000000";
    }
    static const char* digits = "0123456789ABCDEF";
    std::string rc(hex_len, '0');
    for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
        rc[i] = digits[(w >> j) & 0x0f];
    rc.erase(0, 1);
    return ("0x8" + rc);
}

template< typename T >
std::string int_to_hex( T i )
{
  std::stringstream stream;
  stream << "0x" 
         << std::setfill ('0') << std::setw(sizeof(T)*2) 
         << std::hex << i;
  return stream.str();
}

int main(int argc, char const *argv[])
{
    // AtomicFence atomic_fence;
    
    // atomic_fence.Run();

    // BoolAtomicFence bool_atomic_fence;
    
    // bool_atomic_fence.Run();

    // std::stringstream ss;
    // std::string s;
    // int i = 0;
    // uint8_t j = 255;

    // ss << std::hex << i;
    // s = ss.str();

    // std::cout << IntToHexStr(i) << std::endl;
    // std::cout << IntToHexStr(j) << std::endl;

    // std::vector<int> item;
    
    // item.push_back(123);

    // char *p = (char*)malloc(10);
    // char buf[10] = {"Hello"};
    // memcpy(p, buf, sizeof(buf));

    // printf("%s\n", p);

    // std::cout << sizeof(bool) << std::endl;

    string push_mode = "interval";
    
    string push_mode_name = FLEXEM_PUSH_MODE;
    // Get the push mode of name size length.
    int attribute_name_len = push_mode_name.size();
    int attribute_value_len = push_mode.size();
    unsigned int item_len = sizeof(ItemContent);

    // Set the push mode attribute struct. 
    ItemContent *item_content = (ItemContent*)malloc(sizeof(ItemContent) + sizeof(char) *\
        (attribute_name_len + attribute_value_len));
    if (item_content == nullptr) {
        std::cout << "Handle Request Push Mode Malloc Failed." << std::endl;
        return false;
    }
    // Set ItemContent
    item_content->item_type = 1;
    item_content->value_type = 4;
    item_content->id_size = attribute_name_len;
    item_content->value_size = attribute_value_len;
    // Get the name of value and id of value buf.
    char name_buf[attribute_name_len];
    char id_value_buf[attribute_value_len];
    strcpy(name_buf, push_mode_name.c_str());
    // memcpy(name_buf, push_mode_name.c_str(), attribute_name_len);
    // memcpy(id_value_buf, push_mode.c_str(), attribute_value_len);
    strcpy(id_value_buf, push_mode.c_str());
    // Set the zero array of value.
    std::cout << name_buf << std::endl;
    std::cout << id_value_buf << std::endl;

    memcpy(item_content->value, name_buf, attribute_name_len);
    memcpy(item_content->value + attribute_name_len, id_value_buf, attribute_value_len);

    std::cout << item_content->value << std::endl;

    char msg[item_len + attribute_value_len + attribute_name_len];
    memcpy(msg, item_content, item_len + attribute_value_len + attribute_name_len);

    for (unsigned int i = 0; i < item_len + attribute_value_len + attribute_name_len; ++i) {
        printf("%c\n", msg[i]);
    }
    printf("\n");
    
    ItemContent tmp_item_content;
    char tmp_name_buf[attribute_name_len + 1];
    char tmp_id_value_buf[attribute_value_len + 1];

    memcpy(&tmp_item_content, (char *)item_content, sizeof(ItemContent));
    memcpy(tmp_name_buf, (char *)(item_content->value), attribute_name_len);
    tmp_name_buf[attribute_name_len] = '\0';
    memcpy(tmp_id_value_buf, (char *)(item_content->value + attribute_name_len), attribute_value_len);
    tmp_id_value_buf[attribute_value_len] = '\0';
    
    std::cout << push_mode_name.size() << std::endl;
    std::cout << push_mode.size() << std::endl;
    std::cout << (int)attribute_name_len << std::endl;
    std::cout << (int)attribute_value_len << std::endl;
    std::cout << "+ " << tmp_name_buf << std::endl;
    std::cout << "+ " << tmp_id_value_buf << std::endl;

    // free (item_content);

    // char *p = "flexem_push_modeinterval";

    // char x_name_buf[attribute_name_len + 1];
    // char x_id_value[attribute_value_len + 1];

    // memcpy(x_name_buf, p, attribute_name_len);
    // x_name_buf[attribute_name_len] = '\0';
    // memcpy(x_id_value, p + attribute_name_len, attribute_value_len);
    // x_id_value[attribute_value_len] = '\0';

    // std::cout << "+ " << x_name_buf << std::endl;
    // std::cout << "+ " << x_id_value << std::endl;

    return 0;
}



