#include <iostream>

#include "block_manager.h"


using namespace universal_storage;


int main()
{
    char data[] = {0x41, 0x41, 0x41, '\0', 0x41};
    std::string s(data);
    std::cout << "data = " << s << std::endl;
    std::cout << "data len = " << s.size() << std::endl;

    BlockManager a("1");

    return 0;
}
