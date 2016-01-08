#include "compiler_head.h"
#include "four_code.h"
/************

�ʷ���������

*************/

void getch()                    //��ȡһ���ַ�
{
    ch = getchar();
    if(ch == EOF){  //��������
        error(0);
        exit(-1);
    }
    cc += 1;
    if(ch == '\n'){ //һ�н���
        cx += 1;
        ll = cc;
        cc =0;
    }
}//getch end

void nextsym()                                          //��ȡһ������
{
    alfa.clear();
    inum = 0;
    sy = nul;
    while(ch == ' ' || ch == '\t' || ch == '\n'){   //�������ַ�
        getch();
    }
    if((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')){ //��ȡһ����ʶ����ؼ���
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
            error(1);  //��ʶ������
        }
    }
    else if(ch >= '0'&&ch <= '9'){  //��ȡһ������
        inum = 0;
        sy = intcon;
        do{
            alfa += ch;
            inum = inum*10 + (ch-'0');
            getch();
        }while(ch >= '0'&&ch <= '9' && alfa.length()<=kmax );
        if( alfa.length() > kmax ){
            sy = nul;
            error(2);  //��������
        }
    }
    else if(ch == ':'){ //��ȡһ����ֵ����ð��
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
    else if(ch == '<'){ //С�ڣ�С�ڵ��ڣ�������
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
    else if(ch == '>'){ //���ڣ����ڵ���
        getch();
        if(ch == '='){
            alfa += ch;
            sy = geq;
            getch();
        }
        else sy = gtr;
    }
    else if(ch == '.'){ //��㣬������
        alfa += ch;
        sy = period;
    }
    else if(ch == '\''){    //�����ţ���һ���ַ�
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
                error(3);  //ȱ���ҵ�����
            }
        }
        else{
            getch();
            if( ch == '\''){
                error(4);  //�Ƿ��ַ�����
                getch();
            }
            else{
                error(5);  //����ĵ�����
            }
        }
    }
    else if(ch == '\"'){    //˫���ţ���һ���ַ���
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
            error(6);      //ȱ����˫����
        }
        line.clear();
    }
    else{                   //��ȡ�����Ϸ��ַ���'+','-','*','/','(',')','[',']','=',',',':',';'
        alfa += ch;
        sy = sps[ch];
        if( sy == nul ){
            error(7);      //һ���Ƿ��ַ�
        }
        getch();
    }
}//nextsym end

/*** �ʷ��������� ***/

/************

�﷨��������

*************/

void entertable(string name, enum objecttype k)     //��һ����ʶ��д����ű�
{
    int j,l;
    if(t == tmax){
        error(8);    //���ű����
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
            error(9);   //��ʶ���ض���
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

int locate(string name)     //�ڷ��ű���ʶ��
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
        error(10); //δ����ı�ʶ��
    }
    return j;
}//locate end

void entervar() //����д����ű�
{
    if(sy == ident){
        entertable(alfa, vartype);
        nextsym();
    }
    else
        error(12);  //����һ���Ϸ��ı�ʶ����
}

void constant() //ȡ����ֵ
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
        error(11);   //�Ƿ��ĳ���ֵ
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
            error(13);  //Ӧ����ð�ţ������������
        if( sy == charcon || sy == intcon){
            if(alfa == "integer"){ //����
                typ = inttype;
                rf = 0;
                sz = 1;
                nextsym();
            }
            else if(alfa == "char"){    //�ַ���
                typ = chartype;
                rf = 0;
                sz = 1;
                nextsym();
            }
            else
                error(14);   //�Ƿ���������
        }
        while(t0 < t){ //��������Ϣ������ű�, ˳��������Ԫʽ
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
            tab[t0].adr = 0; //****************ƫ����������
            tab[t0].ifvar = isvar;
        }
        if(sy == semicolon){
            nextsym();
        }
        else if(sy == rparent){
            break;
        }
        else{
            error(15);  //�ָ���Ӧ��Ϊ�ֺ�
            nextsym();
        }
    }
    if(sy == rparent){
        nextsym();
    }
    else
        error(16);  //ȱ��������

    if(paranumber == 0){
        error(57);  //��������������һ������
    }
    return paranumber;
}//parameterlist end

void constdeclare()                     //������������
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
            error(17);   //������ֵ��Ӧ��Ϊ�Ⱥ�
        }
        else{
            error(18);   //Ӧ���еȺ�Ϊ������ֵ
        }
        constant();
        if(sy == semicolon){
            break;
        }
        else if(sy == comma){
            nextsym();
        }
        else{
            error(19);  //ÿ����������Ӧ���ж��ŷָ�
        }
    }
    if(sy == semicolon){
        nextsym();
    }
    else{
        error(20);  //����������βӦ���зֺ�
    }
}//constdeclare end

