#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DataBase.h"

#include <QMainWindow>
#include <QButtonGroup>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

// UWAGI
/*
Do wykonania projektu, podczas procesu pisania programu:
inspirowano się lub zaadaptowano kod z książki “Introduction to Programming with C++ for Engineers”, autor: prof. dr hab. inż. Bogusław Cyganek,
wykorzystano bibliotekę nlohmann/json (plik json.hpp), autor: Niels Lohmann, udostepnioną pod adresem nlohmann/json: JSON for Modern C++ - GitHub, przy pracy z formatem JSON (na końcu dokumentu zamieszczono licencję),
inspirowano się lub zaadaptowano kod wygenerowany przez narzędzie ChatGPT 4,
inspirowano się lub zaadaptowano kod ze strony cppreference.com, zawierającą dokumentację i przykłady użycia dla języka C++.
inspirowano się lub zaadaptowano kod zaprezentowany na stronie Qt for Beginners.
*/

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_change_page_clicked();

    void on_return1_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void DaneDoTabeli();

    void on_search_button_clicked();

    void wyniki_do_tab(const BD& wyniki);

    void on_dodaj_button_clicked();

    void on_delete_Button_clicked();

    void on_delete_spinBox_valueChanged(int arg1);

    void wyswietl_deltab(int t_id);

    void on_anuluj_d_clicked();

    void on_Anuluj_search_clicked();

    void on_edit_button_clicked();

    void clearTable();

    void odczyt_bledy();

private:
    Ui::MainWindow *ui;
    DataBase *dataBase;
    QButtonGroup *CheckBoxGroup;  // Grupa checkboxów
};
#endif // MAINWINDOW_H
