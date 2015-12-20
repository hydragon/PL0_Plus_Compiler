#ifndef COMPILER_HEAD_H_INCLUDED
#define COMPILER_HEAD_H_INCLUDED

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>
using namespace std;
const unsigned int nkw = 20,                 //关键字数量
                   al  = 10,                 //
                   alng = 14,                //标识符长度
                   kmax = 15,                //整数最大长度
                   nmax = 32767, //2^14      //整数最大数值
                   tmax = 100,               //符号表长度
                   bmax = 20,                //分程序表长度
                   amax = 30,                //数组表长度
                   smax = 600,               //字符串表长度
                   cmax = 800,               //四元式表长度
                   casemax = 30,             //case语句分支最大数量
                   lmax = 10;                 //最大嵌套层次


enum symbol{nul,
intcon, charcon, stringcon,                //变量声明符
minussy, plussy, multi,divsy,               //运算符                                                                                                                                                                                                                                                           sy, divsy,      //数值运算符
eql, neq, gtr, geq, lss, leq,         //关系运算符
lparent, rparent, lbrack, rbrack,     //小括号，中括号
comma, semicolon, period, colon, becomes, //标点符号
constsy, varsy, funcsy,                   //各类声明符号和标识符
procsy, arraysy, ident,                   //
beginsy, ifsy, casesy, forsy, readsy, writesy,             //语句起始符号
endsy, elsesy, ofsy, dosy, tosy, downtosy, thensy};//其他保留字

string symbolname[] = {"nul",
"intcon", "charcon", "stringcon",                //变量声明符
"minussy", "plussy", "multi","divsy",               //运算符                                                                                                                                                                                                                                                           sy, divsy,      //数值运算符
"eql", "neq", "gtr", "geq", "lss", "leq",         //关系运算符
"lparent", "rparent", "lbrack", "rbrack",     //小括号，中括号
"comma", "semicolon", "period", "colon", "becomes", //标点符号
"constsy", "varsy", "funcsy",                   //各类声明符号和标识符
"procsy", "arraysy", "ident",                   //
"beginsy", "ifsy", "casesy", "forsy", "readsy", "writesy",       //语句起始符号
"endsy", "elsesy", "ofsy", "dosy", "tosy", "downtosy", "thensy"};

enum objecttype {consttype, vartype, proctype, functype};     //标识符基本类型
enum valuetype {notype, inttype, chartype, arraytype};        //标识符值类型

enum four_code_option {ADD, SUB, DIV, MUL, BEQ, BGEZ, BGTZ, BLEZ, BLTZ, BNE, J, JR, ARRAY, LABEL, CALL, PUSH, POP,
                        DEC, PAR, VAR, CON, VART, READ, WRITE};                //四元式操作符

struct table{               //符号表
    string name ;
    int link ;              //同一个分程序中的上一个标识符
    enum objecttype obj ;   //标识符基本类型
    enum valuetype typ ;    //标识符值类型
    int refer ;             //数组、过程函数标识符指向的atab、btab
    int level ;             //标识符所属分程序层次
    int ifvar ;             //如果是参数，是否是变量形参
    int adr ;               //标识符在分程序运行栈的偏移量
};
struct btable{              //分程序表
    int last ;              //当前分程序的最后一个定义的标识符在table中的索引
    int lastpar ;           //当前分程序的最后一个参数在table中的索引
    int pnum ;              //参数个数
    int psize ;             //参数及内务信息所占运行栈的规模
    int vsize ;             //局部变量、参数及内务信息在运行栈中规模
};
struct atable{              //数组表
    enum valuetype type ;   //数组元素类型
    int high ;              //数组最大下标
    int asize ;             //数组所占运行栈规模
};

struct four_code{
    enum four_code_option op;
    string t1;
    string t2;
    string t3;
};


string key[nkw];            //关键字字符串表

enum symbol ksy[nkw];       //关键字独立的symbol数组
enum symbol sps[256];       //字符的symbol表
enum symbol sy;             //每次读取单词得到的符号信息记录

struct table tab[tmax];     //符号表
struct btable btab[bmax];   //分程序表
struct atable atab[amax];   //数组表
string stab[smax];          //字符串表
int    display[lmax];       //display区

struct four_code four_codes[cmax]; //四元式表



int cc = 0,                 //读一行字符计数
    ll = 0,                 //上一行字符数
    cx = 0,                 //当前代码行数
    inum = 0,               //整数值存储
    level = 0,              //当前分程序层次
    t = 1,      //符号表地址
    a = 0,      //数组表地址
    b = 0,      //分程序表地址
    fc = 0;     //四元式表地址
char ch = ' ';              //每次读出的单个字符
string line = "",           //记录""中的字符串
       alfa = "";           //记录每次读出的字符串


void error(int eno){                   //错误处理
    printf("*****Error%d: line%d char(%d)*****\n",eno, cx + 1, cc);
}//error end



#endif // COMPILER_HEAD_H_INCLUDED
