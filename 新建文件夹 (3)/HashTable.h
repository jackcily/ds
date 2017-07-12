#ifndef HASHTABLE_H//ͷ�ļ�������  
#define HASHTABLE_H  
  
#include "ElemType.h"  
static int hashsize[] = {11,19,29,37};//�ڲ����Ӿ�̬��������ϣ����������m��������һ�����ʵ��������С�  
typedef struct HashTable  
{//��ϣ��Ĵ洢�ṹ  
    ElemType *elem;//��¼�洢��ַ��������̬��������  
    int count;//��ǰ��¼����  
    int sizeindex;//hashsize[sizeindex]Ϊ��ǰ��  
}HashTable;  
  
//�궨��  
typedef int Status; // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬���±������궨��  
#define SUCCESS 1 //���ҳɹ�  
#define UNSUCCESS 0//����ʧ��  
#define DUPLICATE -1//��¼�ظ�  
  
//����������������  
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