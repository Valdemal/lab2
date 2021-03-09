#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <windows.h>

#define PI 3.1415926

struct coord {
    double x, y, z;
};// Тип, который задает координаты

struct vector {
    struct coord c;
    double len;
};// Тип, который задает вектор

void input_point(struct coord *p) {
    //Ввод координат точки по адресу p
    scanf("%lg %lg %lg", &(p->x), &(p->y), &(p->z));
}

struct vector create_vector(struct coord a, struct coord b){
    // Возвращает вектор, образованный точками a, b
    struct vector v;
    struct coord c = {b.x - a.x, b.y - a.y, b.z - a.z};
    v.c = c;
    v.len = sqrt(pow(c.x, 2) + pow(c.y, 2) + pow(c.z, 2));
    return v;
}

double calc_cos(struct vector ab, struct vector bc) {
    /* Возвращает значение косинуса угла между векторами ab и bc*/

    return (ab.c.x * bc.c.x + ab.c.y * bc.c.y + ab.c.z * bc.c.z)/
           (ab.len * bc.len);
}

double max_d(double a,double b){
    /*Возвращает максимальное из значений: a, b */
    return a > b ? a : b;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);// Подключение русского языка

    printf("Введите количество вершин:");
    size_t n;
    scanf("%d", &n);
    if (n < 3) {
        printf("Ошибка! Входные данные некорректны! Чтобы построить угол,"
               " нужно минимум 3 точки, вы ввели %d.", n);
    } else {
        struct coord p0, p1, p2;
        struct vector v0, v1, v2;

        printf("Введите 1-ю точку:");
        input_point(&p0);
        printf("Введите 2-ю точку:");
        input_point(&p1);

        v0 = create_vector(p0, p1);
        v2 = v0;

        double max_cos = -1;

        for (size_t i = 3; i <= n; i++) {
            v1 = v2;

            printf("Введите %d-ю точку:", i);
            input_point(&p2);

            v2 = create_vector(p1, p2);
            max_cos = max_d(max_cos, calc_cos(v1, v2));

            p1 = p2;
        }

        struct vector v_last = create_vector(p2, p0);

        max_cos = max_d(max_cos, calc_cos(v2, v_last));
        max_cos = max_d(max_cos, calc_cos(v_last, v0));

        double angle = acos(-max_cos) * 180 / PI;
        printf("Самый большой угол в данном %d-угольнике равен %lg градусов.",
               n, angle);
    }
}