void vardeclare()                       //������������
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
                error(21);  //���ź�������б�ʶ��
        }
        if(sy == colon){
            nextsym();
        }
        else
            error(22);  //��������������ð�ź�����������
        t1 = t;
        if(sy == arraysy || sy == charcon || sy == intcon){
            if(sy == arraysy){          //������������
                nextsym();
                if(sy == lbrack){
                    nextsym();
                }
                else
                    error(23);  //ȱ����������
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
                            error(24);  //ȱ����������
                        if(sy == ofsy){
                            nextsym();
                        }
                        else
                            error(25);  //ȱ��of
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
                            error(26);  //�Ƿ���������
                        sz = atab[a].asize;
                        rf = a;
                        a += 1;
                        if (a == amax){
                            error(27);  //��������
                            exit(-1);
                        }
                    }
                    else{
                        error(53);  //���鶨���Ͻ�������0
                    }
                }
                else{
                    error(54);  //���鶨���ϱ�ֻ����������
                }
            }
            else if(alfa == "integer"){ //����
                typ = inttype;
                rf = 0;
                sz = 1;
                nextsym();
            }
            else if(alfa == "char"){    //�ַ���
                typ = chartype;
                rf = 0;
                sz = 1;
                nextsym();
            }
            else
                error(28);  //�Ƿ��ı�������
        }
        while(t0 < t1){ //����ű�˳��������Ԫʽ
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
            tab[t0].adr = 0; //****************ƫ����������
            tab[t0].ifvar = 0;
        }
        if(sy == semicolon){
            nextsym();
        }
        else{
            error(29);       //Ӧ���зֺ�
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
        error(30);  //û�к����������
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

    level += 1;             //level+1,������һ��ֳ��򣬸���display����
    if(level >= lmax){
        error(34);  //Ƕ�ײ�ι���
        exit(-1);
    }
    if(b >= bmax){
        error(35);  //�ֳ�������
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
            error(31);   //������Ҫ�з���ֵ����
        if(sy == intcon || sy == charcon){
            tab[prt].typ = (sy == intcon)?inttype : chartype;
            nextsym();
        }
        else
            error(32);  //�Ƿ��ĺ����ķ���ֵ����
    }
    if(sy == semicolon){
        nextsym();
    }
    else{
        error(33);  //���̺ͺ���������βӦ�зֺ�
        if(sy == comma)
            nextsym();
    }

    btab[b].pnum = paranumber;//��������ͳ��

    block();                //������һ��ֳ���

    gen_code(JR, "", "", "");
    if(sy == semicolon){
        nextsym();
    }
    else
        error(36);  //ÿ���ֳ������Ӧ�зֺ�
}//procdeclare end

string simpleexp();
string arrayselector()          //����ѡȡ
{
    string first;

    if(sy != lbrack){
        error(23);  //ȱ��������
    }
    nextsym();
    first = simpleexp();
    if(sy == rbrack){
        nextsym();
    }
    else
        error(24);  //ȱ��������
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
            error(16);   //ȱ������

        while(paracount < paranumber){  //���ɴ���������Ԫʽ
            gen_code(PUSH, "", "", paraname[paracount]);
            paracount++;
        }
    }

    gen_code(CALL, "", "", procname);

    if(paranumber != btab[btabrefer].pnum){
        error(56);  //������������
    }
}//call end

string factor()           //���Ӵ���
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
                case proctype  : error(37); //���̲��ܲ�������
            }
        }
        else if(sy == lparent){
            nextsym();
            first = simpleexp();
            if(sy == rparent){
                nextsym();
            }
            else
                error(16);  //ȱ������
        }
    }
    else{
        error(38);  //�Ƿ�������
        nextsym();
    }
    return first;
}//factor end

string term()                 //���
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

string simpleexp()         //�򵥱��ʽ����
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

string conditionexp()        //�������ʽ����
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
        error(39);  //�Ƿ��Ĺ�ϵ�����
    }
    second = simpleexp();
    first = gen_code(op, first, second, "if");
    return first;
}//conditionexp end

void assignment(string first)       //��ֵ��䴦��
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
        error(39);  //ȱ�ٸ�ֵ����
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
void compoundstatement()        //������䴦��
{
    nextsym();//printf("Line%d: char(%d): This is a compound statement.\n", cx , ll);
    statement();
    while(sy == semicolon || sy == beginsy || sy == ifsy || sy == casesy || sy == forsy){
        if(sy != semicolon){
            error(40);  //���������ÿ������βӦ�зֺ�
        }
        else
            nextsym();
        statement();
    }
    if(sy == endsy){
        nextsym();
    }
    else
        error(41);  //ȱ��end
}//compoundstatement end

