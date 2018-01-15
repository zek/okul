#include <stdio.h>

/*
4
10 11 12 13
14 15 16 17
18 19 20 21
22 23 24 25

3
11 22 33
44 55 66
77 88 99

(0, 0) => (2, 0)
(2, 0) => (2, 2)
(2, 2) => (0, 2)
(0, 2) => (0, 0)

(a, b) => (length - b ,a)

i = 0; j= 0;
(0, 0) => (0, 2)
(0, 2) => (2, 2)
(2, 2) => (2, 0)
(2, 0) => (0, 0)

i = 0; j= 1;
(0, 1) => (1, 2)
(1, 2) => (2, 1)
(2, 1) => (1, 0)
(1, 0) => (0, 1)

length = 3 - 1
(a, b) => (b, length - a)
 */

/*
 *
 * rotate = 1 to left
 * rotate = 0 to right
 */
void rotate(int array[50][50], int size, int rotate_to) {
    unsigned int i, j, a, b, temp3, rotate;

    int temp, temp2;

    for (i = 0; i < size / 2; i++) {
        for (j = 0; j < (size + 1) / 2; j++) {
            a = i;
            b = j;
            temp = array[a][b];

            rotate = 4;
            while (rotate--) {
                if (rotate_to == 1) {
                    temp2 = array[size - b - 1][a];

                    array[size - b - 1][a] = temp;
                    temp = temp2;

                    temp3 = a;
                    a = size - b - 1;
                    b = temp3;
                } else {
                    temp2 = array[b][size - a - 1];

                    array[b][size - a - 1] = temp;
                    temp = temp2;

                    temp3 = b;
                    b = size - a - 1;
                    a = temp3;
                }

            }

        }
    }


}

int main() {
    unsigned int size, i = 0, i2 = 0;
    int array[50][50];
    char c;

    scanf("%d", &size);

    for (i = 0; i < size; ++i) {
        for (i2 = 0; i2 < size; ++i2) {
            scanf("%d", &array[i][i2]);
        }
    }

    while (scanf("%c ", &c) == 1) {
        if (c == '>') {
            scanf("%c ", &c);
            if (c == 'R') {
                scanf("%c ", &c);
                if (c == '+') {
                    rotate(array, size, 0); // rotate to right
                    for (i = 0; i < size; ++i) {
                        for (i2 = 0; i2 < size; ++i2) {
                            printf("%d ", array[i][i2]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                } else if (c == '-') {
                    rotate(array, size, 1); // rotate to left
                    for (i = 0; i < size; ++i) {
                        for (i2 = 0; i2 < size; ++i2) {
                            printf("%d ", array[i][i2]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
            } else if (c == 'q') {
                return 0;
            }
        }
    }

    return 0;
}