#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//num for calculate difficulty
#define COUNT

#ifdef COUNT
int step_num;
int branch_num;
int count_flag;
int worst_step_num;
int worst_branch_num;
#endif
int solution_num;


struct element {
    int num;
    int status;
    int opt[10];
};
struct subject {
    struct element square[9][9];
    int min_i, min_j;
    int min_status;
};


void print_square(struct subject subj)
{
    int i,j;
#ifdef DEBUG
    printf("min_status = %d,min_i = %d, min_j = %d\n",subj.min_status,subj.min_i,subj.min_j);
    printf("min_status opt array = ");
    for(i = 1; i<=9; i++) {
        printf("%d ",subj.square[subj.min_i][subj.min_j].opt[i]);
    }
    printf("\n");
#endif
    for(i = 0; i<9; i++) {
        if((i%3)==0)
            printf("\n");
        for(j = 0; j<9; j++) {
            printf("%d ",subj.square[i][j].num);
            if((j%3)==2)
                printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}


int calculate(struct subject subj)
{
    int i,j,k,s,t;
    int mret = -1;
    int tmp_status;
    int tmp_array[10];


#ifdef COUNT
    if(count_flag) {
        step_num++;
    }
    worst_step_num++;
#endif


    subj.min_status = 100;


    //renew opt by num
    for(i = 0; i<9; i++) {
        for(j = 0; j<9; j++) {
            if(subj.square[i][j].num > 0) {
                subj.square[i][j].status = -1;
                continue;
            }


            for( k = 0; k<9; k++) {
                subj.square[i][j].opt[subj.square[i][k].num] = 0;
                subj.square[i][j].opt[subj.square[k][j].num] = 0;
            }


            for (s = (i/3) * 3; s< (i/3 +1)*3; s++) {
                for (t = (j/3) * 3; t< (j/3 +1)*3; t++) {
                    subj.square[i][j].opt[subj.square[s][t].num]=0;
                }
            }


        }
    }


    //renew opt by neighbor opt
    for(i = 0; i<9; i++) {
        for(j = 0; j<9; j++) {
            if(subj.square[i][j].num > 0) {
                continue;
            }


            for(k = 1; k < 10; k++) {
                tmp_array[k] = subj.square[i][j].opt[k];
            }


            for( s = 0; s<9; s++) {


                if((s!=j)&&(subj.square[i][s].num == 0)) {
                    for(t = 1; t <= 9; t++) {
                        if(subj.square[i][s].opt[t]!=0) {
                            tmp_array[t] = 0;
                        }
                    }
                }


                if((s!=i)&&(subj.square[s][j].num == 0)) {
                    for(t = 1; t <= 9; t++) {
                        if(subj.square[s][j].opt[t]!=0) {
                            tmp_array[t] = 0;
                        }
                    }
                }
            }


            for (s = (i/3) * 3; s< (i/3 +1)*3; s++) {
                for (t = (j/3) * 3; t< (j/3 +1)*3; t++) {
                    if(((s!=i)||(t!=j))&&(subj.square[s][t].num == 0)) {
                        for(k = 1; k <= 9; k++) {
                            if(subj.square[s][t].opt[k]!=0) {
                                tmp_array[k] = 0;
                            }


                        }
                    }
                }
            }


            tmp_status = 0;
            for(k=1; k<=9; k++) {
                if(tmp_array[k] !=0)
                    tmp_status++;
            }


            if(tmp_status != 0) {
                subj.square[i][j].status = tmp_status;
                for(k = 1; k<=9; k++) {
                    subj.square[i][j].opt[k] = tmp_array[k];
                }
            }


            subj.square[i][j].status=0;
            for(k = 1; k < 10; k++) {
                if(subj.square[i][j].opt[k] != 0) {
                    subj.square[i][j].status++;
                }
            }


            if(subj.square[i][j].status == 0) {
                return -1;
            } else if(subj.square[i][j].status < subj.min_status) {
                subj.min_status = subj.square[i][j].status;
                subj.min_i = i;
                subj.min_j = j;
            }
        }
    }


    if(subj.min_status == 100) {
        printf("Success,Output Square\n");
        print_square(subj);
        solution_num++;
        return 0;
    }


#ifdef DEBUG
    print_square(subj);
#endif


#ifdef COUNT
    if(subj.min_status>1) {
        worst_branch_num++;
        if(count_flag) {
            branch_num++;
        }
    }
#endif


    for(i = 1; i<=9; i++) {
        if(subj.square[subj.min_i][subj.min_j].opt[i] > 0) {
            subj.square[subj.min_i][subj.min_j].num = subj.square[subj.min_i][subj.min_j].opt[i];
            if(calculate(subj)==0) {
#ifdef COUNT
                count_flag = 0;
#endif
                mret = 0;
            }
        }
    }
    return mret;
}


int main(int argc,char *argv[])
{
    int i,j,k;
    char c;
    struct subject subj;


    subj.min_status = 9;
    subj.min_i = 0;
    subj.min_j = 0;
    solution_num = 0;


#ifdef COUNT
    step_num = 0;
    branch_num = 0;
    worst_step_num = 0;
    worst_branch_num = 0;
    count_flag = 1;
#endif


    for(i = 0; i<9; i++) {
        for(j = 0; j<9; j++) {
            while(1) {
                c = getchar();
                if(c >='0' && c<='9') {
                    subj.square[i][j].num=c-'0';
                    break;
                }
            }


            if(subj.square[i][j].num == 0) {
                for(k=0; k<=9; k++) {
                    subj.square[i][j].opt[k] = k;
                }
            }
        }
    }
    printf("Input Square\n");
    print_square(subj);
    printf("***************************************************\n");
    calculate(subj);
#ifdef COUNT
    printf("Real Step Num = %d\n",step_num);
    printf("Worst Step Num = %d\n",worst_step_num);
    printf("Real Branch Num = %d\n",branch_num);
    printf("Worst Branch Num = %d\n",worst_branch_num);
#endif
    printf("Solution Num = %d\n",solution_num);


    return 0;
}
