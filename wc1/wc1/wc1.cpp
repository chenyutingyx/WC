#include <stdio.h>
#include <string.h>
#include<iostream>
using namespace std;
int *open(char *filename, int *Count){
    FILE *point;  // 指向文件的指针
    char buffer[1003];  //存储读取到的每行的内容
    int bufferLen; 
    int i;  // 当前读到缓冲区的第i个字符
    char c;  // 读取到的字符
    int isLastBlank = 0;  // 上个字符是否是空格
    int charCount = 0;  // 当前一行的字符数
    int wordCount = 0; // 当前一行的单词数
    if( (point=fopen(filename, "rb")) == NULL ){
        perror(filename);
        return NULL;
    }  
    // 每次读取一行数据，保存到buffer
    while(fgets(buffer, 1003, point) != NULL)
	{
        bufferLen = strlen(buffer);
        for(i=0; i<bufferLen; i++){
            c = buffer[i];
            if( c==' ' || c=='\t'){  // 遇到空格
                !isLastBlank && wordCount++;  // 如果上个字符不是空格，那么单词数加1，防止出现两个连续空格
                isLastBlank = 1;
            }
			else if(c!='\n'&&c!='\r'){  
                charCount++;  // 如果既不是换行符也不是空格，字符数加1
                isLastBlank = 0;
            }
        }
        !isLastBlank && wordCount++;  // 如果最后一个字符不是空格，那么单词数加1
        isLastBlank = 1;  // 每次换行重置为1
        Count[0]++;  // 总行数
        Count[1] += charCount;  // 总字符数
        Count[2] += wordCount;  // 总单词数
        /*cout<<Count[0]<<"    ";
        cout<<Count[1]<<"    ";
        cout<<Count[2]<<"    "<<endl;*/
        // 置零，重新统计下一行
        charCount = 0;
        wordCount = 0;
    }
    return Count;
}
int main(){
	do{
		char filename[30];  
		int Count[3] = {0};//  Count[0]: 总行数   Count[1]: 总字符数   Count[2]: 总单词数
		cout<<"请输入路径：";
		cin>>filename;
		if(open(filename, Count)){
			cout<<"行数为："<<Count[0]<<endl;
			cout<<"字符数为："<<Count[1]<<endl;
			cout<<"单词数为："<<Count[2]<<endl;
		}
		else{
			cout<<"Error!\n";
		}        
		system("pause");
		cout<<"请输入任意键继续";
	}while(1);
    return 0;
}