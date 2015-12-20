#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>

using namespace std;

const int displaylength = 3,    //display区在运行栈中的个数
          spreturnshift = 36,   //过程返回时调用上层过程运行栈sp地址的存放地址
          codereturnshift = 44, //过程返回时调用代码返回地址的存放地址
          returnvalueshift = 40,//函数返回值存放地址
          parlistlength = 20;   //参数表在运行栈中的个数

const int cmax = 800,//四元式表长度
          mmax = 3000,//mips表长度
          levelmax = 10,//嵌套最大层次
          tmax = 800;//符号表长度
string spreturnshifts = "36",   //过程返回时调用上层过程运行栈sp地址的存放地址
       codereturnshifts = "44", //过程返回时调用代码返回地址的存放地址
       returnvalueshifts = "40";//函数返回值存放地址

char ch;
int cx = 0,
    fc = 0,         //四元式索引
    mc = 0,         //mips表索引
    t  = 0,         //符号表索引
    level = 0,      //display区索引
    iffileend = 0;

string alfa;

enum four_code_option {ADD, SUB, DIV, MUL, BEQ, BGEZ, BGTZ, BLEZ, BLTZ, BNE, J, JR, ARRAY, LABEL, CALL, PUSH, POP,
                        DEC, PAR, VAR, VART, CON, READ, WRITE};                //四元式操作符

enum identtype {proc, func, normal, arraytype, varpar};

enum four_code_option op;

struct four_code{
    enum four_code_option op;
    string t1;
    string t2;
    string t3;
};

struct mips_code{
    string op;
    string rs;
    string rt;
    string rd;
};

struct table{   //符号表
    string name;
    enum identtype type;    //类型
    int vtype;              //值类型，0代表无类型，1代表是整形，2代表字符型
    int countt;             //记录从声明一个新的过程开始占用的符号表个数
    int value;              //标识符值，过程函数存其在运行栈的占用空间，数组、常量、变量存其占用空间长度
    int level;              //记录标识符所属嵌套层次
    int spshift;            //在运行栈中相对sp的偏移量
};

struct four_code four_codes[cmax]; //四元式表
struct mips_code mips_codes[mmax]; //mips表
struct table tab[tmax];            //符号表

int display[levelmax];          //display区

using namespace std;

void getch()                    //读取一个字符
{
    ch = getchar();
    if(ch == EOF){  //程序不完整
        iffileend = 1;
        return;
    }
    if(ch == '\n'){ //一行结束
        cx += 1;
    }
}

void nextsym()                                          //读取一个单词
{
    alfa.clear();
    while(ch == ' ' || ch == '\t' || ch == '\n'){   //消除空字符
        getch();
    }
    if(ch == '\"'){
        alfa += ch;
        getch();
        while(ch != '\"'){
            alfa += ch;
            getch();
        }
        alfa += ch;
        getch();
    }
    else{
        while(!(ch == ' ' || ch == '\t' || ch == '\n' || ch == EOF)){
            alfa += ch;
            getch();
        }
    }

}

void trans_op(){        //翻译四元式操作符
    if    (alfa == "ADD")  {op = ADD; }
    else if(alfa == "SUB")  {op = SUB;}
    else if(alfa == "MUL")  {op = MUL;}
    else if(alfa == "DIV")  {op = DIV;}
    else if(alfa == "BEQ")  {op = BEQ;}
    else if(alfa == "BGEZ") {op = BGEZ;}
    else if(alfa == "BGTZ") {op = BGTZ;}
    else if(alfa == "BLEZ") {op = BLEZ;}
    else if(alfa == "BLTZ") {op = BLTZ;}
    else if(alfa == "BNE")  {op = BNE; }
    else if(alfa == "ARRAY")  {op = ARRAY;}
    else if(alfa == "J")    {op = J;}
    else if(alfa == "JR")   {op = JR;}
    else if(alfa == "LABEL"){op = LABEL;}
    else if(alfa == "DEC")  {op = DEC;}
    else if(alfa == "PAR")  {op = PAR;}
    else if(alfa == "CON")  {op = CON;}
    else if(alfa == "VAR")  {op = VAR;}
    else if(alfa == "VART") {op = VART;}
    else if(alfa == "CALL") {op = CALL;}
    else if(alfa == "PUSH") {op = PUSH;}
    else if(alfa == "POP")  {op = POP;}
    else if(alfa == "READ") {op = READ;}
    else if(alfa == "WRITE"){op = WRITE;}
}

