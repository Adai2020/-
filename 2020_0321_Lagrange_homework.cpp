#include<stdio.h>
#include<math.h>
#include<windows.h>

void color(short x);

int main(void)
{
    //定义数据
    double X[5] = {9,11,13,15,17};//已知样本点的天数
    double Y[5] = { 37289,42747,59885, 66581,70644 } ,y_[4],t;//确诊人数
    double x_[4] = { 10,12,14,16 };//待计算的样本点
    int Rel_y[4] = { 40262,44765 ,63950 ,68595 };//待测点的真实确诊人数
    double f[5][5] = {0};
    int e[4];
    int k,i, j, n=5,N=4;
    //k代表待预测的点的数量,n代表样本点的数量,N为待预测点的数量
    //处理数据——Lagrange插值法——
    color(3);
    printf("\n问题二，使用拉格朗日插值法预测人数,结果如下：\n\n");
    color(15); 
    for (k = 0; k <N; k++) {
        y_[k] = 0; //目标函数y_初始值为0
           //处理数据
           //先对整个函数循环
        for (i = 0; i < n; i++) {
            t = 1;
            //跳过i=j的项
            for (j = 0; j < n; j++) {
                if (j != i) {
                    t *= (x_[k] - X[j]) / (X[i] - X[j]);//累乘
                }
            }
            y_[k] += t * Y[i];//先乘y，再累加
        }
        //与真实值进行比较，计算绝对误差
        e[k] = fabs(Rel_y[k] - round(y_[k]));
        //输出结果
        printf("     第%.0lf天的确诊人数可能为%.0lf人，相对于真实值的绝对误差为%d人。\n", x_[k], round(y_[k]), e[k]);
   }
    color(3); 
    printf("\n问题三，使用牛顿插值法预测人数,结果如下：\n\n");
    color(15);
    for (i = 0; i < 5; i++) { f[0][i] = Y[i]; }
    for (i = 0; i < 4; i++) { f[1][i + 1] = (f[0][i + 1] - f[0][i]) / (X[i + 1] - X[i]); }
    for (i = 0; i < 3; i++) { f[2][i + 2] = (f[1][i + 2] - f[1][i + 1]) / (X[i + 2] - X[i]); }
    for (i = 0; i < 2; i++) { f[3][i + 3] = (f[2][i + 3] - f[2][i + 2]) / (X[i + 3] - X[i]); }
    f[4][4] = (f[3][4] - f[3][3]) / (X[0 + 4] - X[0]);
    for (k = 0; k < 4; k++) {
        t = f[4][4];
        for (i = 0; i < 4; i++) { t = t * (x_[k] - X[4 - 1 - i]) + f[4 - i - 1][4 - i - 1]; }
        y_[k] = t;
        e[k] = fabs(Rel_y[k] - round(y_[k]));
        printf("     第%.0lf天的确诊人数可能为%.0lf人，相对于真实值的绝对误差为%d人。\n", x_[k], round(y_[k]), e[k]);
    }
    //生成差商表格
    for (i = 0; i < 5; i++) {
        printf("\n     %d阶差商：", i);
        for (j = 0; j < 5; j++) {
            printf("%-9.2f  ", f[i][j]);
        }
    }
    printf("\n");
}

void color(short x)	//自定义函根据参数改变颜色 
{
    if (x >= 0 && x <= 15)//参数在0-15的范围颜色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色 
    else//默认的颜色白色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}