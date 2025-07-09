#pragma once

//Idee und Code von Robert Puskas
//Mehrere Tests können so in einer Main vereinigt und abgespielt werden
//Siehe: http://www.robert-puskas.info/2019/10/lod-running-multiple-qtest-classes.html

#include <QtTest>

template <typename TestClass>
void runTests(int argc, char* argv[], int* status)
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);
    QTEST_DISABLE_KEYPAD_NAVIGATION TestClass tc;
    *status |= QTest::qExec(&tc, argc, argv);
}