string trans_op_to_string(enum four_code_option enumop){
    string tmpop;
    switch(enumop){
        case ADD : {tmpop = "ADD"; break;}
        case SUB : {tmpop = "SUB"; break;}
        case MUL : {tmpop = "MUL"; break;}
        case DIV : {tmpop = "DIV"; break;}
        case BEQ : {tmpop = "BEQ"; break;}
        case BGEZ: {tmpop = "BGEZ"; break;}
        case BGTZ: {tmpop = "BGTZ"; break;}
        case BLEZ: {tmpop = "BLEZ"; break;}
        case BLTZ: {tmpop = "BLTZ"; break;}
        case BNE : {tmpop = "BNE"; break;}
        case ARRAY : {tmpop = "ARRAY"; break;}
        case J   : {tmpop = "J"; break;}
        case JR  : {tmpop = "JR"; break;}
        case LABEL:{tmpop = "LABEL"; break;}
        case DEC : {tmpop = "DEC"; break;}
        case PAR : {tmpop = "PAR"; break;}
        case CON : {tmpop = "CON"; break;}
        case VAR : {tmpop = "VAR"; break;}
        case VART: {tmpop = "VART"; break;}
        case CALL: {tmpop = "CALL"; break;}
        case PUSH: {tmpop = "PUSH"; break;}
        case POP : {tmpop = "POP"; break;}
        case READ: {tmpop = "READ"; break;}
        case WRITE:{tmpop = "WRITE"; break;}
    }
    return tmpop;
}

void getfour_code()     //读取四元式
{
    while(iffileend == 0){
        nextsym();
        if(iffileend == 1){
            break;
        }
        nextsym();
        nextsym();
        trans_op();

        if(op == ADD || op == SUB || op == MUL || op == DIV || op == ARRAY){    //运算符及数组操作生成
            four_codes[fc].op = op;
            nextsym();
            four_codes[fc].t1 = alfa;
            nextsym();
            four_codes[fc].t2 = alfa;
            nextsym();
            four_codes[fc].t3 = alfa;

            fc += 1;
        }
        else if(op == BNE || op == BEQ || op == BGEZ || op == BGTZ || op == BLEZ || op == BLTZ){    //条件跳转生成
            four_codes[fc].op = op;
            nextsym();
            four_codes[fc].t1 = alfa;
            nextsym();
            four_codes[fc].t2 = alfa;
            nextsym();
            four_codes[fc].t3 = alfa;

            fc += 1;
        }
        else if(op == J){                                           //无条件跳转生成
            four_codes[fc].op = op;
            nextsym();
            four_codes[fc].t3 = alfa;

            fc += 1;
        }
        else if(op == JR){
            four_codes[fc].op = op;

            fc += 1;
        }
        else if(op == DEC || op == CON){    //声明语句和调用语句生成
            four_codes[fc].op = op;
            nextsym();
            four_codes[fc].t1 = alfa;
            nextsym();
            four_codes[fc].t3 = alfa;

            fc += 1;
        }
        else if(op == PAR || op == VAR){
            four_codes[fc].op = op;
            nextsym();
            four_codes[fc].t1 = alfa;
            nextsym();
            four_codes[fc].t2 = alfa;
            nextsym();
            four_codes[fc].t3 = alfa;

            fc += 1;
        }
        else if(op == CALL || op == PUSH ){
            four_codes[fc].op = op;
            nextsym();
            four_codes[fc].t3 = alfa;

            fc += 1;
        }
        else if(op == VART){   //临时变量空间声明处理
            four_codes[fc].op = op;
            nextsym();
            four_codes[fc].t3 = alfa;

            fc += 1;
        }
        else if(op == LABEL){               //标记生成
            four_codes[fc].op = op;
            nextsym();
            four_codes[fc].t3 = alfa;

            fc += 1;
        }

        else if(op == READ || op == WRITE){
            four_codes[fc].op = op;
            nextsym();
            four_codes[fc].t3 = alfa;

            fc += 1;
        }
    }
}


