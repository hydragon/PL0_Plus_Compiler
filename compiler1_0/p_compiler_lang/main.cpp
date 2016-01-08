#include "compiler_head.h"
#include "four_code.h"
/************

词法分析部分

*************/

void getch()                    //读取一个字符
{
    ch = getchar();
    if(ch == EOF){  //程序不完整
        error(0);
        exit(-1);
    }
    cc += 1;
    if(ch == '\n'){ //一行结束
        cx += 1;
        ll = cc;
        cc =0;
    }
}//getch end

void nextsym()                                          //读取一个单词
{
    alfa.clear();
    inum = 0;
    sy = nul;
    while(ch == ' ' || ch == '\t' || ch == '\n'){   //消除空字符
        getch();
    }
    if((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')){ //读取一个标识符或关键字
        do{
            if(ch >= 'A'&&ch <= 'Z'){
                ch = ch - 'A' + 'a';
            }
            if((ch >= 'a'&&ch <= 'z') || (ch >= '0'&& ch <= '9')){
                alfa += ch;
            }
            getch();
        }while((ch >= 'A'&&ch <= 'Z')||(ch >= 'a'&&ch <= 'z') || (ch >= '0'&& ch <= '9'));
        if( alfa.length() <= alng ){
            int i = 0,j = nkw - 1, k;
            for(; i <= j; ){
                k = (i + j)/2;
                if (alfa < key[k])
                    j = k - 1;
                else if (alfa > key[k])
                    i = k + 1;
                else if (alfa == key[k])
                    break;
            }
            if( alfa == key[k] ){
                sy = ksy[k];
            }
            else{
                sy = ident;
            }
        }
        else{
            sy = nul;
            error(1);  //标识符过长
        }
    }
    else if(ch >= '0'&&ch <= '9'){  //读取一个整数
        inum = 0;
        sy = intcon;
        do{
            alfa += ch;
            inum = inum*10 + (ch-'0');
            getch();
        }while(ch >= '0'&&ch <= '9' && alfa.length()<=kmax );
        if( alfa.length() > kmax ){
            sy = nul;
            error(2);  //整数过长
        }
    }
    else if(ch == ':'){ //读取一个赋值符或冒号
        alfa += ch;
        getch();
        if (ch == '='){
            alfa += ch;
            sy = becomes;
            getch();
        }
        else{
            sy = colon;
        }
    }
    else if(ch == '<'){ //小于，小于等于，不等于
        alfa += ch;
        getch();
        if(ch == '='){
            alfa += ch;
            sy = leq;
            getch();
        }
        else if(ch == '>'){
            alfa += ch;
            sy = neq;
            getch();
        }
        else sy = lss;
    }
    else if(ch == '>'){ //大于，大于等于
        getch();
        if(ch == '='){
            alfa += ch;
            sy = geq;
            getch();
        }
        else sy = gtr;
    }
    else if(ch == '.'){ //句点，结束符
        alfa += ch;
        sy = period;
    }
    else if(ch == '\''){    //单引号，读一个字符
        alfa += ch;
        getch();
        if((ch >= 'A'&&ch <= 'Z')||(ch >= 'a'&&ch <= 'z') || (ch >= '0'&& ch <= '9')){
            alfa += ch;
            getch();
            if(ch == '\''){
                alfa += ch;
                sy = charcon;
                getch();
            }
            else{
                sy = nul;
                error(3);  //缺少右单引号
            }
        }
        else{
            getch();
            if( ch == '\''){
                error(4);  //非法字符常量
                getch();
            }
            else{
                error(5);  //多余的单引号
            }
        }
    }
    else if(ch == '\"'){    //双引号，读一个字符串
        alfa += ch;
        getch();
        while(ch == '\x20' || ch == '\x21' || (ch >= '\x23' && ch <= '\x7E')){
            alfa += ch;
            line += ch;
            getch();
        }
        if(ch == '\"'){
            alfa += ch;
            sy = stringcon;
            getch();
        }
        else{
            error(6);      //缺少右双引号
        }
        line.clear();
    }
    else{                   //读取其他合法字符：'+','-','*','/','(',')','[',']','=',',',':',';'
        alfa += ch;
        sy = sps[ch];
        if( sy == nul ){
            error(7);      //一个非法字符
        }
        getch();
    }
}//nextsym end

/*** 词法分析结束 ***/

/************

语法分析部分

*************/

void entertable(string name, enum objecttype k)     //将一个标识符写入符号表
{
    int j,l;
    if(t == tmax){
        error(8);    //符号表溢出
        exit(-1);
    }
    else{
        tab[0].name = name;
        j = btab[display[level]].last;
        l = j;
        while(tab[j].name != name){
            j = tab[j].link;
        }
        if(j != 0){
            error(9);   //标识符重定义
        }
        else{
            t = t + 1;
            tab[t].name = name;
            tab[t].link = l;
            tab[t].obj = k;
            tab[t].typ = notype;
            tab[t].refer = 0;
            tab[t].level = level;
            tab[t].adr = 0;
            tab[t].ifvar = 0;
        }
        btab[display[level]].last = t;
    }
}//entertable end

int locate(string name)     //在符号表查标识符
{
    int i,j;
    i = level;
    tab[0].name = name;
    do{
        j = btab[display[i]].last;
        while(tab[j].name != name && j != 0){
            j = tab[j].link;
        }
        i = i - 1;
    }while(i >= 0 && j == 0);
    if(j == 0){
        error(10); //未定义的标识符
    }
    return j;
}//locate end

void entervar() //变量写入符号表
{
    if(sy == ident){
        entertable(alfa, vartype);
        nextsym();
    }
    else
        error(12);  //不是一个合法的标识符名
}

void constant() //取常量值
{

    if(sy == intcon ){
        tab[t].typ = inttype;
        nextsym();
    }
    else if(sy == charcon){
        tab[t].typ = chartype;
        nextsym();
    }
    else
        error(11);   //非法的常量值
}//constant end

int parameterlist()
{
    enum valuetype typ = notype;
    int t0 = t, rf = 0, sz = 0, isvar = 0, paranumber = 0;
    nextsym();
    while(sy == ident || sy == varsy){
        if(sy != varsy){
            isvar = 0;
        }
        else{
            nextsym();
            isvar = 1;
        }
        t0 = t;
        paranumber += 1;
        entervar();
        while(sy == comma){
            nextsym();
            paranumber += 1;
            entervar();
        }
        if(sy == colon){
            nextsym();
        }
        else
            error(13);  //应该有冒号，定义参数类型
        if( sy == charcon || sy == intcon){
            if(alfa == "integer"){ //整型
                typ = inttype;
                rf = 0;
                sz = 1;
                nextsym();
            }
            else if(alfa == "char"){    //字符型
                typ = chartype;
                rf = 0;
                sz = 1;
                nextsym();
            }
            else
                error(14);   //非法参数类型
        }
        while(t0 < t){ //将参数信息填入符号表, 顺便生成四元式
            t0 = t0 + 1;
            if(isvar == 1){
                gen_code(PAR, "v", (typ == inttype)? "i" : "c", tab[t0].name);
            }
            else{
                gen_code(PAR, "n", (typ == inttype)? "i" : "c", tab[t0].name);
            }

            tab[t0].typ = typ;
            tab[t0].refer = rf;
            tab[t0].level = level;
            tab[t0].adr = 0; //****************偏移量有问题
            tab[t0].ifvar = isvar;
        }
        if(sy == semicolon){
            nextsym();
        }
        else if(sy == rparent){
            break;
        }
        else{
            error(15);  //分隔符应该为分号
            nextsym();
        }
    }
    if(sy == rparent){
        nextsym();
    }
    else
        error(16);  //缺少右括号

    if(paranumber == 0){
        error(57);  //参数表中至少有一个参数
    }
    return paranumber;
}//parameterlist end

void constdeclare()                     //常量声明处理
{
    string identname;

    //printf("Line%d: char(%d): This is a const declaration.\n", cx , ll);
    nextsym();

    while(sy == ident){
        identname = alfa;
        entertable(alfa, consttype);
        nextsym();
        if(sy == eql){
            nextsym();
            if(sy == charcon){
                gen_code(CON, alfa, "", identname);
            }
            else if(sy == intcon){
                gen_code(CON, alfa, "", identname);
            }
            else if(sy == minussy){
                nextsym();
                if(sy == intcon){
                    gen_code(CON, "-" + alfa, "", identname);
                }
                else{
                    error(11);
                }
            }
            else{
                error(11);
            }
        }
        else if(sy == becomes){
            error(17);   //常量赋值符应该为等号
        }
        else{
            error(18);   //应该有等号为常量赋值
        }
        constant();
        if(sy == semicolon){
            break;
        }
        else if(sy == comma){
            nextsym();
        }
        else{
            error(19);  //每个常量声明应该有逗号分隔
        }
    }
    if(sy == semicolon){
        nextsym();
    }
    else{
        error(20);  //常量声明结尾应该有分号
    }
}//constdeclare end

void vardeclare()                       //变量声明处理
{
    enum valuetype typ = notype;
    int t0 = t, t1 = t, rf, sz;
    string arraylength;

    nextsym();//printf("Line%d: char(%d): This is a var declaration.\n", cx , ll);
    while(sy == ident){
        t0 = t;
        entertable(alfa, vartype);
        nextsym();
        while(sy == comma){
            nextsym();
            if(sy == ident){
                entertable(alfa, vartype);
                nextsym();
            }
            else
                error(21);  //逗号后面必须有标识符
        }
        if(sy == colon){
            nextsym();
        }
        else
            error(22);  //变量声明必须有冒号后面声明类型
        t1 = t;
        if(sy == arraysy || sy == charcon || sy == intcon){
            if(sy == arraysy){          //数组声明处理
                nextsym();
                if(sy == lbrack){
                    nextsym();
                }
                else
                    error(23);  //缺少左中括号
                typ = arraytype;
                if(sy == intcon){
                    if(inum != 0){
                        arraylength = alfa;
                        atab[a].high = inum - 1;
                        atab[a].asize = inum;
                        nextsym();
                        if(sy == rbrack){
                            nextsym();
                        }
                        else
                            error(24);  //缺少右中括号
                        if(sy == ofsy){
                            nextsym();
                        }
                        else
                            error(25);  //缺少of
                        if(sy == intcon || sy == charcon){
                            if(alfa == "integer"){
                                atab[a].type = inttype;
                            }
                            else if(alfa == "char"){
                                atab[a].type = chartype;
                            }
                            nextsym();
                        }
                        else
                            error(26);  //非法数组类型
                        sz = atab[a].asize;
                        rf = a;
                        a += 1;
                        if (a == amax){
                            error(27);  //数组表溢出
                            exit(-1);
                        }
                    }
                    else{
                        error(53);  //数组定义上界必须大于0
                    }
                }
                else{
                    error(54);  //数组定义上标只能是正整数
                }
            }
            else if(alfa == "integer"){ //整型
                typ = inttype;
                rf = 0;
                sz = 1;
                nextsym();
            }
            else if(alfa == "char"){    //字符型
                typ = chartype;
                rf = 0;
                sz = 1;
                nextsym();
            }
            else
                error(28);  //非法的变量类型
        }
        while(t0 < t1){ //填符号表，顺便生成四元式
            t0 = t0 + 1;

            if(typ == arraytype){
                gen_code(VAR, "a", arraylength, tab[t0].name);
            }
            else{
                gen_code(VAR, "n", (typ == inttype)? "i" : "c", tab[t0].name);
            }

            tab[t0].typ = typ;
            tab[t0].refer = rf;
            tab[t0].level = level;
            tab[t0].adr = 0; //****************偏移量有问题
            tab[t0].ifvar = 0;
        }
        if(sy == semicolon){
            nextsym();
        }
        else{
            error(29);       //应该有分号
            if(sy == comma)
                nextsym();
        }
    }
}//vardeclaration end
void block();
void procdeclare()
{
    int isfunc = 0,
        paranumber = 0,
        prt = 0,
        prb = 0;
    string procname;

    if(sy == funcsy)
        isfunc = 1;
    nextsym();
    if(sy != ident){
        error(30);  //没有函数或过程名
    }
    procname = alfa;
    if(isfunc == 1){
        gen_code(DEC, "f", "", procname);
        entertable(alfa, functype);printf("Line%d: char(%d): This is a func declaration.\n", cx , ll);
    }
    else{
        gen_code(DEC, "p", "", procname);
        entertable(alfa, proctype);printf("Line%d: char(%d): This is a proc declaration.\n", cx , ll);
    }
    prt = t;
    nextsym();

    level += 1;             //level+1,进入下一层分程序，更改display区。
    if(level >= lmax){
        error(34);  //嵌套层次过多
        exit(-1);
    }
    if(b >= bmax){
        error(35);  //分程序表溢出
        exit(-1);
    }
    b = b + 1;
    btab[b].last = 0;
    btab[b].lastpar = 0;
    display[level] = b;
    tab[prt].refer = b;//printf("%s %d\n",tab[prt].name.c_str(), tab[prt].refer);

    if(sy == lparent){
        paranumber = parameterlist();
    }
    if(isfunc == 1){
        if(sy == colon){
            nextsym();
        }
        else
            error(31);   //函数需要有返回值类型
        if(sy == intcon || sy == charcon){
            tab[prt].typ = (sy == intcon)?inttype : chartype;
            nextsym();
        }
        else
            error(32);  //非法的函数的返回值类型
    }
    if(sy == semicolon){
        nextsym();
    }
    else{
        error(33);  //过程和函数声明结尾应有分号
        if(sy == comma)
            nextsym();
    }

    btab[b].pnum = paranumber;//参数个数统计

    block();                //进入下一层分程序

    gen_code(JR, "", "", "");
    if(sy == semicolon){
        nextsym();
    }
    else
        error(36);  //每个分程序结束应有分号
}//procdeclare end

string simpleexp();
string arrayselector()          //数组选取
{
    string first;

    if(sy != lbrack){
        error(23);  //缺左中括号
    }
    nextsym();
    first = simpleexp();
    if(sy == rbrack){
        nextsym();
    }
    else
        error(24);  //缺右中括号
    return first;
}//arrayselector end

void call(int btabrefer, string procname)
{
    string paraname[20];

    int paranumber = 0,
        paracount = 0;
    //printf("Line%d: char(%d): This is a call.\n", cx , ll);
    if(sy == lparent){
        do{
            nextsym();
            paraname[paranumber] = simpleexp();
   //         gen_code(PUSH, "", "", paraname);
            paranumber += 1;
        }while(sy == comma);
        if(sy == rparent){
            nextsym();
        }
        else
            error(16);   //缺右括号

        while(paracount < paranumber){  //生成传参数的四元式
            gen_code(PUSH, "", "", paraname[paracount]);
            paracount++;
        }
    }

    gen_code(CALL, "", "", procname);

    if(paranumber != btab[btabrefer].pnum){
        error(56);  //参数个数错误
    }
}//call end

string factor()           //因子处理
{
    int i, f, ivalue;
    enum valuetype typ = notype;
    string first, second;
    int refer = 0;
    if(sy == intcon || sy == ident || sy == lparent){
        if(sy == intcon){
            typ = inttype;
            refer = 0;
            ivalue = inum;
            first = alfa;
            nextsym();
        }
        else if(sy == ident){
            i = locate(alfa);//printf("getident %d %s\n", i, tab[i].name.c_str());
            first = alfa;
            nextsym();
            switch(tab[i].obj)
            {
                case consttype : {typ = tab[i].typ;
                                  refer = 0;
                                  ivalue = tab[i].adr;
                                  break;
                                  }
                case vartype   : {typ = tab[i].typ;
                                  refer = tab[i].refer;
                                  if(sy == lbrack){
                                    second = arrayselector();
                                    first = gen_code(ARRAY, first, second, "%");
                                  }
                                  break;
                                  }
                case functype  : {typ = tab[i].typ;
                                  call(tab[i].refer, first);
                                  first = gen_code(ADD, first, "0", "#");
                                  break;
                                  }
                case proctype  : error(37); //过程不能参与运算
            }
        }
        else if(sy == lparent){
            nextsym();
            first = simpleexp();
            if(sy == rparent){
                nextsym();
            }
            else
                error(16);  //缺右括号
        }
    }
    else{
        error(38);  //非法的因子
        nextsym();
    }
    return first;
}//factor end

string term()                 //项处理
{
    int refer = 0;
    enum symbol op;
    enum valuetype typ;
    string first,second;

    first = factor();
    while(sy == multi || sy == divsy){
        op = sy;
        nextsym();
        second = factor();
        if(op == multi){
            first = gen_code(MUL, first, second, "#");
        }
        else if(op == divsy){
            first = gen_code(DIV, first, second, "#");
        }
    }
    return first;
}//term end

string simpleexp()         //简单表达式处理
{

    int refer = 0;//printf("Line%d: char(%d): This is a simple expression.\n", cx , ll);
    enum symbol op;
    enum valuetype typ;
    string first,second;

    if(sy == plussy || sy == minussy){
        op = sy;
        nextsym();
        first = term();
        if(op == minussy){
            first = gen_code(SUB, "0", first, "#");
        }
    }
    else{
        first = term();
    }
    while(sy == plussy || sy == minussy){
        op = sy;
        nextsym();
        second = term();
        if(op == plussy){
            first = gen_code(ADD, first, second, "#");
        }
        else{
            first = gen_code(SUB, first, second, "#");
        }
    }
    return first;
}//simpleexp end

string conditionexp()        //条件表达式处理
{
    string first,second;
    enum four_code_option op;
    //printf("Line%d: char(%d): This is a conditional expression.\n", cx , ll);
    first = simpleexp();
    if(sy == eql || sy == neq || sy == gtr || sy == geq || sy == leq || sy == lss){
        if(sy == eql){
            op = BNE;
        }
        else if(sy == neq){
            op = BEQ;
        }
        else if(sy == gtr){
            op = BLEZ;
        }
        else if(sy == geq){
            op = BLTZ;
        }
        else if(sy == leq){
            op = BGTZ;
        }
        else if(sy == lss){
            op = BGEZ;
        }
        nextsym();
    }
    else{
        error(39);  //非法的关系运算符
    }
    second = simpleexp();
    first = gen_code(op, first, second, "if");
    return first;
}//conditionexp end

void assignment(string first)       //赋值语句处理
{
    enum valuetype typ;
    string second;
    //printf("Line%d: char(%d): This is a assignment statement.\n", cx , ll);
    if(sy == lbrack){
        second = arrayselector();
        first = gen_code(ARRAY, first, second, "%");
    }
    if(sy == becomes){
        nextsym();
        second = simpleexp();
        gen_code(ADD, "0", second, first);
    }
    else
        error(39);  //缺少赋值符号
/*    if(typ == chartype){
        if(sy == becomes){
            nextsym();
            if(sy == charcon){

            }
            else
                error(0);
        }
        else
            error(0);
    }
    else if(typ == inttype){
        if(sy == becomes){
            nextsym();
            simpleexp();

        }
    }*/
}//assignment end
void statement();
void compoundstatement()        //复合语句处理
{
    nextsym();//printf("Line%d: char(%d): This is a compound statement.\n", cx , ll);
    statement();
    while(sy == semicolon || sy == beginsy || sy == ifsy || sy == casesy || sy == forsy){
        if(sy != semicolon){
            error(40);  //复合语句中每条语句结尾应有分号
        }
        else
            nextsym();
        statement();
    }
    if(sy == endsy){
        nextsym();
    }
    else
        error(41);  //缺少end
}//compoundstatement end

void ifstatement()          //判断语句处理
{
    string label1, label2;
    nextsym();//printf("Line%d: char(%d): This is a if statement.\n", cx , ll);
    label1 = conditionexp();
    if(sy == thensy){
        nextsym();
    }
    else
        error(42);   //缺少then
    statement();

    if(sy == elsesy){
        label2 = gen_code(J, "", "", "else");
        gen_code(LABEL, "", "", label1);
        nextsym();
        statement();
        gen_code(LABEL, "", "", label2);
    }
    else{
        gen_code(LABEL, "", "", label1);
    }
}//ifstatement end

void casestatement()        //条件语句处理
{
    string first, second;
    string label1, label2;
    char value[20];//存储字符转换成整数后的字符串形式
    nextsym();
    //printf("Line%d: char(%d): This is a case statement.\n", cx , ll);

    first = simpleexp();
    if(sy == ofsy){
        nextsym();
    }
    else
        error(42);  //缺少of
    label1 = gen_code(LABEL, "", "", "case");
    while(sy == charcon || sy == intcon){
        if(sy == charcon){
            itoa(alfa[1] - '\0', value, 10);
            second = (string)value;
        }
        else{
            second = alfa;
        }
        label2 = gen_code(BNE, first, second, "case");
        nextsym();
        if(sy == colon){
            nextsym();
            statement();
        }
        else{
            error(43);  //情况语句每个常量判断后面应有冒号
        }
        gen_code(J, "", "", label1);
        gen_code(LABEL, "", "", label2);
        if(sy == endsy){
            break;
        }
        if(sy != semicolon){
            error(44);  //情况语句每个分支的结尾需要分号
        }
        else{
            nextsym();
        }
    }
    gen_code(LABEL, "", "", label1);
    if(sy == endsy){
        nextsym();
    }
    else{
        error(41);  //缺少end
    }
}//casestatement end

void forstatement()         //循环语句处理
{
    int i;
    string first, second;
    string label1, label2;
    enum four_code_option op, calop;
    nextsym();//printf("Line%d: char(%d): This is a for statement.\n", cx , ll);
    if(sy == ident){
        i = locate(alfa);
        first = alfa;
        if(tab[i].obj == vartype && tab[i].typ != arraytype){
            nextsym();
            assignment(first);
        }
        else
            error(52);  //for循环变量不合法
        label1 = gen_code(LABEL, "", "", "for");

        if(sy == tosy || sy == downtosy){
            op = (sy == tosy) ? BGTZ : BLTZ;
            calop = (sy == tosy) ? ADD : SUB;
            nextsym();
            second = simpleexp();
        }
        else
            error(45);  //应有to或downto
        label2 = gen_code(op, first, second, "for");

        if(sy == dosy){
            nextsym();
            statement();
        }
        else
            error(46);  //应有do

        gen_code(calop, first, "1", first);
        gen_code(J, "", "", label1);
        gen_code(LABEL, "", "", label2);
    }
}//forstatement end

void readproc()        //read处理
{
    int i;

    nextsym();//printf("Line%d: char(%d): This is a read statement.\n", cx , ll);
    if(sy == lparent){
        nextsym();
    }
    else
        error(47);  //缺少左括号
    if(sy == ident){
        i = locate(alfa);
        if(tab[i].obj != vartype){
            error(55);  //read语句中实参必须是变量
        }
        gen_code(READ, "", "", alfa);
        nextsym();
    }
    else
        error(48);  //应该是一个标识符
    while(sy == comma){
        nextsym();
        i = locate(alfa);
        if(sy == ident){
            if(tab[i].obj != vartype){
                error(55);
            }
            gen_code(READ, "", "", alfa);
            nextsym();
        }
        else
            error(48);  //应该是一个标识符
    }
    if(sy == rparent){
        nextsym();
    }
    else
        error(16);  //缺少右括号
}//readproc end

void writeproc()        //write处理
{
    string first;
    nextsym();//printf("Line%d: char(%d): This is a write statement.\n", cx , ll);
    if(sy == lparent){
        nextsym();
    }
    else
        error(47);  //缺少左括号
    if(sy == stringcon){

        gen_code(WRITE, "", "", alfa);
        nextsym();
        if(sy == comma){
            nextsym();
            first = simpleexp();
            gen_code(WRITE, "", "", first);
        }
    }
    else{
        first = simpleexp();
        gen_code(WRITE, "", "", first);
    }
    if(sy == rparent){
        nextsym();
    }
    else
        error(16);  //缺少右括号
}//writeproc end

void statement()        //语句处理
{
    int i;
    string first;

    if(sy == ident){
        i = locate(alfa);
        first = alfa;
        if(tab[i].obj == proctype){
            nextsym();
            call(tab[i].refer, first);
        }
        else if(tab[i].obj == vartype || tab[i].obj == functype){
            nextsym();
            assignment(first);
        }
        else if(tab[i].obj == consttype){
            error(51);    //常量不能被赋值
        }
    }
    else if(sy == beginsy)
        compoundstatement();
    else if(sy == ifsy)
        ifstatement();
    else if(sy == casesy)
        casestatement();
    else if(sy == forsy)
        forstatement();
    else if(sy == readsy)
        readproc();
    else if(sy == writesy)
        writeproc();
    else;
      //  error(49);  //不合法的语句起始符
}//statement end

void block()        //分程序处理
{
    string vartstring,  //记录临时变量声明的四元式地址
            beginlabel; //过程和函数跳到函数体的标志

    if(sy == constsy){
        constdeclare();
    }
    if(sy == varsy){
        vardeclare();
    }
    vartstring = gen_code(VART, "0", "", "");   //生成临时变量声明的四元式
    beginlabel = gen_code(J, "", "", "begin");  //生成跳转至函数体的四元式

    while(sy == procsy || sy == funcsy){
            procdeclare();
    }

    gen_code(LABEL, "", "", beginlabel);    //
    if(sy == beginsy){
        compoundstatement();
    }
    else
        error(50);  //分程序必须有一个复合语句部分
    gen_code(VART, "1", vartstring, "");

    if(level == 0){
        if(sy == period){
            return;
        }
        else{
            error(58);  //程序结尾缺少句号
        }
    }

    level -= 1;
}//block end

void setup()        //初始化key，ksy，sps
{
    for(int i=0; i<256; i++){
        sps[i] = nul;
    }
    key[0] = "array";
    key[1] = "begin";
    key[2] = "case";
    key[3] = "char";
    key[4] = "const";
    key[5] = "do";
    key[6] = "downto";
    key[7] = "else";
    key[8] = "end";
    key[9] = "for";
    key[10] = "function";
    key[11] = "if";
    key[12] = "integer";
    key[13] = "of";
    key[14] = "procedure";
    key[15] = "read";
    key[16] = "then";
    key[17] = "to";
    key[18] = "var";
    key[19] = "write";

    ksy[0] = arraysy;
    ksy[1] = beginsy;
    ksy[2] = casesy;
    ksy[3] = charcon;
    ksy[4] = constsy;
    ksy[5] = dosy;
    ksy[6] = downtosy;
    ksy[7] = elsesy;
    ksy[8] = endsy;
    ksy[9] = forsy;
    ksy[10] = funcsy;
    ksy[11] = ifsy;
    ksy[12] = intcon;
    ksy[13] = ofsy;
    ksy[14] = procsy;
    ksy[15] = readsy;
    ksy[16] = thensy;
    ksy[17] = tosy;
    ksy[18] = varsy;
    ksy[19] = writesy;

    sps['+'] = plussy;
    sps['-'] = minussy;
    sps['*'] = multi;
    sps['/'] = divsy;
    sps['('] = lparent;
    sps[')'] = rparent;
    sps['='] = eql;
    sps[','] = comma;
    sps['['] = lbrack;
    sps[']'] = rbrack;
    sps[':'] = colon;
    sps[';'] = semicolon;
}//init end

void compiler_shell(){
    char filepath[200];
    string input_string;

    setup();

    while(1){
        printf("Please give the path of the file:");
        scanf("%s", filepath);
        input_string = string(filepath);

        if(input_string == "exit"){
            break;
        }

        if(freopen(filepath, "r", stdin)){
            nextsym();
            block();
            print_four_code();

            cc = 0,                 //读一行字符计数
            ll = 0,                 //上一行字符数
            cx = 0,                 //当前代码行数
            inum = 0,               //整数值存储
            level = 0,              //当前分程序层次
            t = 1,      //符号表地址
            a = 0,      //数组表地址
            b = 0,      //分程序表地址
            fc = 0;     //四元式表地址
            ch = ' ';              //每次读出的单个字符
            line = "",           //记录""中的字符串
            alfa = "";           //记录每次读出的字符串

            freopen("CON", "r", stdin);
        }
        else{
            freopen("CON", "r", stdin);
            printf("\nError: Can't found the file!\n\n");
        }
        break;
    }
}

int main()          //主函数
{
    compiler_shell();

    return 0;
}//main end
