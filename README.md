# XSocket

这是一个半自动socket框架,大部分功能已经满足

## 注意事项

本程序基于`C++-11+`

依赖库:

1. string

2. vector

3. list

4. thread (建议)

依赖组件:

1. try/catch (排错方便)

## 特点

1. 跨平台,可在linux/win下使用(mac理论上可以)
2. 代码结构简单,win稍微复杂

## 使用方法

### 服务端

```cpp
#include <iostream>
#include "xsocket" //声明库
using namespace std;
int main()try{
#ifdef WIN32 //WIN平台进行WSA的初始化,linux不用
    XSOCKET::WSA();
#endif
    string msg;
    xsocket s; //定义一个 xsocekt
    bind(8089);
    s<<"Hello,I'm server."; //输出
    s>>msg; //输入数据,如果出错会throw
}catch(const char *error){
	cout<<error<<endl;
    exit(1);
}
```

### 客户端

```cpp
#include <iostream>
#include "xsocket" //声明库
using namespace std;
int main()try{
#ifdef WIN32 //WIN平台进行WSA的初始化,linux不用
    XSOCKET::WSA();
#endif
    string msg;
    xsocket s; //定义一个 xsocekt
    s.connect("127.0.0.1",8099);
    s>>msg; //输入数据到msg,如果出错会throw
    s<<"Hello,I'm client."; //向服务器发送信息
}catch(const char *error){
	cout<<error<<endl;
    exit(1);
}
```



## 具体函数介绍&用法

```cpp
XSOCKET::WSA(); //初始化WSA 在 win 下使用
xsocket(); //纯声明
xsocket(std::string,int); //相当于 connect 服务器
connect(std::string,int); //connect 服务器
connect(std::string,int,int); //规定重连次数
send(std::string); //发送字符串
read(std::string,int); //接受字符串,并规定最大值
read(char*,int); //接受 char* 类型字符串,并规定最大值
operator==(xsocket&); //判断 socket 是否相等
operator==(int); //判断 socket 与 socket_id 是否相等 (socket其实就是一个id)
operator!=(xsocket); //判断是否不等
operator!=(int); //判断是否不等
operator<<(std::string); //向服务器发送字符串
operator>>(std::string); //接收服务器的字符串,最大长度默认为 1024
operator>>(char*); //接收服务器的字符串,最大长度默认为 1024
close(); //关闭 socket
```

## BUG 代办

1. UDP协议没写好
