#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <bits/stdc++.h>
using namespace std;

class KeyValue{
public:
    string key;
    string value;

    KeyValue(string k, string v): key(k), value(v) {};
    KeyValue(): key(""), value("") {};
};

/**
 * @brief 自己写的字符串按照单词分割函数，因为mapReduce中经常用到
 * 
 * @param text 传入的文本内容，数据量极大
 * @param length 传入的字符串长度
 * @return vector<string> 返回各个分割后的单词列表
 */
vector<string> split(const string& text){
    //  这里就不用string流了，毕竟我们只要单词而不要其他字符。
    vector<string> str;
    string tmp = "";
    for(int i = 0; i < text.size(); i++){
        if(isalpha(text[i])){
            tmp += text[i];
        }else{
            if(tmp.size() != 0) str.push_back(tmp);      
            tmp = "";
        }
    }
    if(tmp.size() != 0) str.push_back(tmp);
    return str;
}

/**
 * @brief mapFunc，需要打包成动态库，并在worker中通过dlopen以及dlsym运行时加载
 * @param kv 将文本按单词划分并以出现次数代表value长度存入keyValue
 * @return 类似{"my 11111", "you 111"} 即文章中my出现了5次，you出现了3次
 */
extern "C" vector<KeyValue> mapF(KeyValue kv){
    vector<KeyValue> kvs;
    // int len = kv.value.size();
    // char content[len + 1];
    // strcpy(content, kv.value.c_str());
    vector<string> str = split(kv.value);
    for(const auto& s : str){
        kvs.emplace_back(s, "1");   //修改一下，不然用emplace_back意义何在
    }
    return kvs;
}

/**
 * @brief redecuFunc，也是动态加载，输出对特定keyValue的reduce结果
 * @param reduceTaskIdx 好像多余了，后来才发现的，放着也没事，懒得重新编译.so了
 * @return vector<string>
 */
extern "C" vector<string> reduceF(vector<KeyValue> kvs, int reduceTaskIdx){
    vector<string> str;
    string tmp;
    for(const auto& kv : kvs){
        str.push_back(to_string(kv.value.size()));
    }
    return str;
}

