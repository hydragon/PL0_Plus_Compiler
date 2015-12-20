#ifndef FOUR_CODE_H_INCLUDED
#define FOUR_CODE_H_INCLUDED

#include "compiler_head.h"

string gen_code(enum four_code_option op, string t1, string t2, string t3)
{
    static int tno = 0, beginno = 0, ifno = 0, elseno = 0, forloopno = 0, forendno = 0, caseno = 0, caseendno = 0; //临时变量、跳转标记计数
    int vartno = 0; //记录临时变量声明的四元式位置
    char c_tno[20];

    if(op == ADD || op == SUB || op == MUL || op == DIV || op == ARRAY){    //运算符及数组操作生成
        four_codes[fc].op = op;
        four_codes[fc].t1 = t1;
        four_codes[fc].t2 = t2;
        if(t3 == "#" || t3 == "%"){
            itoa(tno, c_tno, 10);
            four_codes[fc].t3 = t3 + (string)c_tno;
            tno += 1;
        }
        else{
            four_codes[fc].t3 = t3;
        }
        t3 = four_codes[fc].t3;
        fc += 1;
    }
    else if(op == BNE || op == BEQ || op == BGEZ || op == BGTZ || op == BLEZ || op == BLTZ){    //条件跳转生成
        four_codes[fc].op = op;
        four_codes[fc].t1 = t1;
        four_codes[fc].t2 = t2;
        if(t3 == "if"){
            itoa(ifno, c_tno, 10);
            four_codes[fc].t3 = t3 + (string)c_tno;
            ifno += 1;
        }
        else if(t3 == "case"){
            itoa(caseno, c_tno, 10);
            four_codes[fc].t3 = "case" + (string)c_tno;
            caseno += 1;
        }
        else if(t3 == "for"){
            itoa(forendno, c_tno, 10);
            four_codes[fc].t3 = "forend" + (string)c_tno;
            forendno += 1;
        }
        t3 = four_codes[fc].t3;
        fc += 1;
    }
    else if(op == J){                                           //无条件跳转生成
        four_codes[fc].op = op;
        if(t3 == "else"){
            itoa(elseno, c_tno, 10);
            four_codes[fc].t3 = t3 + (string)c_tno;
            elseno += 1;
        }
        else if(t3 == "begin"){
            itoa(beginno, c_tno, 10);
            four_codes[fc].t3 = t3 + (string)c_tno;
            beginno += 1;
        }
        else{
            four_codes[fc].t3 = t3;
        }
        t3 = four_codes[fc].t3;
        fc += 1;
    }
    else if(op == JR){
        four_codes[fc].op = op;
        tno = 0;
        fc += 1;
    }
    else if(op == DEC || op == PAR || op == VAR || op == CON || op == CALL || op == PUSH || op == POP){    //声明语句和调用语句生成
        four_codes[fc].op = op;
        four_codes[fc].t1 = t1;
        four_codes[fc].t2 = t2;
        four_codes[fc].t3 = t3;
        fc += 1;
    }
    else if(op == VART){   //临时变量空间声明处理
        if(t1 == "0"){
            four_codes[fc].op = op;
            four_codes[fc].t3 = "0";
            itoa(fc, c_tno, 10);
            t3 = (string)c_tno;
            fc += 1;
        }
        else if(t1 == "1"){
            vartno = atoi(t2.c_str());
            itoa(tno, c_tno, 10);
            four_codes[vartno].t3 = (string)c_tno;
        }
    }
    else if(op == LABEL && t3 != "case"){               //标记生成
        four_codes[fc].op = op;
        if(t3 == "for"){
            itoa(forloopno, c_tno, 10);
            four_codes[fc].t3 = t3 + (string)c_tno;
            forloopno += 1;
        }
        else{
            four_codes[fc].t3 = t3;
        }
        t3 = four_codes[fc].t3;
        fc += 1;
    }
    else if(op == LABEL && t3 == "case"){               //case语句预申请标记
        itoa(caseendno, c_tno, 10);
        t3 = "caseend" + (string)c_tno;
        caseendno += 1;
    }
    else if(op == READ){
        four_codes[fc].op = op;
        four_codes[fc].t3 = t3;
        fc += 1;
    }
    else if(op == WRITE){
        four_codes[fc].op = op;
        four_codes[fc].t3 = t3;
        fc += 1;
    }
    return t3;
}

void print_four_code()
{
    int i;
    string op;
    freopen("out.txt","w", stdout);

    for(i = 0; i < fc; i++){
        switch(four_codes[i].op){
            case ADD : {op = "ADD"; break;}
            case SUB : {op = "SUB"; break;}
            case MUL : {op = "MUL"; break;}
            case DIV : {op = "DIV"; break;}
            case BEQ : {op = "BEQ"; break;}
            case BGEZ: {op = "BGEZ"; break;}
            case BGTZ: {op = "BGTZ"; break;}
            case BLEZ: {op = "BLEZ"; break;}
            case BLTZ: {op = "BLTZ"; break;}
            case BNE : {op = "BNE"; break;}
            case ARRAY : {op = "ARRAY"; break;}
            case J   : {op = "J"; break;}
            case JR  : {op = "JR"; break;}
            case LABEL:{op = "LABEL"; break;}
            case DEC : {op = "DEC"; break;}
            case PAR : {op = "PAR"; break;}
            case CON : {op = "CON"; break;}
            case VAR : {op = "VAR"; break;}
            case VART: {op = "VART"; break;}
            case CALL: {op = "CALL"; break;}
            case PUSH: {op = "PUSH"; break;}
            case POP : {op = "POP"; break;}
            case READ: {op = "READ"; break;}
            case WRITE:{op = "WRITE"; break;}
        }
        printf("%-3d . %-8s %-14s %-14s %-14s\n", i, op.c_str(), four_codes[i].t1.c_str(), four_codes[i].t2.c_str(), four_codes[i].t3.c_str());
    }
}

#endif // FOUR_CODE_H_INCLUDED
