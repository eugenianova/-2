// Дана квадратная матрица. Найти минимальное значение среди элементов, расположенных над главной диагональю.
//Выбрать три различных точки из множества точек на плоскости так, чтобы была минимальной разность между количеством точек,
//...лежащих внутри и вне треугольника с вершинами в выбранных точках.

#define ROWS 4
#define COLS 4
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

void gen_stat_matrix(int m[ROWS][COLS], int min = -25, int max = 25) //генератор статич матрицы
{
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
            m[i][j] = uniform_dist(e1);
    }
}

int** gen_dyn_matrix(int rows, int cols, int min = -25, int max = 25) //генератор динам матрицы
{
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);

    int** m = (int**)malloc(sizeof(int) * rows);
    for (int i = 0; i < rows; i++)
    {
        m[i] = (int*)malloc(sizeof(int) * cols);
        for (int j = 0; j < cols; j++)
            m[i][j] = uniform_dist(e1);
    }
    return m;
}

void print_matrix(const int m[ROWS][COLS]) //функция вывода матрицы на экран статит
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++) {
            std::cout << std::setw(5) << m[i][j];

            if (j != ROWS)
                std::cout << " ";
        }
        if (i != COLS)
            std::cout << std::endl;
    }
}

void print_dyn_matrix(int** m, int rows, int cols) // вывод динам матрицы на экран
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(5) << m[i][j];

            if (j != rows)
                std::cout << " ";
        }
        if (i != cols)
            std::cout << std::endl;
    }
}

int thelowestofhighest_stat(int m[ROWS][COLS])
{
    int min = m[0][1];
    int max = m[1][0];
    int imin = 0, jmin = 0, imax = 0, jmax = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < ROWS; j++)
        {
            if (i < j) //условие главной диагонали
            {
                if (min > (m[i][j]))
                {
                    min = m[i][j];
                    imin = i + 1;
                    jmin = j + 1;
                }
            }
        }
    return min;
}

int thelowestofhighest_dyn(int** m)
{
    int min = m[0][1];
    int max = m[1][0];
    int imin = 0, jmin = 0, imax = 0, jmax = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < ROWS; j++)
        {
            if (i < j) //условие главной диагонали
            {
                if (min > (m[i][j]))
                {
                    min = m[i][j];
                    imin = i + 1;
                    jmin = j + 1;
                }
            }
        }
    return min;
}

// реализация для статического массива. (для динамического массива реализация аналогична)
void fill_stat_and_dyn_matrix(int m[ROWS][COLS]) //ввод матрицы с клавиатуры
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
            std::cin >> m[i][j];
    }
}

void fill_vector_matrix(std::vector<std::vector<char> >& vec, int rows = 20, int cols = -1) //заполнение двумерного вектора точками
{
    if (cols == -1)
        cols = rows;

    for (int r = 0; r < rows; r++)
    {
        std::vector<char> row;
        for (int c = 0; c < cols; c++)
            row.push_back('.');

        vec.push_back(row);
    }
}


struct point
{
    double x;
    double y;
};

double getArea(const point& a, const point& b, const point& c) //функция вычисляет плозадь треугольника вершин которого заданы точнами в структуре point
{
    return fabs((a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y)); //fabs вычисляет абсолютное значение
}

bool inTriangle(const point& p, const point& a, const point& b, const point& c)
{
    return (getArea(a, b, c) >= (getArea(p, b, c) + getArea(a, p, c) + getArea(a, b, p))); //показывает больше ли плозадь основного треугольника, чем суммы побочных
} //если да, то точка Р лежит за пределами треугольника. Нам нужно чтобы кол-во внутри было примерно равно за пределами


int main()
{
    setlocale(LC_ALL, "");
    int zello;
    cout << "Практическая работа №2 Тараканова Евгения " << endl;
    cout << "Выберите массив:" << endl << "1 - статический" << endl << "2 - динамический" << endl << "3 - вектор" << endl;

    int mode;
    do
    {
        cin >> mode;
        if (mode < 1 || mode > 3) cout << "Такого режима нет. Введите число от 1 до 3: ";
    } while (mode < 1 || mode > 3);


    switch (mode)
    {
    case 1: //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!    C  A  S  E  1
    {//Статический массив
        cout << "Реализация на статическом массиве : " << endl;
        int m1[ROWS][COLS];
        int result[ROWS][COLS];

        cout << "Выберите способ ввода массива:" << endl << "1 - генерация случайных чисел" << endl << "2 - вручную" << endl;
        int mode1;
        do
        {
            cin >> mode1;
            if (mode1 < 1 || mode1 > 2) cout << "Такого режима нет. Введите число 1 или 2: ";
        } while (mode1 < 1 || mode1 > 2);

        switch (mode1)
        {
        case 1:
        {
            cout << "Заполнение случайными числами : " << endl;
            gen_stat_matrix(m1, 0, 20); //генерация матрицы м1 случайными значениями от 0 до 20
            print_matrix(m1); // вывод матрицы на экран
            cout << endl;
            zello = thelowestofhighest_stat(m1); //нашли минимальное значение над главной диагональю
            cout << "Минимальное число над главной диагональю: " << zello << endl;
            break;
        }
        case 2:
        {
            cout << "Заполнение числами с клавиатуры: " << endl;
            fill_stat_and_dyn_matrix(m1);
            print_matrix(m1); // вывод матрицы на экран
            cout << endl;
            int zello = thelowestofhighest_stat(m1); //нашли минимальное значение над главной диагональю
            cout << zello << endl;

            break;
        }
        }
        break;
    }
    case 2: //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!    C  A  S  E  2
    { //Динамический массив
        int rows = 4;
        int cols = 4;
        cout << "Реализация на динамическом массиве : " << endl;
        int mode1;
        cout << "Заполнение случайными числами : " << endl;
        int** m1 = gen_dyn_matrix(rows, cols, 1, 40);

        print_dyn_matrix(m1, rows, cols); // вывод матрицы на экран
        cout << endl;
        int zello = thelowestofhighest_dyn(m1); //нашли минимальное значение над главной диагональю
        cout << endl << "Минимальное число над главной диагональю: " << zello;
        break;
    }
    case 3:
    {//вектор
        cout << "Реализация на векторе : " << endl;

        const int n = 16;
        point p[n] = { {0,0},{0,1},{0,2},{0,3},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,0},{3,1},{3,2},{3,3} };
        int a, b, c;
        int difference = n;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                for (int k = j + 1; k < n; k++) {
                    int tmp = 0;
                    for (int x = 0; x < n; x++) {
                        if ((x - i) * (x - j) * (x - k)) {
                            if (inTriangle(p[x], p[i], p[j], p[k])) {
                                tmp++;
                            }
                            else {
                                tmp--;
                            }
                        }
                        else {
                            continue;
                        }
                    }
                    tmp = abs(tmp);
                    if (tmp < difference) {
                        difference = tmp;
                        a = i;
                        b = j;
                        c = k;
                    }
                    if (tmp == 0) {
                        goto Find;
                    }
                }
            }
        }

    Find:
        std::cout << a << ' ' << b << ' ' << c;
        

        break;
    }
    }
}