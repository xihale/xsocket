#include <iostream>
#include "../xsocket.h" //声明库
using namespace std;
using namespace xstd;
using namespace xstd::XSOCKET;
int main()try{
    xsocketInit();
    bind(8099,XSOCKET_UDP);
    string msg;
    xsocket s; //定义一个 xsocekt
    s.listen();
    s<<"Hello,I'm server."; //输出
    s>>msg; //输入数据,如果出错会throw
    cout<<msg<<endl;
}catch(const char *error){
	cout<<error<<endl;
    exit(1);
}