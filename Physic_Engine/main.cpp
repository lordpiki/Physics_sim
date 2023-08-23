#include <iostream>
#include <WinSock2.h>
#include "Communicator.h"

using std::cout;
using std::endl;

int main() 
{
    const int PORT = 8876;
    Communicator communicator(PORT);
    communicator.sendMsg("test");
    cout << "Msg recieved:" << communicator.recieveMsg() << endl;


    return 0;
}
