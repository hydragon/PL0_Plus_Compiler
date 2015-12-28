void optimize_dag()
{
    struct dag{

    };
    struct four_code optimized_four_codes[cmax]; //优化后的四元式表
    int i,
        optimized_fc = 0;

    for(i = 0; i < fc; i++){
        if(four_codes[i].op == ADD || four_codes[i].op == SUB ||
           four_codes[i].op == MUL || four_codes[i].op == DIV || four_codes[i].op == ARRAY){    //需要进行优化的语句

        }
    }
}
