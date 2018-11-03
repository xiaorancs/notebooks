/**
 * 随机生成数据，200w个字符串， 
 * 这里全部又小写字母组成，每个字符串长5B
 *  
 */ 
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

// 尽可能选择一个大素数
const int MOD = 1000013;

/** 随机产生100W个长度为10的字符串，写入文件中，字符[0-9] + 'a'*/
void randCreateData(const char* outputfile, const int cnt = 1000000) {
    FILE *fp = NULL;
    fp = fopen(outputfile, "w+");
    if(fp == NULL) {
        printf("File error\n");
        return;
    }
    srand((unsigned)time(0));
    for(int i = 0; i < cnt; i++) {
        char tmp[12];
        int j;
        for(j = 0; j < 5; j++) {
            tmp[j] = char(rand()%5 + 'a');
        }
        tmp[j] = '\0';
        fprintf(fp, "%s\n", tmp);
    }
    fclose(fp);
}

/** 得到hash(str) % MOD **/
int hash_key(const char* str) {
    int value = 0;
    while(*str != '\0') {
        value = value * 31 + *str;
        value = value % MOD;
        str ++;
    }
    return value;;
}

void readFile(const char* inputfile) {
    FILE *fp = fopen(inputfile, "r");
    assert(fp != NULL);
    int i = 0;
    char buffer[10];
    while(! feof(fp)) {
        // 这样读取包含换行符
        fgets(buffer, sizeof(buffer)-1 ,fp);
        // 去掉换行符号
        buffer[strlen(buffer)-1] = '\0';
        if(i < 5) {
            printf("%s\n", buffer);
        }
        i ++;
    }
    fclose(fp);
}

/** 将200w * 5B的文件，根据key划分成50个文件，每个文件100B，大约1M **/
void partation(const char* inputfile, int filecnt = 50) {
    FILE * fps[filecnt];
    for(int i = 0; i < filecnt; i++) {
        char tmpfile[20] = "./data/tmpfile";
        char s[3];
        sprintf(s, "%d", i);
        char *file = strcat(tmpfile, s);
        // printf("%s\n", file);
        fps[i] = fopen(file, "w+");
        assert(fps[i] != NULL);
    }

    FILE *fp_read = fopen(inputfile, "r");
    assert(fp_read != NULL);
    int i = 0;
    char buffer[10];
    while(! feof(fp_read)) {
        // 这样读取包含换行符
        fgets(buffer, sizeof(buffer)-1 ,fp_read);
        // 去掉换行符号
        buffer[strlen(buffer)-1] = '\0';
        // 得到字符串对应的key，写入对应的文件
        int key = hash_key(buffer) % filecnt;
        fprintf(fps[key], "%s\n", buffer);
    }
    // close 所有文件指针
    for(int i = 0; i < filecnt; i++) {
        fclose(fps[i]);
    }
    fclose(fp_read);
}

/**自定义比较方式, 得到小根堆**/
struct cmp{
    bool operator()(pair<string, int> &t1, pair<string, int> &t2) const{
        return t1.second > t2.second;
    }
};
priority_queue<pair<string, int>, vector<pair<string, int> >, cmp > q;

/** 统计单个文件中的出现的频率 **/
int preocessedOneFile(const char *inputfile, const int topK=100) {
    map<string, int> s2cnt;
    FILE *fp_read = fopen(inputfile, "r");
    assert(fp_read != NULL);
    int i = 0;
    char buffer[10];
    while(! feof(fp_read)) {
        // 这样读取包含换行符
        fgets(buffer, sizeof(buffer)-1 ,fp_read);
        // 去掉换行符号
        buffer[strlen(buffer)-1] = '\0';
        string s = buffer;
        s2cnt[s] += 1;
    }
    // cout<<s2cnt.size()<<endl;
    for(auto it=s2cnt.begin(); it!=s2cnt.end(); it++) {
        q.push(make_pair(it->first, it->second));
        if(q.size() > topK) { // 保存最大的100个
            q.pop();
        }
    }

    /*
    int k = 0;
    while(q.size()) {
        pair<string, int> t = q.top();
        cout<<t.first<<" "<<t.second<<endl;
        q.pop();
        k ++;
        if(k > 10) break;
    }
    */
   return s2cnt.size();
}

/**得到topK **/
void getTopK(const int topK = 10) {
    int filecnt = 50;
    for(int i = 0; i < filecnt; i++) {
        char tmpfile[20] = "./data/tmpfile";
        char s[3];
        sprintf(s, "%d", i);
        char *file = strcat(tmpfile, s);
        preocessedOneFile(file, topK);
    }

    // print 结果
    cout<<q.size()<<endl;
    while(q.size()) {
        pair<string, int> t = q.top();
        cout<<t.first<<" "<<t.second<<endl;
        q.pop();
    }
}

int main()
{
    const char outputfile[] = "./data/randStr.txt";
    const char inputfile[] = "./data/randStr.txt";

    // 随机产生200w个长度5的字符串
    randCreateData(outputfile, 2000000);
    // readFile(inputfile);

    // 划分成50个小文件
    partation(inputfile);
    // preocessedOneFile(inputfile);

    // 处理所有的小文件得到最后的记过
    getTopK(20);
    return 0;
}