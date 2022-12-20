#include <stdio.h>

char sign(char x) {
    if ((x=='-')||(x=='/')||(x=='%')) return 2;
    if ((x=='+')||(x=='*')) return 1;
    return 0;
}

char precalc(char a, char b, char sign, char param) {
    a = a - '0';
    b = b - '0';
    switch (sign) {
    case '+':
        if (param) return a+b;
        return a-b;
    case '-':
        if (param) return a-b;
        return a+b;
    case '*':
        if (param) return a*b;
        return a/b;
    case '/':
        if (param) return a/b;
        return a*b;
    default: // '%'
        return a%b;
    }
}

int Calc(char *exp) {
    char xpos = -1, eqpos = -1, signpos = -1, result = -1;
    for (int i = 0; i < 5; i++) {
        if (*(exp + i) == 'x') xpos = i;
        if (sign(*(exp + i))) signpos = i;
    }
    if (xpos == 0) {
        if (signpos == 1) return precalc(*(exp+4),*(exp+2),*(exp+signpos),0);
        return precalc(*(exp+2),*(exp+4),*(exp+signpos),1);
    }
    if (xpos == 2) {
        if ((signpos == 1)&&(sign(*(exp+signpos))==1)) return precalc(*(exp+4),*(exp+0),*(exp+signpos),0);
        if ((signpos == 1)&&(sign(*(exp+signpos))==2)) return precalc(*(exp+0),*(exp+4),*(exp+signpos),1);
        if (sign(*(exp+signpos))==1) return precalc(*(exp+0),*(exp+4),*(exp+signpos),0);
        return precalc(*(exp+4),*(exp+0),*(exp+signpos),0);
    }
    if (signpos == 1) return precalc(*(exp+0),*(exp+2),*(exp+signpos),1);
    if (sign(*(exp+signpos))==2) return precalc(*(exp+2),*(exp+0),*(exp+signpos),1);
    return precalc(*(exp+0),*(exp+2),*(exp+signpos),0);
}

int main(void) {
    char *expression[] = {  "x+7=2", "x=7+2", "7+x=2", "7=x+2", "7=2+x", "7+2=x",
                            "x-7=2", "x=7-2", "7-x=2", "7=x-2", "7=2-x", "7-2=x",
                            "x*7=2", "x=7*2", "7*x=2", "7=x*2", "7=2*x", "7*2=x",
                            "x/7=2", "x=7/2", "7/x=2", "7=x/2", "7=2/x", "7/2=x",
                            "x=7%2", "7%2=x" };
    int len = sizeof(expression)/sizeof(char *);
    printf("%d\n",len);
    for (int i = 0; i < len; i++) {
        printf("%s \tx = %2d\n",expression[i],Calc(expression[i]));
    }
}