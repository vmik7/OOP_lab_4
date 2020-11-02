#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

/*
    Класс: Прямая.
    Элементы класса: Координаты двух точек (x1,y1) и (x2,y2).
    Методы: Конструктор, деструктор, метод вывода уравнения прямой.
    Перегружаемые операции: Проверка параллельности двух прямых ||, определение угла между двумя прямыми %.
*/

// EPS для сравнения чисел типа double
const double EPS = 1e-7;

// Равенство double чисел
inline double eq(double a, double b) { return a > b - EPS && a < b + EPS; }

class line {
private:

    // Координаты точек, которыми задается прямая
    int x_1, x_2, y_1, y_2;

    // Булево значение vertical истинно в частном случае, когда прямая задается уравнением x = c = const
    bool vertical;

    // Коэффициенты для уравнения y = k * x + b
    double k, b;
    
    // Константа для уравнения x = c = const
    int c;

    // Проверяет прямую на вертикальность и расчитывает коэффициенты
    void init() {
        if (x_1 == x_2) {
            vertical = true;
            c = x_1;
        }
        else {
            vertical = false;
            k = (double)(y_2 - y_1) / (x_2 - x_1);
            b = (double)(-x_1) * (y_2 - y_1) / (x_2 - x_1) + y_1;
        }
    }

public:
	// Конструкторы со списками инициализации
    line() : x_1(0), y_1(0), x_2(1), y_2(1) { init(); }
    line(int _x_1, int _y_1, int _x_2, int _y_2) : x_1(_x_1), y_1(_y_1), x_2(_x_2), y_2(_y_2) { init(); }

	// Перегрузка операции перенаправления потока <<
    friend ostream& operator << (ostream& os, line& t);

    // Перегрузка операции || (параллельность двух прямых)
    bool operator || (const line& t) const {
        if (this->vertical && t.vertical)
            return true;
        else if (!this->vertical && !t.vertical)
            return this->k == t.k;
        else
            return false;
    }

    // Перегрузка операции % (угол между прямыми)
    double operator % (const line& t) const {
        double uv = (this->x_2 - this->x_1) * (t.x_2 - t.x_1) + (this->y_2 - this->y_1) * (t.y_2 - t.y_1);
        double u = sqrt((this->x_2 - this->x_1) * (this->x_2 - this->x_1) + (this->y_2 - this->y_1) * (this->y_2 - this->y_1));
        double v = sqrt((t.x_2 - t.x_1) * (t.x_2 - t.x_1) + (t.y_2 - t.y_1) * (t.y_2 - t.y_1));
        return acos(uv / (u * v));
    }

    // Деструктор
    ~line() {}
};

// Функция вывода уравнения прямой
ostream& operator << (ostream& os, line& t) {
    if (t.vertical) {
        os << "x = " << t.c;
    }
    else {
        if (eq(t.k, 0)) {
            os << "y = " << t.b;
        }
        else {
            if (eq(t.b, 0))
                os << "y = " << t.k << " * x";
            else
                os << "y = " << t.k << " * x" << (t.b < 0 ? " - " : " + ") << abs(t.b);
        }
    }
    return os;
}

int main() {

    cout << fixed << setprecision(3) << endl;

    int x_1, x_2, y_1, y_2;

    cout << "Прямая a\n";
    cout << "Первая точка:\n";
    cout << "x: "; cin >> x_1;
    cout << "y: "; cin >> y_1;
    cout << "Вторая точка:\n";
    cout << "x: "; cin >> x_2;
    cout << "y: "; cin >> y_2;

    line a(x_1, y_1, x_2, y_2);

    cout << endl;

    cout << "Прямая b\n";
    cout << "Первая точка:\n";
    cout << "x: "; cin >> x_1;
    cout << "y: "; cin >> y_1;
    cout << "Вторая точка:\n";
    cout << "x: "; cin >> x_2;
    cout << "y: "; cin >> y_2;

    line b(x_1, y_1, x_2, y_2);

    cout << endl;

    cout << "Уравнение a: " << a << endl;
    cout << "Уравнение b: " << b << endl;

    cout << (a || b ? "Прямые параллельны!" : "Прямые не являются параллельными") << endl;
    cout << "Угол между прямыми: " << (a % b) << " = " << (a % b) / acos(-1) * 180 << "°" << endl;

    return 0;
}