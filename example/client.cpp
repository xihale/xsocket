#include <iostream>
#include "../xsocket.h" //声明库
using namespace std;
using namespace xstd;
using namespace xstd::XSOCKET;
int main()try{
    xsocketInit();
    string msg;
    xsocket s; //定义一个 xsocekt
    s.connect("127.0.0.1",8099,XSOCKET_UDP);
    s>>msg; //输入数据到msg,如果出错会throw
    s<<"Hello,I'm client."; //向服务器发送信息
    cout<<msg<<endl;
}catch(const char *error){
	cout<<error<<endl;
    exit(1);
}