#ifndef ELEMTYPE_H//ͷ�ļ�������  
#define ELEMTYPE_H  
  
#define NULL_KEY 0//0Ϊ�޼�¼��־  
typedef int KeyType;//�ؼ�������  
typedef struct ElemType  
{//����Ԫ�أ���¼������  
    KeyType key;  
    int order;  
}ElemType;  
  
//��������ֵ�͹ؼ��ֵıȽ�Լ��Ϊ���µĺ궨�塣  
#define EQ(a,b) ((a) == (b))  
#define LT(a,b) ((a) < (b))  
#define LE(a,b) ((a) <= (b))  
  
//����������������  
void Visit(int p,ElemType r);  
#endif  