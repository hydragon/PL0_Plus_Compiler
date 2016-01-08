const int dag_length = 200;

struct dag{
    string point_opt;
    string name;
    int fathercount;
    int left;
    int right;
};
struct dag_point{
    string name;
    int locate;
};
struct dag dag_tree[dag_length]; //dag图数组
struct dag_point dag_point_list[dag_length]; //dag节点表

struct four_code optimized_four_codes[cmax]; //优化后的四元式表
int i,
    dag_c = 0,
    dag_point_c = 0,
    optimized_fc = 0;

void dag_enterfourcode(enum four_code_option op, string t1, string t2, string t3){
    optimized_four_codes[optimized_fc].op = op;
    optimized_four_codes[optimized_fc].t1 = t1;
    optimized_four_codes[optimized_fc].t2 = t2;
    optimized_four_codes[optimized_fc].t3 = t3;

    optimized_fc ++;
}

void dag_to_four_code()
{
    int point_stack[dag_length];
    int tree_stack[dag_length];
    int point_s_top = 0,
        tree_s_top = 0;

    for(int j = dag_c; j >= 0; j--){

    }
}

void optimize_dag()
{
    for(i = 0; i < fc; i++){
        int begin_point = 0,
            end_point = 0;

        if(four_codes[i].op == ADD || four_codes[i].op == SUB ||
           four_codes[i].op == MUL || four_codes[i].op == DIV || four_codes[i].op == ARRAY){    //需要进行优化的语句

        }
        else{
            dag_to_four_code();

            dag_enterfourcode(four_codes[i].op, four_codes[i].t1, four_codes[i].t2, four_codes[i].t3);
            beginpoint = optimized_fc;
        }
    }
}
