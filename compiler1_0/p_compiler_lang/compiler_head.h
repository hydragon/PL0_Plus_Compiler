#ifndef COMPILER_HEAD_H_INCLUDED
#define COMPILER_HEAD_H_INCLUDED

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>
using namespace std;
const unsigned int nkw = 20,                 //�ؼ�������
                   al  = 10,                 //
                   alng = 14,                //��ʶ������
                   kmax = 15,                //������󳤶�
                   nmax = 32767, //2^14      //���������ֵ
                   tmax = 100,               //���ű���
                   bmax = 20,                //�ֳ������
                   amax = 30,                //�������
                   smax = 600,               //�ַ�������
                   cmax = 800,               //��Ԫʽ����
                   casemax = 30,             //case����֧�������
                   lmax = 10;                 //���Ƕ�ײ��


enum symbol{nul,
intcon, charcon, stringcon,                //����������
minussy, plussy, multi,divsy,               //�����                                                                                                                                                                                                                                                           sy, divsy,      //��ֵ�����
eql, neq, gtr, geq, lss, leq,         //��ϵ�����
lparent, rparent, lbrack, rbrack,     //С���ţ�������
comma, semicolon, period, colon, becomes, //������
constsy, varsy, funcsy,                   //�����������źͱ�ʶ��
procsy, arraysy, ident,                   //
beginsy, ifsy, casesy, forsy, readsy, writesy,             //�����ʼ����
endsy, elsesy, ofsy, dosy, tosy, downtosy, thensy};//����������

string symbolname[] = {"nul",
"intcon", "charcon", "stringcon",                //����������
"minussy", "plussy", "multi","divsy",               //�����                                                                                                                                                                                                                                                           sy, divsy,      //��ֵ�����
"eql", "neq", "gtr", "geq", "lss", "leq",         //��ϵ�����
"lparent", "rparent", "lbrack", "rbrack",     //С���ţ�������
"comma", "semicolon", "period", "colon", "becomes", //������
"constsy", "varsy", "funcsy",                   //�����������źͱ�ʶ��
"procsy", "arraysy", "ident",                   //
"beginsy", "ifsy", "casesy", "forsy", "readsy", "writesy",       //�����ʼ����
"endsy", "elsesy", "ofsy", "dosy", "tosy", "downtosy", "thensy"};

enum objecttype {consttype, vartype, proctype, functype};     //��ʶ����������
enum valuetype {notype, inttype, chartype, arraytype};        //��ʶ��ֵ����

enum four_code_option {ADD, SUB, DIV, MUL, BEQ, BGEZ, BGTZ, BLEZ, BLTZ, BNE, J, JR, ARRAY, LABEL, CALL, PUSH, POP,
                        DEC, PAR, VAR, CON, VART, READ, WRITE};                //��Ԫʽ������

struct table{               //���ű�
    string name ;
    int link ;              //ͬһ���ֳ����е���һ����ʶ��
    enum objecttype obj ;   //��ʶ����������
    enum valuetype typ ;    //��ʶ��ֵ����
    int refer ;             //���顢���̺�����ʶ��ָ���atab��btab
    int level ;             //��ʶ�������ֳ�����
    int ifvar ;             //����ǲ������Ƿ��Ǳ����β�
    int adr ;               //��ʶ���ڷֳ�������ջ��ƫ����
};
struct btable{              //�ֳ����
    int last ;              //��ǰ�ֳ�������һ������ı�ʶ����table�е�����
    int lastpar ;           //��ǰ�ֳ�������һ��������table�е�����
    int pnum ;              //��������
    int psize ;             //������������Ϣ��ռ����ջ�Ĺ�ģ
    int vsize ;             //�ֲ�������������������Ϣ������ջ�й�ģ
};
struct atable{              //�����
    enum valuetype type ;   //����Ԫ������
    int high ;              //��������±�
    int asize ;             //������ռ����ջ��ģ
};

struct four_code{
    enum four_code_option op;
    string t1;
    string t2;
    string t3;
};


string key[nkw];            //�ؼ����ַ�����

enum symbol ksy[nkw];       //�ؼ��ֶ�����symbol����
enum symbol sps[256];       //�ַ���symbol��
enum symbol sy;             //ÿ�ζ�ȡ���ʵõ��ķ�����Ϣ��¼

struct table tab[tmax];     //���ű�
struct btable btab[bmax];   //�ֳ����
struct atable atab[amax];   //�����
string stab[smax];          //�ַ�����
int    display[lmax];       //display��

struct four_code four_codes[cmax]; //��Ԫʽ��



int cc = 0,                 //��һ���ַ�����
    ll = 0,                 //��һ���ַ���
    cx = 0,                 //��ǰ��������
    inum = 0,               //����ֵ�洢
    level = 0,              //��ǰ�ֳ�����
    t = 1,      //���ű��ַ
    a = 0,      //������ַ
    b = 0,      //�ֳ�����ַ
    fc = 0;     //��Ԫʽ���ַ
char ch = ' ';              //ÿ�ζ����ĵ����ַ�
string line = "",           //��¼""�е��ַ���
       alfa = "";           //��¼ÿ�ζ������ַ���


void error(int eno){                   //������
    printf("*****Error%d: line%d char(%d)*****\n",eno, cx + 1, cc);
}//error end



#endif // COMPILER_HEAD_H_INCLUDED
