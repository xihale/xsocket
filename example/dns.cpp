#include <iostream>
#include <vector>
#include <string>
#include "../xsocket.h"
using namespace std;
using namespace xstd::XSOCKET;
int main(){
    string host;
    vector<string> ip;
    while(true){
        try{
            cout<<"Host: ";
            cin>>host;
            ip=getHostByName(host);
            for(auto s:ip)
                cout<<s<<endl;
        }catch(const char* err){
            cerr<<err<<endl;
        }
    }
    return 0;
}