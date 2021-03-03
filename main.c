// Найти величину максимального угла n-угольника, заданного  координатами вершин
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
    // Возвращает вектор образованный точками a, b
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

int main() {
    SetConsoleOutputCP(CP_UTF8);// Подключение русского языка

    printf("Введите количество углов:");
    size_t n;
    scanf("%d", &n);
    if (n < 3) {
        printf("Ошибка! Входные данные некорректны! Чтобы построить угол,"
               " нужно минимум 3 точки, вы ввели %d.", n);
    } else {
        struct coord p1, p2, p3, p1_copy, p2_copy;
        struct vector v1, v2;

        printf("Введите 1-ю точку:");
        input_point(&p1);
        printf("Введите 2-ю точку:");
        input_point(&p2);
        p1_copy = p1;
        p2_copy = p2;
        v1 = create_vector(p1, p2);
        double max_cos = -2;
        for (size_t i = 1; i <= n - 2; i++) {
            printf("Введите %d-ю точку:", 2 + i);
            input_point(&p3);
            v2 = create_vector(p2, p3);
            double cos;
            cos = calc_cos(v1, v2);

            if (cos > max_cos) max_cos = cos;

            p1 = p2;
            p2 = p3;
        }
        p2 = p1;

        double last_cos, first_cos;
        last_cos = calc_cos(create_vector(p2, p3), create_vector(p3,p1_copy));
        first_cos = calc_cos(create_vector(p3, p1_copy),
                             create_vector(p1_copy, p2_copy));

        if (last_cos > max_cos) {
            max_cos = last_cos;
        }
        if (first_cos > max_cos) {
            max_cos = first_cos;
        }
        double angle;
        angle = acos(-max_cos) * 180 / PI;
        printf("Самый большой угол в данном %d-угольнике равен %lg градусов.",
               n, angle);
    }
}
