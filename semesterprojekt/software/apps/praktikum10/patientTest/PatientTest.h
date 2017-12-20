#ifndef PATIENT_TEST_H
#define PATIENT_TEST_H

#include <qttest>
#include <qstring>
#include "Patient.h"

class PatientTest : public QObject
{
    Q_OBJECT

private slots:

    void constructorTest() {

        Patient p;

        QCOMPARE( p.id(), 0 );
        QVERIFY( p.forename() == "unknown" );
        QVERIFY( p.familyName() == "unknown" );
    }

    void idTest() {

        Patient p;

        p.setId( 10 );
        QCOMPARE( p.id(), 10 );

        p.setId( 1000 );
        QCOMPARE( p.id(), 1000 );
    }

	// ...
    
};

#endif // PATIENT_TEST_H
