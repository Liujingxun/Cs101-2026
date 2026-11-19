#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_GROUPS 5
#define PICK_COUNT 7
#define MIN_NUM 1
#define MAX_NUM 69

static void generate_unique_pick(int out[PICK_COUNT]) {
    int used[MAX_NUM + 1] = {0};
    int count = 0;

    while (count < PICK_COUNT) {
        int r = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
        if (!used[r]) {
            used[r] = 1;
            out[count++] = r;
        }
    }
}

static void strip_newline(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
}

int main(void) {
    int n = 0;

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩:");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_GROUPS) {
        printf("輸入無效，請輸入 1 到 %d 之間的整數。\n", MAX_GROUPS);
        return 1;
    }

    FILE *fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        perror("無法開啟 lotto.txt");
        return 1;
    }

    srand((unsigned int)time(NULL));

    time_t now = time(NULL);
    char time_buf[64] = "Unknown Time";
    char *raw_time = ctime(&now);
    if (raw_time != NULL) {
        snprintf(time_buf, sizeof(time_buf), "%s", raw_time);
        strip_newline(time_buf);
    }

    fprintf(fp, "= lotto649 =\n");
    fprintf(fp, "= %s =\n", time_buf);

    for (int i = 1; i <= MAX_GROUPS; i++) {
        fprintf(fp, "[%d]: ", i);
        if (i <= n) {
            int nums[PICK_COUNT];
            generate_unique_pick(nums);
            for (int j = 0; j < PICK_COUNT; j++) {
                fprintf(fp, "%02d", nums[j]);
                if (j < PICK_COUNT - 1) {
                    fprintf(fp, " ");
                }
            }
            fprintf(fp, "\n");
        } else {
            fprintf(fp, "--\n");
        }
    }

    fprintf(fp, "= csie@CGU =\n");
    fclose(fp);

    printf("以為您購買的%d組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}
