#include <bits/stdc++.h>
using namespace std;

struct Date {
    int y, m, d;
};

bool isLeap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int daysInMonth(int y, int m) {
    static const int mdays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeap(y)) return 29;
    return mdays[m];
}

// 统计区间 [1, y] 内闰年的个数
long long leapCount(long long y) {
    if (y <= 0) return 0;
    return y / 4 - y / 100 + y / 400;
}

// 将日期 y-m-d 转成绝对天数序号（从 1 开始），约定 0001-01-01 对应 1
long long toSerial(int y, int m, int d) {
    long long yy = y - 1;
    long long days = yy * 365 + leapCount(yy);
    for (int mm = 1; mm < m; mm++) days += daysInMonth(y, mm);
    days += d;
    return days;
}

// 将绝对天数序号（从 1 开始）反推回具体日期
Date fromSerial(long long serial) {
    // 假设 serial >= 1
    int y = 1;

    // 二分年份
    int l = 1, r = 5000000;
    while (l < r) {
        int mid = l + (r - l + 1) / 2;
        long long startMid = toSerial(mid, 1, 1);
        if (startMid <= serial) l = mid;
        else r = mid - 1;
    }
    y = l;

    long long dayOfYear = serial - toSerial(y, 1, 1) + 1;
    int m = 1;
    while (m <= 12) {
        int dm = daysInMonth(y, m);
        if (dayOfYear > dm) {
            dayOfYear -= dm;
            m++;
        } else {
            break;
        }
    }

    int d = (int)dayOfYear;
    return {y, m, d};
}

// 计算两个日期相差天数（绝对值）
long long diffDays(const Date &a, const Date &b) {
    return llabs(toSerial(a.y, a.m, a.d) - toSerial(b.y, b.m, b.d));
}

// 日期加减天数（delta 可正可负）
Date addDays(const Date &a, long long delta) {
    long long s = toSerial(a.y, a.m, a.d);
    s += delta;
    // 若题目允许年份 <= 0，需要改成更完整的历法处理。
    if (s < 1) s = 1;
    return fromSerial(s);
}

// 星期计算：0=周日, 1=周一, ..., 6=周六
// 以 1970-01-01 为周四（4）作为基准
int weekday(const Date &a) {
    long long base = toSerial(1970, 1, 1);
    long long cur = toSerial(a.y, a.m, a.d);
    long long delta = cur - base;
    int w = (int)((4 + delta) % 7);
    if (w < 0) w += 7;
    return w;
}

int main() {
    // 简单示例
    Date a{2026, 4, 10};
    Date b{2026, 5, 1};

    cout << "diffDays = " << diffDays(a, b) << "\n";

    Date c = addDays(a, 30);
    cout << "a + 30 days = " << c.y << "-" << c.m << "-" << c.d << "\n";

    static const string name[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    cout << "weekday(a) = " << name[weekday(a)] << "\n";

    return 0;
}
