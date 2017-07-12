#include <stdio.h>//NULL��  
#include <stdlib.h>//exit()�� rand()  
#include <malloc.h>//malloc  
#include <math.h>//OVERFLOW��pow()  
#include "HashTable.h"  
  
static int m;//�ڲ����Ӿ�̬������mΪ��ϣ���  
  
void InitHashTable(HashTable &H)  
{//��ʼ����ϣ������һ����¼Ϊ�յĹ�ϣ��  
    int i;  
    H.sizeindex = 0;//��ʼ������������Ϊ0  
    m = hashsize[H.sizeindex];//��ʼ����Ϊhashsize[0]  
    H.count = 0;//��ʼ����¼��Ϊ0  
    H.elem = (ElemType *)malloc(m * sizeof(ElemType));//��̬�����¼����  
    if (!H.elem)  
    {//����ʧ��  
        exit(OVERFLOW);  
    }  
    for (i = 0; i < m; ++i)  
    {//��ʼ����¼����ؼ���Ϊ��  
        H.elem[i].key = NULL_KEY;//δ���¼�ı�־  
    }  
}  
  
void DestroyHashTable(HashTable &H)  
{//���ٹ�ϣ��  
    free(H.elem);//�ͷŶ�̬��¼����  
    H.elem = NULL;//ָ����Ϊ��  
    H.count = 0;//��¼����ΪΪ0  
    H.sizeindex = 0;//����������Ϊ0  
}  
unsigned Hash(KeyType k)  
{//���ع�ϣ������õĹ�ϣ��ַ���ó��������������һ���򵥵Ĺ�ϣ������  
    return k % m;// H(key) = key MOD p (p �� m),ȡp=m  
}  
  
int d(int i)  
{//�������к���������iΪ��ͻ������������Ҫ��3�ַ���ѡȡһ�֣���������ע�͵�  
    return i;//����̽����ɢ�У�di = 1,2,3,...,m-1  
//  return ((i + 1)/2) * ((i + 1)/2) * (int)pow(double(-1),i - 1);//����̽����ɢ�У�di = 1,-1^2,2,-2^2,...,��k^2(k <= m - 1)  
//  return rand();//α���̽����ɢ�У�di = α���������  
}  
  
void collision(KeyType &k,int &p,int i)  
{//�ÿ��Ŷ�ַ�������ͻ,����pΪ��������õĹ�ϣ��ַ,iΪ��ͻ������  
    p = (Hash(k) + d(i)) % m;  
}  
  
Status SearchHash(HashTable H,KeyType k,int &p,int &c)  
{//�ڿ��ŵ�ַ��ϣ���в��ҹؼ���ΪK�ļ�¼�������ҳɹ�����pָʾ��¼�ڱ��е�λ�ã�������SUCCESS��  
 //������pָʾ����λ�ã�������UNSUCCESS��c�ԼƳ�ͻ���������ֵΪ0,���������ʱ�ο�  
    p = Hash(k);//�ù�ϣ���������ϣ��ַ  
    while (H.elem[p].key != NULL_KEY && !EQ(H.elem[p].key,k))  
    {//��λ�������м�¼������������¼�����  
        c++;  
        if (c < m)  
        {//�����ͻ����δ����m - 1������������ͻ  
            collision(k,p,c);  
        }  
        else  
        {//��������������H��λ�ҵ���¼  
            break;  
        }  
    }  
    if (EQ(H.elem[p].key,k))  
    {//���ҳɹ�  
        return SUCCESS;  
    }  
    else  
    {//����ʧ��  
        return UNSUCCESS;  
    }  
}  
  
void RecreateHashTable(HashTable &);//�Ժ���RecreateHashTable()������  
  
Status InsertHash(HashTable &H,ElemType e)  
{  
    int p,c = 0;//��ͻ������ʼΪ0  
    if (SearchHash(H,e.key,p,c))  
    {//���ҳɹ�  
        return DUPLICATE;//H��������e����ͬ�ؼ��ֵļ�¼,������  
    }  
    else if (c < hashsize[H.sizeindex]/2)  
    {//δ�ҵ�����ͻ����cҲδ�ﵽ���ޣ�c�ķ�ֵ�ɵ�,����󲻳���hashsize[H.sizeindex] - 1��  
        H.elem[p] = e;//��H�в�������Ԫ��e  
        ++H.count;  
        return SUCCESS;//����ɹ�  
    }  
    else  
    {//δ�ҵ�������ͻ����c�Ѵﵽ����  
        RecreateHashTable(H);//�ؽ���ϣ��  
        return UNSUCCESS;//���벻�ɹ�  
    }  
}  
  
void RecreateHashTable(HashTable &H)  
{  
    int i,count = H.count;//H��ԭ�м�¼����  
    ElemType *p,*elem = (ElemType *)malloc(count *sizeof(ElemType));//��̬���ɴ�Ź�ϣ��Hԭ�����ݵĿռ�  
    p =elem;  
    for (i = 0; i < m; ++i)  
    {//��ԭ�е����м�¼�����浽elem��  
        if (!EQ(H.elem[i].key,NULL_KEY))  
        {//H�ڸõ�Ԫ�м�¼  
            *p++ = H.elem[i];//����¼���δ���elem  
        }  
    }  
    H.count = 0;//��ԭ�м�¼����Ϊ0��Ϊ�������InserHash��׼��  
    H.sizeindex++;//������������1  
    m = hashsize[H.sizeindex];//�µĴ洢����������  
    H.elem = (ElemType *)realloc(H.elem,m*sizeof(ElemType));//���µĴ洢�����������ɿչ�ϣ��H  
    for (i = 0; i < m; ++i)  
    {//��ʼ���µĹ�ϣ��  
        H.elem[i].key = NULL_KEY;//δ���¼  
    }  
    for (p = elem; p < elem + count; ++p)  
    {//��ԭ���еļ�¼���´洢���µĹ�ϣ����  
        InsertHash(H,*p);  
    }  
    free(elem);//�ͷ�elem�Ĵ洢�ռ�  
}  
  
void TraverseHash(HashTable H,void (*Visit)(int,ElemType))  
{//����ϣ��ַ��˳�������ϣ��H  
    int i;  
    printf("��ϣ��ַ 0 ~ %d\n",m - 1);  
    for (i = 0; i < m; ++i)  
    {//����������ϣ��H  
        if (!EQ(H.elem[i].key,NULL_KEY))  
        {//H�ڵ�i����Ԫ�м�¼  
            Visit(i,H.elem[i]);//���ʵ�i������  
        }  
    }  
}  