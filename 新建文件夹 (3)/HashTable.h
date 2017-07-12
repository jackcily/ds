#ifndef HASHTABLE_H//头文件保护符  
#define HASHTABLE_H  
  
#include "ElemType.h"  
static int hashsize[] = {11,19,29,37};//内部链接静态变量，哈希表容量（表长m）递增表，一个合适的素数序列。  
typedef struct HashTable  
{//哈希表的存储结构  
    ElemType *elem;//记录存储基址变量，动态分配数组  
    int count;//当前记录个数  
    int sizeindex;//hashsize[sizeindex]为当前表长  
}HashTable;  
  
//宏定义  
typedef int Status; // Status是函数的类型,其值是函数结果状态代码，如下边三个宏定义  
#define SUCCESS 1 //查找成功  
#define UNSUCCESS 0//查找失败  
#define DUPLICATE -1//记录重复  
  
//基本操作函数声明  
void InitHashTable(HashTable &H);  
  
void DestroyHashTable(HashTable &H);  
  
unsigned Hash(KeyType k);  
  
int d(int i);  
  
void collision(KeyType &k,int &p,int i);  
  
Status SearchHash(HashTable H,KeyType k,int &p,int &c);  
  
Status InsertHash(HashTable &H,ElemType e);  
  
void RecreateHashTable(HashTable &H);  
  
void TraverseHash(HashTable H,void (*Visit)(int,ElemType));  
  
#endif  