#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DataBase.h"
#include <QMessageBox>
#include "dialog.h"

// UWAGI
/*
Do wykonania projektu, podczas procesu pisania programu:
inspirowano się lub zaadaptowano kod z książki “Introduction to Programming with C++ for Engineers”, autor: prof. dr hab. inż. Bogusław Cyganek,
wykorzystano bibliotekę nlohmann/json (plik json.hpp), autor: Niels Lohmann, udostepnioną pod adresem nlohmann/json: JSON for Modern C++ - GitHub, przy pracy z formatem JSON (na końcu dokumentu zamieszczono licencję),
inspirowano się lub zaadaptowano kod wygenerowany przez narzędzie ChatGPT 4,
inspirowano się lub zaadaptowano kod ze strony cppreference.com, zawierającą dokumentację i przykłady użycia dla języka C++.
inspirowano się lub zaadaptowano kod zaprezentowany na stronie Qt for Beginners.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dataBase(new DataBase())
{
    ui->setupUi(this);

    odczyt_bledy();

    CheckBoxGroup = new QButtonGroup(this);  // inicjalizacja grupy przycisków

    ui->stackedWidget->setCurrentIndex(0);  // ustawia pierwszą, domyślną stronę (indeks 0)

    ui->return1->hide(); // przycisk return1 ukryty na początku

    ui->komunikat->show();  //komunikat w delete pokazany defaultowo
    ui->komunikat->setText("Brak osoby o danym numerze ID");
    ui->del_table->hide();  //tabela w delete schowana defaultowo

    connect(ui->delete_spinBox, SIGNAL(valueChanged(int)), this, SLOT(on_delete_spinBox_valueChanged(int))); //zmiana wartości w Spinbox - tabela wyswietla coś innego

    connect(ui->endprog, &QPushButton::clicked, this, &QApplication::quit); //przycisk do kończenia programu

    // checkboxy do grupy
    CheckBoxGroup->addButton(ui->add_checkBox);
    CheckBoxGroup->addButton(ui->remove_checkBox);
    CheckBoxGroup->addButton(ui->show_checkBox);

    //tylko jeden checkbox może być zaznaczony
    CheckBoxGroup->setExclusive(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dataBase;

}

// wywoływanie funkcji "odczyt()" z obsługą błędów
void MainWindow::odczyt_bledy()
{
    auto [blad, kod, wiadomosc] = dataBase->odczyt("Baza_danych.json"); // wczytywanie danych z b.d.

    if(blad)
    {
        if(kod == 2)
        {
            QMessageBox::information(nullptr, "Pusty plik", "Plik jest pusty. Inicjalizacja pustej bazy danych.");
        }
        //else
        //{
        //    QMessageBox::information(nullptr, "Wczytano dane", "Wczytywanie zakończone pomyślnie.");
        //}
    }
    else
    {
        switch (kod)
        {
        case 1:
            QMessageBox::critical(nullptr, "Blad", "Nie mozna otworzyc pliku do odczytu.");
            break;
        case 3:
            QMessageBox::warning(nullptr, "Brak danych", "Nie znaleziono użytecznych danych w pliku.");
            break;
        case 4:
             QMessageBox::critical(nullptr, "Błąd", QString("Błąd podczas wczytywania pliku JSON: ")+QString::fromStdString(wiadomosc)+".");
            break;
        }
    }
}

void MainWindow::on_change_page_clicked()
{
    if (ui->show_checkBox->isChecked()) {
        ui->stackedWidget->setCurrentIndex(1); // Strona 2
        DaneDoTabeli();
    }
    else if(ui->add_checkBox->isChecked())
    {
        ui->stackedWidget->setCurrentIndex(2); // Strona 3
    }
    else if(ui->remove_checkBox->isChecked())
    {
        ui->stackedWidget->setCurrentIndex(3); // Strona 4
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0); // Strona 1
    }
}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    if (arg1 == 0) {
        ui->return1->hide();
    } else {
        ui->return1->show();
    }
}

void MainWindow::on_return1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::DaneDoTabeli()
{
    odczyt_bledy();

    const auto& osoby = dataBase->Get_osoby();

    ui->show_table->clearContents(); // stare dane z tabeli usuwane
    ui->show_table->setRowCount(static_cast<int>(osoby.size())); // tyle rzędów ile osób w bazie

    for (int i = 0; i < osoby.size(); ++i)
    {
        const Person& osoba = osoby[i];

        ui->show_table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(osoba.Get_imie())));
        ui->show_table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(osoba.Get_nazw())));
        ui->show_table->setItem(i, 2, new QTableWidgetItem(QString::number(osoba.Get_id())));
        ui->show_table->setItem(i, 3, new QTableWidgetItem(QString::number(osoba.Get_wiek())));
        ui->show_table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_miejscowosc())));
        ui->show_table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_ulica())));
        ui->show_table->setItem(i, 6, new QTableWidgetItem(QString::number(osoba.Get_adres().Get_nrdomu())));
        ui->show_table->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_kraj())));
    }

}

void MainWindow::wyniki_do_tab(const BD& wyniki) {

    ui->show_table->clearContents();
    ui->show_table->setRowCount(wyniki.size());  // ustawia liczbę wierszy na liczbę wyników

    int row = 0;
    for (const auto& osoba : wyniki) {

        ui->show_table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(osoba.Get_imie())));
        ui->show_table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(osoba.Get_nazw())));
        ui->show_table->setItem(row, 2, new QTableWidgetItem(QString::number(osoba.Get_id())));
        ui->show_table->setItem(row, 3, new QTableWidgetItem(QString::number(osoba.Get_wiek())));
        ui->show_table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_miejscowosc())));
        ui->show_table->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_ulica())));
        ui->show_table->setItem(row, 6, new QTableWidgetItem(QString::number(osoba.Get_adres().Get_nrdomu())));
        ui->show_table->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_kraj())));
        row++;
    }
}

void MainWindow::on_search_button_clicked()
{
    QString wybrany_typ = ui->search_by->currentText();

    QString szukane = ui->look_for->text();

    string szukane_str = szukane.toStdString();

    BD poszukuj;

    if (wybrany_typ == "Imię") {
        poszukuj = dataBase->wyszukaj_podfunkcja('I', szukane_str);
    } else if (wybrany_typ == "Nazwisko") {
        poszukuj = dataBase->wyszukaj_podfunkcja('N', szukane_str);
    } else if (wybrany_typ == "Numer ID") {
        poszukuj = dataBase->wyszukaj_podfunkcja('D', szukane_str);
    } else if (wybrany_typ == "Wiek") {
        poszukuj = dataBase->wyszukaj_podfunkcja('W', szukane_str);
    } else if (wybrany_typ == "Miejscowość") {
        poszukuj = dataBase->wyszukaj_podfunkcja('J', szukane_str);
    } else if (wybrany_typ == "Ulica") {
        poszukuj = dataBase->wyszukaj_podfunkcja('U', szukane_str);
    } else if (wybrany_typ == "Numer domu") {
        poszukuj = dataBase->wyszukaj_podfunkcja('M', szukane_str);
    } else if (wybrany_typ == "Kraj") {
        poszukuj = dataBase->wyszukaj_podfunkcja('K', szukane_str);
    }
    wyniki_do_tab(poszukuj);
}

void MainWindow::on_Anuluj_search_clicked()
{
    ui->look_for->clear();
    DaneDoTabeli();
}

void MainWindow::on_dodaj_button_clicked()
{
    QString w_imie = ui->name->text();
    QString w_nazwisko = ui->surname->text();
    int w_id = ui->spinBox_ID->value();
    int w_wiek = ui->spinBox__age->value();
    QString w_miejsc = ui->town->text();
    QString w_ulica = ui->alley->text();
    int w_numd = ui->spinBox_hnum->value();
    QString w_kraj = ui->country->text();

    // w wypadku gdyby pola były puste
    if (w_imie.isEmpty() || w_nazwisko.isEmpty() || w_miejsc.isEmpty() || w_ulica.isEmpty() || w_kraj.isEmpty() || w_id <= 0 || w_wiek <= 0 || w_numd <= 0)
    {
        QMessageBox::warning(this, "Błąd", "Wszystkie pola muszą być wypełnione!");
        return;
    }

    auto [zapis_danych, bool_nowe_id, int_nowe_id] = dataBase->wprowadz(w_imie.toStdString(), w_nazwisko.toStdString(), w_id, w_wiek, w_miejsc.toStdString(), w_ulica.toStdString(), w_numd, w_kraj.toStdString());

    if(zapis_danych)
    {
        QMessageBox::information(nullptr, "Zapisano dane", "Zapisywanie zakończone pomyślnie.");
    }
    else
    {
        QMessageBox::critical(nullptr, "Błąd", "Nie można otworzyć pliku do zapisu.");
    }

    if (bool_nowe_id)
    {
        QMessageBox::information(nullptr, "Błędne ID", "Podane ID było już zajęte. ID zostało zmienione na: " + QString::number(int_nowe_id) + ".");
    }

    // Czyszczone pola po dodaniu osoby
    ui->name->clear();
    ui->surname->clear();
    ui->town->clear();
    ui->alley->clear();
    ui->country->clear();
    ui->spinBox_ID->setValue(0);
    ui->spinBox__age->setValue(0);
    ui->spinBox_hnum->setValue(0);
}


void MainWindow::on_delete_Button_clicked()
{
    int u_id = ui->delete_spinBox->value();
    dataBase->usun(u_id);
    ui->del_table->clearContents();
}

void MainWindow::wyswietl_deltab(int t_id)
{
    BD znaleziony = dataBase->znajdz_usuwanego(t_id);

    if (!znaleziony.empty())
    {

        ui->del_table->clearContents(); // ustawienia dla tablicy
        ui->del_table->setRowCount(1); // z założenia tylko 1 osoba do pokazania

        ui->komunikat->hide();
        ui->del_table->show();

        const Person& osoba = znaleziony[0];

        ui->del_table->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(osoba.Get_imie())));
        ui->del_table->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(osoba.Get_nazw())));
        ui->del_table->setItem(0, 2, new QTableWidgetItem(QString::number(osoba.Get_id())));
        ui->del_table->setItem(0, 3, new QTableWidgetItem(QString::number(osoba.Get_wiek())));
        ui->del_table->setItem(0, 4, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_miejscowosc())));
        ui->del_table->setItem(0, 5, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_ulica())));
        ui->del_table->setItem(0, 6, new QTableWidgetItem(QString::number(osoba.Get_adres().Get_nrdomu())));
        ui->del_table->setItem(0, 7, new QTableWidgetItem(QString::fromStdString(osoba.Get_adres().Get_kraj())));
    }
    else
    {

        ui->del_table->clearContents();
        ui->komunikat->show();
        ui->komunikat->setText("Brak osoby o danym numerze ID");
        ui->del_table->hide();
    }
}

void MainWindow::on_delete_spinBox_valueChanged(int arg1)
{
    wyswietl_deltab(arg1);
}


void MainWindow::on_anuluj_d_clicked()
{
    ui->name->clear();
    ui->surname->clear();
    ui->spinBox_ID->setValue(0);
    ui->spinBox__age->setValue(0);
    ui->town->clear();
    ui->alley->clear();
    ui->spinBox_hnum->setValue(0);
    ui->country->clear();
}

//  obsługa przycisku edycji i wywołanie okna dialogowego
void MainWindow::on_edit_button_clicked()
{
    int val = ui->delete_spinBox->value();
    if(val == 0)
    {
        return;
    }

    Person* persontoedit = dataBase->persona_do_edycji(val);

    if (persontoedit == nullptr) {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono osoby o tym ID.");
        return;
    }

    Dialog dialog(persontoedit, dataBase, this);

    dialog.exec();

    wyswietl_deltab(val);
}

void MainWindow::clearTable()
{
    ui->del_table->clearContents();
    ui->delete_spinBox->setValue(0);
}