int locate(string name)
{
    int i;
    for(i = t - 1; i > 0; i--){
        if(tab[i].name == name){
            return i;
        }
    }
    return 0;
}

void entermips(string mipsop, string mipsrs, string mipsrt, string mipsrd)
{
    mips_codes[mc].op = mipsop;
    mips_codes[mc].rs = mipsrs;
    mips_codes[mc].rt = mipsrt;
    mips_codes[mc].rd = mipsrd;

    mc += 1;
}

void gen_mips()
{
    int i,  //循环访问四元式
        coni1,//运算时的常量整数
        coni2,
        tmpt,  //对符号表的临时访问
        parcount = 0;   //传递参数计数
    char spchar[20];

    tab[t].name = "_main";
    tab[t].level = level;
    tab[t].countt = 1;
    tab[t].value = 3;
    tab[t].spshift = 0;
    tab[t].type = proc;
    display[level] = t;
    t = t + 1;

    entermips("addi", "$s0,", "$sp,", "0");     //初始sp记录进s0
    entermips("addi", "$sp,", "$sp,", "-80");   //跳过参数栈开始运行栈
    entermips("sw", "", "$sp,", "0($sp)");

    for(i = 0; i < fc; i++){
        coni1 = coni2 = -1;

        entermips("\n#" + trans_op_to_string(four_codes[i].op), four_codes[i].t1, four_codes[i].t2, four_codes[i].t3 + "\n");  //注释四元式

        if(four_codes[i].op == ADD || four_codes[i].op == SUB ||
           four_codes[i].op == MUL || four_codes[i].op == DIV || four_codes[i].op == ARRAY ||
           four_codes[i].op == BNE || four_codes[i].op == BEQ || four_codes[i].op == BGEZ ||
           four_codes[i].op == BGTZ || four_codes[i].op == BLEZ || four_codes[i].op == BLTZ){    //运算符及数组操作生成

            if(four_codes[i].t1[0] >= '0' && four_codes[i].t1[0] <= '9'){   //取第一个操作数
                coni1 = atoi(four_codes[i].t1.c_str());
                entermips("addi", "$t1,", "$zero,", four_codes[i].t1);
            }
            else if(four_codes[i].t1[0] == '#'){    //临时变量
                tmpt = locate(four_codes[i].t1.erase(0, 1));

                itoa(-tab[tmpt].spshift*4, spchar, 10);
                entermips("lw", "", "$t1,", (string)spchar + "($sp)");
            }
            else if(four_codes[i].t1[0] == '%'){
                tmpt = locate(four_codes[i].t1.erase(0, 1));

                itoa(-tab[tmpt].spshift*4, spchar, 10);
                entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                entermips("lw", "", "$t1,", "0($t0)");
            }
            else{   //标识符变量
                tmpt = locate(four_codes[i].t1);

                if(tab[tmpt].type == normal){   //普通标识符
                    if(tab[tmpt].level == level){
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("lw", "", "$t1,", (string)spchar + "($sp)");
                    }
                    else{
                        itoa(-tab[tmpt].level*4, spchar, 10);
                        entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("lw", "", "$t1,", (string)spchar + "($t0)");
                    }
                }
                else if(tab[tmpt].type == func){    //函数标识符
                    entermips("addi", "$t1,", "$v0,", "0");
                }
                else if(tab[tmpt].type == arraytype){   //数组标识符
                    if(tab[tmpt].level == level){
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("addi", "$t1,", "$sp,", (string)spchar);
                    }
                    else{
                        itoa(-tab[tmpt].level*4, spchar, 10);
                        entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("addi", "$t1", "$t0,", (string)spchar);
                    }
                }
                else if(tab[tmpt].type == varpar){  //变量形参
                    itoa(-tab[tmpt].spshift*4, spchar, 10);
                    entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                    entermips("lw", "", "$t1,", "0($t0)");
                }
            }

            if(four_codes[i].t2[0] >= '0' && four_codes[i].t2[0] <= '9'){   //取第二个操作数
                coni1 = atoi(four_codes[i].t2.c_str());
                entermips("addi", "$t2,", "$zero,", four_codes[i].t2);
            }
            else if(four_codes[i].t2[0] == '#'){
                tmpt = locate(four_codes[i].t2.erase(0, 1));

                itoa(-tab[tmpt].spshift*4, spchar, 10);
                entermips("lw", "", "$t2,", (string)spchar + "($sp)");
            }
            else if(four_codes[i].t2[0] == '%'){
                tmpt = locate(four_codes[i].t2.erase(0, 1));

                itoa(-tab[tmpt].spshift*4, spchar, 10);
                entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                entermips("lw", "", "$t2,", "0($t0)");
            }
            else{
                tmpt = locate(four_codes[i].t2);

                if(tab[tmpt].type == normal || tab[tmpt].type == func){
                    if(tab[tmpt].level == level){
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("lw", "", "$t2,", (string)spchar + "($sp)");
                    }
                    else{
                        itoa(-tab[tmpt].level*4, spchar, 10);
                        entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("lw", "", "$t2,", (string)spchar + "($t0)");
                    }
                }
                else if(tab[tmpt].type == varpar){  //变量形参
                    itoa(-tab[tmpt].spshift*4, spchar, 10);
                    entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                    entermips("lw", "", "$t2,", "0($t0)");
                }
            }

            switch(four_codes[i].op){                   //翻译成为特定的mips指令
                case ADD   : {
                                entermips("add", "$t3,", "$t1,", "$t2");
                                break;
                             }
                case SUB   : {
                                entermips("sub", "$t3,", "$t1,", "$t2");
                                break;
                             }
                case MUL   : {
                                entermips("mul", "$t3,", "$t1,", "$t2");
                                break;
                             }
                case DIV   : {
                                entermips("div", "$t1,", "$t2", "");
                                entermips("mflo", "", "", "$t3");
                                break;
                             }
                case ARRAY : {
                                entermips("mul", "$t2,", "$t2,", "4");
                                entermips("sub", "$t0,", "$t1,", "$t2");
                                if(four_codes[i].t3[0] == '#'){
                                    entermips("lw", "", "$t3,", "0($t0)");
                                }
                                else{
                                    tmpt = locate(four_codes[i].t3.erase(0, 1));

                                    itoa(-tab[tmpt].spshift*4, spchar, 10);
                                    entermips("sw", "", "$t0,", (string)spchar + "($sp)");
                                    continue;
                                }
                                break;
                             }
                case BEQ   : {
                                entermips("beq", "$t1,", "$t2,", four_codes[i].t3);
                                continue;
                             }
                case BNE   : {
                                entermips("bne", "$t1,", "$t2,", four_codes[i].t3);
                                continue;
                             }
                case BGTZ  : {
                                entermips("sub", "$t3,", "$t1,", "$t2");
                                entermips("bgtz", "$t3,", "", four_codes[i].t3);
                                continue;
                             }
                case BGEZ  : {
                                entermips("sub", "$t3,", "$t1,", "$t2");
                                entermips("bgez", "$t3,", "", four_codes[i].t3);
                                continue;
                             }
                case BLEZ  : {
                                entermips("sub", "$t3,", "$t1,", "$t2");
                                entermips("blez", "$t3,", "", four_codes[i].t3);
                                continue;
                             }
                case BLTZ  : {
                                entermips("sub", "$t3,", "$t1,", "$t2");
                                entermips("bltz", "$t3,", "", four_codes[i].t3);
                                continue;
                             }
                default    : ;
            }

            if(four_codes[i].t3[0] == '#'){                 //赋值操作数
                tmpt = locate(four_codes[i].t3.erase(0, 1));

                itoa(-tab[tmpt].spshift*4, spchar, 10);
                entermips("sw", "", "$t3,", (string)spchar + "($sp)");
            }
            else if(four_codes[i].t3[0] == '%'){
                tmpt = locate(four_codes[i].t3.erase(0, 1));

                itoa(-tab[tmpt].spshift*4, spchar, 10);
                entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                entermips("sw", "", "$t3,", "0($t0)");
            }
            else{
                tmpt = locate(four_codes[i].t3);

                if(tab[tmpt].type == normal || tab[tmpt].type == func){
                    if(tab[tmpt].level == level || tab[tmpt].type == func){
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("sw", "", "$t3,", (string)spchar + "($sp)");
                    }
                    else{
                        itoa(-tab[tmpt].level*4, spchar, 10);
                        entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("sw", "", "$t3,", (string)spchar + "($t0)");
                    }
                }
                else if(tab[tmpt].type == varpar){  //变量形参
                    itoa(-tab[tmpt].spshift*4, spchar, 10);
                    entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                    entermips("sw", "", "$t3,", "0($t0)");
                }
            }
        }
        else if(four_codes[i].op == J){                                           //无条件跳转生成
            entermips("j", "", "", four_codes[i].t3);
        }
        else if(four_codes[i].op == JR){
            if(level == 0){
                break;
            }
            tmpt = display[level];
            t = t - tab[tmpt].countt;
            level -= 1;

            entermips("lw", "", "$v0,", "-" + returnvalueshifts + "($sp)");
            entermips("lw", "", "$ra,", "-" + codereturnshifts + "($sp)");
            entermips("lw", "", "$sp,", "-" + spreturnshifts + "($sp)");

            entermips("jr", "", "", "$ra");
        }
        else if(four_codes[i].op == DEC){    //声明语句和调用语句生成
            tab[t].name = four_codes[i].t3;
            tab[t].level = level;
            tab[t].countt = 0;
            tab[t].value = 6;
            tab[t].spshift = 0;
            tab[t].vtype = 0;
            tab[t].type = (four_codes[i].t1 == "f")? func : proc;

            tab[display[level]].countt += 1;
            level += 1;
            display[level] = t;

            t += 1;

            entermips(four_codes[i].t3 + ":", "", "", "");

            entermips("sw", "", "$ra,", "-" + codereturnshifts + "($sp)");
        }
        else if(four_codes[i].op == CON){
            tab[t].name = four_codes[i].t3;
            tab[t].level = level;
            tab[t].countt = tab[t - 1].countt + 1;
            tab[t].value = 1;
            tab[t].spshift = tab[t - 1].spshift + tab[t - 1].value;
            tab[t].type = normal;

            if(four_codes[i].t1[0] == '\''){
                itoa(four_codes[i].t1[1] - '\0', spchar, 10);
                entermips("addi", "$t0,", "$zero,", (string)spchar);
                tab[t].vtype = 2;
            }
            else{
                entermips("addi", "$t0,", "$zero,", four_codes[i].t1);
                tab[t].vtype = 1;
            }

            itoa(-tab[t].spshift*4, spchar, 10);
            entermips("sw", "", "$t0,", (string)spchar + "($sp)");

            t += 1;
        }
        else if(four_codes[i].op == VAR){
            tab[t].name = four_codes[i].t3;
            tab[t].level = level;
            tab[t].countt = tab[t - 1].countt + 1;
            if(four_codes[i].t1 == "a"){
                int inum = atoi(four_codes[i].t2.c_str());
                tab[t].vtype = 1;
                tab[t].value = inum;
            }
            else{
                tab[t].vtype = (four_codes[i].t2 == "c")? 2 : 1;
                tab[t].value = 1;
            }

            tab[t].spshift = tab[t - 1].spshift + tab[t - 1].value;
            tab[t].type = (four_codes[i].t1 == "a")? arraytype : normal;

            t += 1;
        }
        else if(four_codes[i].op == PAR){       //形式参数取值
            tab[t].name = four_codes[i].t3;
            tab[t].level = level;
            tab[t].countt = tab[t - 1].countt + 1;
            tab[t].value = 1;
            tab[t].vtype = (four_codes[i].t2 == "c")? 2 : 1;
            tab[t].spshift = tab[t - 1].spshift + tab[t - 1].value;
            tab[t].type =(four_codes[i].t1 == "v")? varpar : normal;

            int inum = ((four_codes[i].t1 == "v")? 1 : 0) + parcount * 2 ;
            itoa(-4 * inum, spchar, 10); //取参数栈中参数的地址或值
            entermips("lw", "", "$t1,", (string)spchar + "($s0)");

            itoa(-tab[t].spshift*4, spchar, 10);
            entermips("sw", "", "$t1,", (string)spchar + "($sp)");

            t += 1;
            parcount += 1;  //形式参数计数，在vart处置0
        }
        else if(four_codes[i].op == PUSH){  //实际参数压栈
            if(four_codes[i].t3[0] >= '0' && four_codes[i].t3[0] <= '9'){
                itoa(-parcount*4, spchar, 10);
                entermips("addi", "$t1,", "$zero,", four_codes[i].t3);
                entermips("sw", "", "$t1,", (string)spchar + "($s0)");
            }
            else{
                if(four_codes[i].t3[0] == '#'){
                    tmpt = locate(four_codes[i].t3.erase(0, 1));
                }
                else if(four_codes[i].t3[0] == '%'){
                    tmpt = locate(four_codes[i].t3.substr(1, four_codes[i].t3.length()));

                    itoa(-tab[tmpt].spshift*4, spchar, 10);
                    entermips("lw", "", "$t2,", (string)spchar + "($sp)");
                    entermips("lw", "", "$t1,", "0($t2)");
                }
                else{
                    tmpt = locate(four_codes[i].t3);
                }

                if(tab[tmpt].level == level && four_codes[i].t3[0] != '%'){
                    if(tab[tmpt].type == varpar){
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("lw", "", "$t2,", (string)spchar + "($sp)");
                        entermips("lw", "", "$t1,", "0($t2)");
                    }
                    else{
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("lw", "", "$t1,", (string)spchar + "($sp)");
                        entermips("addi", "$t2,", "$sp,", (string)spchar);
                    }
                }
                else if(tab[tmpt].level != level){
                    itoa(-tab[tmpt].level*4, spchar, 10);
                    entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                    itoa(-tab[tmpt].spshift*4, spchar, 10);
                    entermips("lw", "", "$t1,", (string)spchar + "($t0)");
                    entermips("addi", "$t2,", "$t0,", (string)spchar);
                }

                itoa(-parcount*4, spchar, 10);
                entermips("sw", "", "$t1,", (string)spchar + "($s0)");
                itoa(-(parcount + 1)*4, spchar, 10);
                entermips("sw", "", "$t2,", (string)spchar + "($s0)");
            }

            parcount += 2;  //实际参数计数，在call处置0
        }
        else if(four_codes[i].op == CALL){  //调用函数
            parcount = 0;
            tmpt = locate(four_codes[i].t3);

            itoa(-(tab[display[level]].value*4 + spreturnshift), spchar, 10);
            entermips("sw", "", "$sp,", (string)spchar + "($sp)");

            for(int k = 0; k < displaylength; k++){ //拷贝display区
                itoa(-k*4, spchar, 10);
                entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                itoa(-(tab[display[level]].value + k)*4, spchar, 10);
                entermips("sw", "", "$t0,", (string)spchar + "($sp)");
            }
            if(tab[tmpt].level - level == 0){   //对于内层函数的调用写入一个新的display地址
                itoa(-(tab[display[level]].value + level)*4, spchar, 10);
                entermips("sw", "", "$sp,", (string)spchar + "($sp)");
            }

            itoa(-tab[display[level]].value*4, spchar, 10);
            entermips("addi", "$sp,", "$sp,", (string)spchar);

            entermips("jal", "", "", four_codes[i].t3);
        }
        else if(four_codes[i].op == VART){   //临时变量空间声明处理
            tmpt = atoi(four_codes[i].t3.c_str());
            for(int k = 0; k < tmpt; k++){
                itoa(k, spchar, 10);
                tab[t].name = (string)spchar;
                tab[t].level = level;
                tab[t].countt = tab[t - 1].countt + 1;
                tab[t].value = 1;
                tab[t].spshift = tab[t - 1].spshift + tab[t - 1].value;
                tab[t].type = normal;
                t += 1;
            }

            tab[display[level]].value = tab[t - 1].spshift + tab[t - 1].value;
            tab[display[level]].countt = tab[t - 1].countt;
            tab[display[level]].spshift = returnvalueshift/4;

            parcount = 0;
        }
        else if(four_codes[i].op == LABEL){               //标记生成
            entermips(four_codes[i].t3 + ":", "", "", "");
        }

        else if(four_codes[i].op == READ){
            tmpt = locate(four_codes[i].t3);
            if(tab[tmpt].vtype == 2){
                entermips("addi", "$v0,", "$zero,", "12");
            }
            else{
                entermips("addi", "$v0,", "$zero,", "5");
            }

            entermips("syscall", "", "", "");

            if(tab[tmpt].level == level){
                itoa(-tab[tmpt].spshift*4, spchar, 10);
                entermips("sw", "", "$v0,", (string)spchar + "($sp)");
            }
            else{
                itoa(-tab[tmpt].level*4, spchar, 10);
                entermips("sw", "", "$v0,", (string)spchar + "($sp)");
                itoa(-tab[tmpt].spshift*4, spchar, 10);
                entermips("sw", "", "$v0,", (string)spchar + "($t0)");
            }
        }
        else if(four_codes[i].op == WRITE){

            if(four_codes[i].t3[0] == '\"'){
                int charnum;
                entermips("addi", "$v0,", "$zero,", "11");

                for(int j = 1; j < four_codes[i].t3.length()-1; j++){
                    charnum = four_codes[i].t3[j] - '\0';
                    itoa(charnum, spchar, 10);
                    entermips("addi", "$a0,", "$zero,", (string)spchar);
                    entermips("syscall", "", "", "");
                }
            }
            else{
                if(four_codes[i].t3[0] >= '0' && four_codes[i].t3[0] <= '9'){   //取一个操作数
                    entermips("addi", "$v0,", "$zero,", "1");
                    entermips("addi", "$a0,", "$zero", four_codes[i].t3);
                }
                else if(four_codes[i].t3[0] == '#'){
                    entermips("addi", "$v0,", "$zero,", "1");
                    tmpt = locate(four_codes[i].t3.erase(0, 1));

                    itoa(-tab[tmpt].spshift*4, spchar, 10);
                    entermips("lw", "", "$a0,", (string)spchar + "($sp)");
                }
                else if(four_codes[i].t3[0] == '%'){
                    entermips("addi", "$v0,", "$zero,", "1");
                    tmpt = locate(four_codes[i].t3.erase(0, 1));

                    itoa(-tab[tmpt].spshift*4, spchar, 10);
                    entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                    entermips("lw", "", "$a0,", "0($t0)");
                }
                else{
                    tmpt = locate(four_codes[i].t3);

                    if(tab[tmpt].vtype == 2){
                        entermips("addi", "$v0,", "$zero,", "11");
                    }
                    else{
                        entermips("addi", "$v0,", "$zero,", "1");
                    }

                    if(tab[tmpt].type == normal || tab[tmpt].type == func){
                        if(tab[tmpt].level == level){
                            itoa(-tab[tmpt].spshift*4, spchar, 10);
                            entermips("lw", "", "$a0,", (string)spchar + "($sp)");
                        }
                        else{
                            itoa(-tab[tmpt].level*4, spchar, 10);
                            entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                            itoa(-tab[tmpt].spshift*4, spchar, 10);
                            entermips("lw", "", "$a0,", (string)spchar + "($t0)");
                        }
                    }
                    else if(tab[tmpt].type == varpar){  //变量形参
                        itoa(-tab[tmpt].spshift*4, spchar, 10);
                        entermips("lw", "", "$t0,", (string)spchar + "($sp)");
                        entermips("lw", "", "$a0,", "0($t0)");
                    }
                }
                entermips("syscall", "", "", "");
            }
        }
    }
}

void print_mips()
{
    int i;

    freopen("out.asm","w", stdout);
    for(i = 0; i < mc; i++){
        printf("%s %s %s %s\n", mips_codes[i].op.c_str(), mips_codes[i].rs.c_str(), mips_codes[i].rt.c_str(), mips_codes[i].rd.c_str());
    }
}

int main()
{
    freopen("out.txt", "r", stdin);
    getfour_code();

    gen_mips();

    print_mips();
    return 0;
}
