#ifndef DATABASE_TEST_H
#define DATABASE_TEST_H

#include <qttest>
#include <qdebug>
#include <qlist>
#include "Patient.h"
#include "DataBase.h"

class DataBaseTest : public QObject
{
    Q_OBJECT

    void printPatient( const Patient& p ) {

        qDebug() << p.id();
        qDebug() << p.forename();
        qDebug() << p.familyName();
    }

private slots:

    /**
     * @brief initTestCase wird einmal vor allen Tests aufgerufen
     */
    void initTestCase() {

        bool result = DataBase::open( ":memory:", "vetter", "test" );
        QVERIFY( result ); // "Tabelle Patient konnte nicht angelegt werden!"
    }

    /**
     * @brief init wird vor jeder Testmethode Aufgerufen
     */
    void init() {
    }

    /**
     * @brief createTablePatientTest
     */
    void createTablePatientTest() {

        bool result = DataBase::createTablePatient();
        QVERIFY( result ); // "Tabelle Patient konnte nicht angelegt werden!"
    }

    /**
     * @brief addPatientTest
     */
    void addPatientTest() {

        Patient p;

        p.setId( 1 );
        p.setForename( "Peter" );
        p.setFamilyName( "Pan" );

        bool result = DataBase::addPatient( p );

        QVERIFY( result );

        p.setId( 2 );
        p.setForename( "Theodor" );
        p.setFamilyName( "Adorno" );
        result = DataBase::addPatient( p );
        QVERIFY( result );
    }

    /**
     * @brief readPatientTest
     */
    void readPatientTest() {

        Patient p;

        bool result = DataBase::readPatient( 1, p );
        QVERIFY( result );
        QVERIFY( p.id() == 1 );
        QVERIFY( p.forename() == "Peter" );
        QVERIFY( p.familyName() == "Pan" );

        result = DataBase::readPatient( 2, p );
        QVERIFY( result );
        QVERIFY( p.id() == 2 );
        QVERIFY( p.forename() == "Theodor" );
        QVERIFY( p.familyName() == "Adorno" );
    }

    /**
     * @brief changePatientTest
     */
    void changePatientTest() {

        Patient p;
        bool result = DataBase::readPatient( 1, p );
        QVERIFY( result );
        // printPatient( p );

        p.setForename( "James" );
        p.setFamilyName( "Barrie" );
        result = DataBase::changePatient( p );
        QVERIFY( result );

        Patient p2;
        result = DataBase::readPatient( 1, p2 );
        QVERIFY( result );

        // printPatient( p2 );
        QVERIFY( p.forename() == "James" );
        QVERIFY( p.familyName() == "Barrie" );

        // zurücksetzen
        p2.setForename( "Peter" );
        p2.setFamilyName( "Pan" );
        result = DataBase::changePatient( p2 );
        QVERIFY( result );
        // printPatient( p2 );
    }

    /**
     * @brief readAllPatientTest
     */
    void readAllPatientTest() {

        qDebug() << "Start readAllPatientTest";
        typedef QList<Patient*> PatientenList;
        PatientenList patientenList;

        bool result = DataBase::readAllPatient( patientenList );
        QVERIFY( result );

        qDebug() << "Size: " << patientenList.size();

        PatientenList::iterator i = patientenList.begin();
        const PatientenList::iterator end = patientenList.end();

        while ( i != end )
            printPatient( *(*i++) );

        QVERIFY( patientenList[0]->forename() == "Peter" );
        QVERIFY( patientenList[0]->familyName() == "Pan" );

        QVERIFY( patientenList[1]->forename() == "Theodor" );
        QVERIFY( patientenList[1]->familyName() == "Adorno" );
    }

    void addPatientBenchmark() {

        Patient p;

        p.setId( 3 );
        p.setForename( "Michael" );
        p.setFamilyName( "Schumacher" );

        QBENCHMARK {
            DataBase::addPatient( p );
        }
    }

    /**
     * @brief cleanup wird nach jeder TestMethode aufgerufen
     */
    void cleanup() {

    }

    /**
     * @brief cleanupTestCase wird am Ende nach allen Testfällen aufgerufen
     */
    void cleanupTestCase() {

        DataBase::close();
    }
};

#endif // DATABASE_TEST_H
