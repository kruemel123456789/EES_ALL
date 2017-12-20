#include <QtTest>
#include <QCoreApplication>

#include "PatientTest.h"
// #include "DataBaseTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    PatientTest patientTest;
    DataBaseTest dataBaseTest;

    QTest::qExec(&patientTest, argc, argv);
    // QTest::qExec(&dataBaseTest, argc, argv);

    return 0;
}
