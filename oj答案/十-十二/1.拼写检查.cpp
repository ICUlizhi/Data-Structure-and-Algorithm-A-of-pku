#include<bits/stdc++.h>
using namespace std;


bool similar(string lonStr, string shorStr)  //判断单词是否相似
{
    int lon, shor;
    lon = lonStr.length();
    shor = shorStr.length();
    string temp;
    for(int i=0; i<shor; i++)
    {
        if(lonStr[i] != shorStr[i])         //遍历每个字母，找到不想等的字母位置
        {
            temp = shorStr.substr(0,i);
            temp = temp + lonStr[i] + shorStr.substr(i,shor-i); //在较短的单词中插入不想等的字母，然后判断是否相等。
            if(temp == lonStr)
            {
                return true;
            }
        }
    }
    temp = shorStr + lonStr[lon-1];     //以上判断会漏掉最后一个字母不想等的情况，这里补上。
    if(temp == lonStr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    vector<string> dictionary;      //存储字典单词
    vector<string>::iterator iter;  //迭代器
    string word;                    //需要检查的单词
    string dic;
    bool flag = false;
    int sub =0;
 
    while(1)                        //读入字典单词
    {
        cin >> dic;
        if(dic == "#")
        {
            break;
        }
        dictionary.push_back(dic);
    }
    while(1)                            //依次判断
    {
        cin >> word;
        if(word == "#")
        {
            break;
        }
        flag = false;
        for(iter = dictionary.begin(); iter != dictionary.end(); iter++) //判断字典中是否存在该单词
        {
            dic = *iter;
            if(dic == word)
            {
                cout << word << " is correct";
                flag = true;
            }
        }
        if(!flag)    //如果字典中不存在，则查找是否有相似的单词
        {
            cout << word << ":";
            for(iter = dictionary.begin(); iter != dictionary.end(); iter++) //遍历字典，判断是否相似
            {
                dic = *iter;
                sub = dic.length() - word.length();     //获取两个单词长度之差，如果 <=1,则符合条件，如果>1则不可能匹配成功
                if( sub== 0)                            //两个单词长度相同
                {
                    for(int i=0; i< dic.length(); i++)
                    {
                        if(dic[i] != word[i])
                        {
                            string temp = word;         //注意需要新建一个中间变量temp，不能直接修改单词word，因为之后还会用到word
                            temp[i] = dic[i];           //将不相等的单词替换为相等的单词，重新比较
                            if(temp == dic)
                            {
                                cout << " "<< dic ;
                            }
                            break;
                        }
                    }
                }else if(abs(sub) == 1)                  //两个单词长度相差1个字母
                {
                    if(dic.length() < word.length())
                    {
                        if(similar( word , dic ))        //判断单词是否相似的函数similar（）。
                        {
                            cout  << " "<< dic;
                        }
                    }
                    else
                    {
                        if(similar(dic,word))
                        {
                            cout << " "<< dic ;
                        }
                    }
                }
            }
        }
        cout << endl;
    }
 
    return 0;
}
 
