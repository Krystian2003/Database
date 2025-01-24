#ifndef DIALOG_H
#define DIALOG_H
#include "DataBase.h"
#include <QDialog>

// UWAGI
/*
Do wykonania projektu, podczas procesu pisania programu:
inspirowano się lub zaadaptowano kod z książki “Introduction to Programming with C++ for Engineers”, autor: prof. dr hab. inż. Bogusław Cyganek,
wykorzystano bibliotekę nlohmann/json (plik json.hpp), autor: Niels Lohmann, udostepnioną pod adresem nlohmann/json: JSON for Modern C++ - GitHub, przy pracy z formatem JSON (na końcu dokumentu zamieszczono licencję),
inspirowano się lub zaadaptowano kod wygenerowany przez narzędzie ChatGPT 4,
inspirowano się lub zaadaptowano kod ze strony cppreference.com, zawierającą dokumentację i przykłady użycia dla języka C++.
inspirowano się lub zaadaptowano kod zaprezentowany na stronie Qt for Beginners.
*/

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Person* person, DataBase* db, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_OK_b_ed_clicked();

    void on_canc_b_ed_clicked();

private:
    Ui::Dialog *ui;
    DataBase *dataBase;
    Person* ed_person;

signals:
    void accepted();
};

#endif // DIALOG_H
