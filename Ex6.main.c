#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 第 55 行：定義 employee_t 結構體[span_2](start_span)[span_2](end_span)
typedef struct employee {
    int id;
    char name[32];
    int age;
} employee_t;

// 第 62 行：印出單一員工資訊[span_3](start_span)[span_3](end_span)
void emp_info(employee_t emp) {
    printf("ID: %d, Name: %s, Age: %d\n", emp.id, emp.name, emp.age);
}

// 第 69 行：計算平均年齡（維持講義函式名稱 emp_aveage_age）[span_4](start_span)[span_4](end_span)
int emp_aveage_age(employee_t emp[], int n) {
    if (n <= 0) return 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += emp[i].age;
    }
    return sum / n;
}

// 第 77 行：將員工陣列寫入 employee.bin 檔案[span_5](start_span)[span_5](end_span)[span_6](start_span)[span_6](end_span)
void emp_writefile(employee_t emp[], int n) {
    FILE *fp = fopen("employee.bin", "wb");
    if (fp == NULL) {
        return;
    }
    fwrite(emp, sizeof(employee_t), n, fp);
    fclose(fp);
}

// 第 84 行：從 employee.bin 讀出資料並輸出至 stdout (螢幕)[span_7](start_span)[span_7](end_span)[span_8](start_span)[span_8](end_span)
void emp_readfile(employee_t emp[], int n) {
    FILE *fp = fopen("employee.bin", "rb");
    if (fp == NULL) {
        return;
    }
    fread(emp, sizeof(employee_t), n, fp);
    for (int i = 0; i < n; i++) {
        emp_info(emp[i]);
    }
    fclose(fp);
}

// 第 91 行：main 函式[span_9](start_span)[span_9](end_span)
int main() {
    employee_t employees[3] = {
        {1, "Alice", 20},
        {2, "Bob", 22},
        {3, "Charlie", 21}
    };
    int n = 3;

    // 將資料寫入 employee.bin[span_10](start_span)[span_10](end_span)
    emp_writefile(employees, n);

    // 從檔案讀出並輸出至螢幕 (stdout)[span_11](start_span)[span_11](end_span)
    emp_readfile(employees, n);

    // 輸出平均年齡
    printf("Average Age: %d\n", emp_aveage_age(employees, n));

    return 0;
}