void ifstatement()          //�ж���䴦��
{
    string label1, label2;
    nextsym();//printf("Line%d: char(%d): This is a if statement.\n", cx , ll);
    label1 = conditionexp();
    if(sy == thensy){
        nextsym();
    }
    else
        error(42);   //ȱ��then
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

void casestatement()        //������䴦��
{
    string first, second;
    string label1, label2;
    char value[20];//�洢�ַ�ת������������ַ�����ʽ
    nextsym();
    //printf("Line%d: char(%d): This is a case statement.\n", cx , ll);

    first = simpleexp();
    if(sy == ofsy){
        nextsym();
    }
    else
        error(42);  //ȱ��of
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
            error(43);  //������ÿ�������жϺ���Ӧ��ð��
        }
        gen_code(J, "", "", label1);
        gen_code(LABEL, "", "", label2);
        if(sy == endsy){
            break;
        }
        if(sy != semicolon){
            error(44);  //������ÿ����֧�Ľ�β��Ҫ�ֺ�
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
        error(41);  //ȱ��end
    }
}//casestatement end

void forstatement()         //ѭ����䴦��
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
            error(52);  //forѭ���������Ϸ�
        label1 = gen_code(LABEL, "", "", "for");

        if(sy == tosy || sy == downtosy){
            op = (sy == tosy) ? BGTZ : BLTZ;
            calop = (sy == tosy) ? ADD : SUB;
            nextsym();
            second = simpleexp();
        }
        else
            error(45);  //Ӧ��to��downto
        label2 = gen_code(op, first, second, "for");

        if(sy == dosy){
            nextsym();
            statement();
        }
        else
            error(46);  //Ӧ��do

        gen_code(calop, first, "1", first);
        gen_code(J, "", "", label1);
        gen_code(LABEL, "", "", label2);
    }
}//forstatement end

void readproc()        //read����
{
    int i;

    nextsym();//printf("Line%d: char(%d): This is a read statement.\n", cx , ll);
    if(sy == lparent){
        nextsym();
    }
    else
        error(47);  //ȱ��������
    if(sy == ident){
        i = locate(alfa);
        if(tab[i].obj != vartype){
            error(55);  //read�����ʵ�α����Ǳ���
        }
        gen_code(READ, "", "", alfa);
        nextsym();
    }
    else
        error(48);  //Ӧ����һ����ʶ��
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
            error(48);  //Ӧ����һ����ʶ��
    }
    if(sy == rparent){
        nextsym();
    }
    else
        error(16);  //ȱ��������
}//readproc end

void writeproc()        //write����
{
    string first;
    nextsym();//printf("Line%d: char(%d): This is a write statement.\n", cx , ll);
    if(sy == lparent){
        nextsym();
    }
    else
        error(47);  //ȱ��������
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
        error(16);  //ȱ��������
}//writeproc end

void statement()        //��䴦��
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
            error(51);    //�������ܱ���ֵ
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
      //  error(49);  //���Ϸ��������ʼ��
}//statement end

void block()        //�ֳ�����
{
    string vartstring,  //��¼��ʱ������������Ԫʽ��ַ
            beginlabel; //���̺ͺ�������������ı�־

    if(sy == constsy){
        constdeclare();
    }
    if(sy == varsy){
        vardeclare();
    }
    vartstring = gen_code(VART, "0", "", "");   //������ʱ������������Ԫʽ
    beginlabel = gen_code(J, "", "", "begin");  //������ת�����������Ԫʽ

    while(sy == procsy || sy == funcsy){
            procdeclare();
    }

    gen_code(LABEL, "", "", beginlabel);    //
    if(sy == beginsy){
        compoundstatement();
    }
    else
        error(50);  //�ֳ��������һ��������䲿��
    gen_code(VART, "1", vartstring, "");

    if(level == 0){
        if(sy == period){
            return;
        }
        else{
            error(58);  //�����βȱ�پ��
        }
    }

    level -= 1;
}//block end

void setup()        //��ʼ��key��ksy��sps
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

            cc = 0,                 //��һ���ַ�����
            ll = 0,                 //��һ���ַ���
            cx = 0,                 //��ǰ��������
            inum = 0,               //����ֵ�洢
            level = 0,              //��ǰ�ֳ�����
            t = 1,      //���ű��ַ
            a = 0,      //������ַ
            b = 0,      //�ֳ�����ַ
            fc = 0;     //��Ԫʽ���ַ
            ch = ' ';              //ÿ�ζ����ĵ����ַ�
            line = "",           //��¼""�е��ַ���
            alfa = "";           //��¼ÿ�ζ������ַ���

            freopen("CON", "r", stdin);
        }
        else{
            freopen("CON", "r", stdin);
            printf("\nError: Can't found the file!\n\n");
        }
        break;
    }
}

int main()          //������
{
    compiler_shell();

    return 0;
}//main end
