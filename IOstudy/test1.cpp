/*************************************************************************
	> File Name: test1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年09月13日 星期三 17时04分00秒
 ************************************************************************/

#include<iostream>
using namespace std;
istream test(istream i);
int main()
{
    istream = i;
    i=test("./data");
    cout<<"\n"<<i.rdstate().toString<<endl;
    return 0;
}
istream test(istream i)
{
    char c;
    while(i>>c){
        cout>>c;
    }
    i.clear();
    return i;
}
