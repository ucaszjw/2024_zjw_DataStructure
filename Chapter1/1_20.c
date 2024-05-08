#include <stdio.h>

struct Poly {
    int coef;
    int exp;
};

int main(){
    int n, x_0;
    scanf("%d %d", &n, &x_0);
    struct Poly p[n+1];
    for (int i = 0; i < n+1; i++) {
        scanf("%d", &p[i].coef);
        if (p[i].coef < -1000 || p[i].coef > 1000)
            return 0;
    }
    int result = 0;
    for (int i = n; i >= 0; i--) {
        result = result * x_0 + p[i].coef;
    }
    printf("%d", result);
    return 0;
}