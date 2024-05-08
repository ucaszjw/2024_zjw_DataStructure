#include <stdio.h>
#include <string.h>

struct School {
    int male_score;
    int female_score;
    int total_score;
};

int main() {
    struct School scores[5] = {0};
    char project[10], gender, school;
    int score;

    while (scanf("%s %c %c %d", project, &gender, &school, &score) != EOF) {
        int index = school - 'A';
        if (gender == 'M') {
            scores[index].male_score += score;
        } else if (gender == 'F') {
            scores[index].female_score += score;
        }
        scores[index].total_score += score;
    }

    for (int i = 0; i < 5; i++) {
        if (scores[i].male_score > 0) {
            printf("%c M %d\n", 'A' + i, scores[i].male_score);
        }
        if (scores[i].female_score > 0) {
            printf("%c F %d\n", 'A' + i, scores[i].female_score);
        }
        if (scores[i].total_score > 0) {
            printf("%c %d\n", 'A' + i, scores[i].total_score);
        }
    }
    return 0;
}