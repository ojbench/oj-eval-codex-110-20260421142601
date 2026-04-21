#include <bits/stdc++.h>
using namespace std;

class Date {
private:
    int _year{1900};
    int _month{1};
    int _day{1};

    static bool isLeap(int y) {
        return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    }

    static int daysInMonth(int y, int m) {
        static const int md[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if (m == 2) return md[m] + (isLeap(y) ? 1 : 0);
        return md[m];
    }

    static bool valid(int y, int m, int d) {
        if (m < 1 || m > 12) return false;
        if (d < 1) return false;
        int dim = daysInMonth(y, m);
        if (d > dim) return false;
        return true;
    }

    static long long toOrdinal(int y, int m, int d) {
        // days since 1900-01-01 (day 0)
        long long days = 0;
        for (int yy = 1900; yy < y; ++yy) {
            days += 365 + (isLeap(yy) ? 1 : 0);
        }
        for (int mm = 1; mm < m; ++mm) {
            days += daysInMonth(y, mm);
        }
        days += (d - 1);
        return days;
    }

    static void fromOrdinal(long long ord, int &y, int &m, int &d) {
        // assuming ord >= 0
        y = 1900;
        while (true) {
            int diy = 365 + (isLeap(y) ? 1 : 0);
            if (ord >= diy) {
                ord -= diy;
                ++y;
            } else break;
        }
        m = 1;
        while (true) {
            int dim = daysInMonth(y, m);
            if (ord >= dim) {
                ord -= dim;
                ++m;
            } else break;
        }
        d = (int)ord + 1;
    }

    void addDaysInPlace(long long delta) {
        long long ord = toOrdinal(_year, _month, _day);
        ord += delta;
        if (ord < 0) ord = 0; // clamp to minimum representable
        int y, m, d;
        fromOrdinal(ord, y, m, d);
        _year = y; _month = m; _day = d;
    }

public:
    Date() = default;

    Date(int y, int m, int d) {
        if (valid(y, m, d)) {
            _year = y; _month = m; _day = d;
        } else {
            _year = 1900; _month = 1; _day = 1;
        }
    }

    // prefix ++ : next day
    Date& operator++() { addDaysInPlace(1); return *this; }
    // postfix ++
    Date operator++(int) { Date tmp = *this; addDaysInPlace(1); return tmp; }
    // prefix -- : previous day
    Date& operator--() { addDaysInPlace(-1); return *this; }
    // postfix --
    Date operator--(int) { Date tmp = *this; addDaysInPlace(-1); return tmp; }

    // date + int days
    Date operator+(long long days) const { Date res = *this; res.addDaysInPlace(days); return res; }
    // date - int days (previous days)
    Date operator-(long long days) const { Date res = *this; res.addDaysInPlace(-days); return res; }
    // date - date => absolute days between
    long long operator-(const Date& other) const {
        long long a = toOrdinal(_year, _month, _day);
        long long b = toOrdinal(other._year, other._month, other._day);
        long long diff = a - b;
        return diff >= 0 ? diff : -diff;
    }

    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }

    void out() const {
        cout << _year << '-' << _month << '-' << _day << '\n';
    }

    friend ostream& operator<<(ostream& os, const Date& dt) {
        os << dt._year << '-' << dt._month << '-' << dt._day;
        return os;
    }
};

static void Test() {
    int op;
    if (!(cin >> op)) return;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        // d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; // (++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; // (d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; // (d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; // (--d0).out();
        cout << d0 << endl;
        // d0.out();
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Test();
    return 0;
}

