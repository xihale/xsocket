# 本分支针对 `Qt` 进行优化

# XSocket

这是一个半自动socket框架,大部分功能已经满足

## 注意事项

本程序基于`Cpp11+``STL标准库`

主要依赖:

1. string

2. vector

拍错组件: `try/catch`

## 特点

1. 跨平台,代码移植难度为`0`,linux/win(mac理论上可以,因本人没有mac,所以没有加入处理,如果可以提供环境,可以联系添加)
2. 代码结构简单

## 食用方法

`example`内有具体程序案例



## 具体函数介绍&用法

```cpp
xstd::XSOCKET::xsocketInit(); //XSOCKET初始化(针对Windows,Linux可有可无)
xstd::XSOCKET::getHostByName(std::string& host); //返回一个ip地址(返回值为vector)
xstd::XSOCKET::getHostByName(const char* host); //同上
xstd::XSOCKET::bind(int,int mode); //绑定一个服务端口 && 规定协议(默认为XSOCKET_TCP) 可重复使用,绑定后的套接字共用同一个内存空间
// 以下函数皆为 xstd::xsocket 子集
xsocket(); //纯声明
xsocket(std::string,int); //相当于 connect 服务端
connect(std::string,int); //connect 服务端
connect(std::string,int,int mode); //connect 服务端 && 规定协议(默认为XSOCKET_TCP)
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

## Update Logs

2022年1月29日
1. 修改了程序的部分处理
2. 标准化了部分代码

2021年xx月xx日
1. 完成了库主体&&Push
