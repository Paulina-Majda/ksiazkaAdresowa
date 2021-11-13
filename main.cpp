#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <cstdio>
#include <algorithm>

using namespace std;

int iteratorUzytkownikow;
int iteratorAdresatow;
int idZalogowanegoUzytkownika = -1;

string nazwaPlikuAdresowego = "Adresaci.txt";
string nazwaPlikuUzytkownikow = "Uzytkownicy.txt";
string nazwaPlikuTymczasowego = "Tymczasowy.txt";

struct Uzytkownik{
    int id;
    string nazwa, haslo;
};

struct Kontakt {
    int id;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string email;
    string numer;
    string adres;
};

void dopiszKontaktDoPliku(Kontakt kontakt) {
    fstream fileWriter(nazwaPlikuAdresowego, ios::in | ios::out | ios::app);

    if (fileWriter.is_open()) {
        fileWriter << to_string(kontakt.id) << '|';
        fileWriter << to_string(kontakt.idUzytkownika) << '|';
        fileWriter << kontakt.imie << '|';
        fileWriter << kontakt.nazwisko << '|';
        fileWriter << kontakt.email << '|';
        fileWriter << kontakt.numer << '|';
        fileWriter << kontakt.adres << '|' << endl;
        fileWriter.close();
    } else cout << "Pliku nie udalo sie odczytac.";
}

void wyswietlKontakty(vector<Kontakt> kontakty) {
    cout << endl << "LISTA WSZYSTKICH KONTAKTOW" << endl << endl;
    for (int i = 0; i < kontakty.size(); i++) {
        cout << endl << "Id: " << kontakty[i].id;
        cout << endl << "Imie: " << kontakty[i].imie;
        cout << endl << "Nazwisko: " << kontakty[i].nazwisko;
        cout << endl << "Email: " << kontakty[i].email;
        cout << endl << "Numer telefonu: " << kontakty[i].numer;
        cout << endl << "Adres zamieszkania: " << kontakty[i].adres << endl;
    }
    cout << endl;
}

void stworzKontakt(vector<Kontakt> &kontakty) {

    Kontakt kontakt;

    cout << endl << "ZAPISZ NOWY KONTAKT" << endl << endl;
    cout << "Wpisz imie: ";
    cin >> kontakt.imie;
    cout << "Wpisz nazwisko: ";
    cin >> kontakt.nazwisko;
    cout << "Wpisz adres email: ";
    cin >> kontakt.email;
    cout << "Wpisz numer telefonu: ";
    cin.sync();
    getline(cin, kontakt.numer);
    cout << "Wpisz adres zamieszkania: ";
    cin.sync();
    getline(cin, kontakt.adres);

    kontakt.id = iteratorAdresatow;
    kontakt.idUzytkownika = idZalogowanegoUzytkownika;

    iteratorAdresatow++;
    kontakty.push_back(kontakt);
    dopiszKontaktDoPliku(kontakt);

    system("cls");
}

void znajdzImie(vector<Kontakt> kontakty) {
    string imie;

    cout << endl << "WYSZUKIWANIE KONTAKTOW PO IMIENIU" << endl << endl;
    cout << "Wpisz imie kontaktu, ktorego szukasz: ";
    cin >> imie;

    system("cls");
    cout << endl << "KONTAKTY ZAWIERAJACE PODANE IMIE: " << imie << endl << endl;
    for (int i = 0; i < kontakty.size(); i++) {
        if (kontakty[i].imie == imie) {
            cout << endl << "Id: " << kontakty[i].id;
            cout << endl << "Imie: " << kontakty[i].imie;
            cout << endl << "Nazwisko: " << kontakty[i].nazwisko;
            cout << endl << "Email: " << kontakty[i].email;
            cout << endl << "Numer telefonu: " << kontakty[i].numer;
            cout << endl << "Adres zamieszkania: " << kontakty[i].adres << endl;
        }
    }
    cout << endl << endl;
}

void znajdzNazwisko(vector<Kontakt> kontakty) {
    string nazwisko;

    cout << endl << "WYSZUKIWANIE KONTAKTOW PO NAZWISKU" << endl << endl;
    cout << "Wpisz nazwisko kontaktu, ktorego szukasz: ";
    cin >> nazwisko;

    system("cls");
    cout << endl << "KONTAKTY ZAWIEAJACE PODANE NAZWISKO: " << nazwisko << endl << endl;
    for (int i = 0; i < kontakty.size(); i++) {
        if (kontakty[i].nazwisko == nazwisko) {
            cout << endl << "Id: " << kontakty[i].id;
            cout << endl << "Imie: " << kontakty[i].imie;
            cout << endl << "Nazwisko: " << kontakty[i].nazwisko;
            cout << endl << "Email: " << kontakty[i].email;
            cout << endl << "Numer telefonu: " << kontakty[i].numer;
            cout << endl << "Adres zamieszkania: " << kontakty[i].adres << endl;
        }
    }
    cout << endl << endl;
}

void zapiszKontaktyDoPliku(vector<Kontakt> kontakty){
    fstream fileWriter(nazwaPlikuAdresowego, ios::in | ios::out | ios::trunc);

    if (fileWriter.is_open()){
        for (int i = 0; i < kontakty.size(); i++){
            fileWriter << kontakty[i].id << "|";
            fileWriter << kontakty[i].idUzytkownika << "|";
            fileWriter << kontakty[i].imie << "|";
            fileWriter << kontakty[i].nazwisko << "|";
            fileWriter << kontakty[i].email << "|";
            fileWriter << kontakty[i].numer << "|";
            fileWriter << kontakty[i].adres << "|" << endl;
        }
        fileWriter.close();
    } else cout << "Pliku nie udalo sie odczytac.";
}

void usunKontaktWPliku(int idKontaktu){
    fstream fileWriterAdresaci(nazwaPlikuAdresowego, ios::in | ios::out | ios::app);
    fstream fileWriterTymczasowy(nazwaPlikuTymczasowego, ios::in | ios::out | ios::trunc);

    string bufor;
    int n;
    int licznik = 1;

    while(getline(fileWriterAdresaci, bufor, '|')){
        bufor.erase(remove(bufor.begin(), bufor.end(), '\n'), bufor.end());
        switch(licznik){
        case 1:
            if (to_string(idKontaktu) == bufor){
                n = 6;
                while (n > 0){
                    getline(fileWriterAdresaci, bufor, '|');
                    n--;
                }
                licznik = 0;
            } else {
                if (bufor != "\0"){
                    fileWriterTymczasowy << bufor << "|";
                }
            }
            break;
        case 2:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 3:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 4:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 5:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 6:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 7:
            fileWriterTymczasowy << bufor << "|" << endl;
            licznik = 0;
            break;
        }
        licznik++;
    }

    fileWriterTymczasowy.close();
    fileWriterAdresaci.close();

    char charPlikAdresowy[nazwaPlikuAdresowego.size() + 1];
    strcpy(charPlikAdresowy, nazwaPlikuAdresowego.c_str());

    char charPlikTymczasowy[nazwaPlikuTymczasowego.size() + 1];
    strcpy(charPlikTymczasowy, nazwaPlikuTymczasowego.c_str());

    int rezultatUsuwania = remove(charPlikAdresowy);
    if (rezultatUsuwania == 0){
        rename(charPlikTymczasowy, charPlikAdresowy);
    }
}

void usunKontakt(vector<Kontakt> &kontakty){

    int indeksDoUsuniecia = 0;
    char potwierdzenie;

    int idKontaktu;

    cout << endl << "USUWANIE KONTAKTU O PODANYM ID" << endl << endl;
    cout << "Podaj id kontaktu, ktory chcesz usunac: ";
    cin >> idKontaktu;

    for (int i = 0; i < kontakty.size(); i++){
        if (kontakty[i].id == idKontaktu){
            indeksDoUsuniecia = i;
        }
    }

    cout << "Potwierdz chec usuniecia tego kontaktu poprzez wcisniecie litery t: ";
    cin >> potwierdzenie;
    if(potwierdzenie == 't'){
        kontakty.erase(kontakty.begin() + indeksDoUsuniecia);
        usunKontaktWPliku(idKontaktu);
    }

    system("cls");
}

vector<Kontakt> zaladujKontakty() {
    fstream fileWriter(nazwaPlikuAdresowego, ios::in | ios::out | ios::app);

    string bufor;
    int najwiekszeId = 0;
    Kontakt kontakt;
    vector<Kontakt> kontakty;

    int licznik = 1;

    while(getline(fileWriter, bufor, '|')){
        bufor.erase(remove(bufor.begin(), bufor.end(), '\n'), bufor.end());
        switch(licznik){
        case 1:
            kontakt.id = atoi(bufor.c_str());
            if (kontakt.id > najwiekszeId){
                najwiekszeId = kontakt.id;
            }
            break;
        case 2:
            if (atoi(bufor.c_str()) != idZalogowanegoUzytkownika){
                int n = 5;
                while (n > 0){
                    getline(fileWriter, bufor, '|');
                    n--;
                }
                licznik = 0;
            } else {
                kontakt.idUzytkownika = atoi(bufor.c_str());
                break;
            }
        case 3:
            kontakt.imie = bufor;
            break;
        case 4:
            kontakt.nazwisko = bufor;
            break;
        case 5:
            kontakt.email = bufor;
            break;
        case 6:
            kontakt.numer = bufor;
            break;
        case 7:
            kontakt.adres = bufor;
            kontakty.push_back(kontakt);
            licznik = 0;
            break;
        }
        licznik++;
    }

    iteratorAdresatow = najwiekszeId + 1;
    return kontakty;
}

void edytujKontaktWPliku(int idDoEdycji, char opcja, string noweDane, vector<Kontakt> &kontakty){

    fstream fileWriterAdresaci(nazwaPlikuAdresowego, ios::in | ios::out | ios::app);
    fstream fileWriterTymczasowy(nazwaPlikuTymczasowego, ios::in | ios::out | ios::trunc);

    string bufor;
    Kontakt kontakt;
    int n;
    int licznik = 1;

    while(getline(fileWriterAdresaci, bufor, '|')){
        bufor.erase(remove(bufor.begin(), bufor.end(), '\n'), bufor.end());
        switch(licznik){
        case 1:
            if (to_string(idDoEdycji) == bufor){
                kontakt.id = atoi(bufor.c_str());
                getline(fileWriterAdresaci, bufor, '|');
                kontakt.idUzytkownika = atoi(bufor.c_str());
                getline(fileWriterAdresaci, bufor, '|');
                kontakt.imie = bufor;
                getline(fileWriterAdresaci, bufor, '|');
                kontakt.nazwisko = bufor;
                getline(fileWriterAdresaci, bufor, '|');
                kontakt.email = bufor;
                getline(fileWriterAdresaci, bufor, '|');
                kontakt.numer = bufor;
                getline(fileWriterAdresaci, bufor, '|');
                kontakt.adres = bufor;

                switch (opcja){
                case '1':
                    kontakt.imie = noweDane;
                    break;
                case '2':
                    kontakt.nazwisko = noweDane;
                    break;
                case '3':
                    kontakt.email = noweDane;
                    break;
                case '4':
                    kontakt.numer = noweDane;
                    break;
                case '5':
                    kontakt.adres = noweDane;
                    break;
                }

                if (fileWriterTymczasowy.is_open()) {
                    fileWriterTymczasowy << to_string(kontakt.id) << '|';
                    fileWriterTymczasowy << to_string(kontakt.idUzytkownika) << '|';
                    fileWriterTymczasowy << kontakt.imie << '|';
                    fileWriterTymczasowy << kontakt.nazwisko << '|';
                    fileWriterTymczasowy << kontakt.email << '|';
                    fileWriterTymczasowy << kontakt.numer << '|';
                    fileWriterTymczasowy << kontakt.adres << '|' << endl;
                } else cout << "Pliku nie udalo sie odczytac.";

                licznik = 0;

            } else {
                if (bufor != "\0"){
                    fileWriterTymczasowy << bufor << "|";
                }
            }
            break;
        case 2:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 3:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 4:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 5:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 6:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 7:
            fileWriterTymczasowy << bufor << "|" << endl;
            licznik = 0;
            break;
        }
        licznik++;
    }

    fileWriterTymczasowy.close();
    fileWriterAdresaci.close();

    char charPlikAdresowy[nazwaPlikuAdresowego.size() + 1];
    strcpy(charPlikAdresowy, nazwaPlikuAdresowego.c_str());

    char charPlikTymczasowy[nazwaPlikuTymczasowego.size() + 1];
    strcpy(charPlikTymczasowy, nazwaPlikuTymczasowego.c_str());

    int rezultatUsuwania = remove(charPlikAdresowy);
    if (rezultatUsuwania == 0){
        rename(charPlikTymczasowy, charPlikAdresowy);
        kontakty = zaladujKontakty();
    }
}

void menuEdycjiKontaktu(vector<Kontakt> &kontakty){

    int idDoEdycji;
    char opcja;
    string noweDane;

    cout << endl << "EDYCJA KONTAKTU CZ 1" << endl << endl;
    cout << endl << "1. Wybierz id uzytkownika do edycji" << endl;
    cout << endl << "Twoj wybor: ";

    cin >> idDoEdycji;

    cout << endl << "EDYCJA KONTAKTU CZ 2" << endl << endl;
    cout << "1. Zmien imie" << endl;
    cout << "2. Zmien nazwisko" << endl;
    cout << "3. Zmien adres email" << endl;
    cout << "4. Zmien telefon" << endl;
    cout << "5. Zmien adres" << endl;
    cout << "6. Powrot do menu" << endl;
    cout << endl << "Twoj wybor: ";

    cin >> opcja;

    cout << endl << "EDYCJA KONTAKTU CZ 3" << endl << endl;
    cout << "1. Wprowadz ";

    switch (opcja){
        case '1':
            cout << "nowe imie\nTwoj wybor: ";
            cin >> noweDane;
            break;
        case '2':
            cout << "nowe nazwisko\nTwoj wybor: ";
            cin >> noweDane;
            break;
        case '3':
            cout << "nowy adres email\nTwoj wybor: ";
            cin >> noweDane;
            break;
        case '4':
            cout << "nowy telefon\nTwoj wybor: ";
            cin.sync();
            getline(cin, noweDane);
            break;
        case '5':
            cout << "nowy adres\nTwoj wybor: ";
            cin.sync();
            getline(cin, noweDane);
            break;
    }

    edytujKontaktWPliku(idDoEdycji, opcja, noweDane, kontakty);
}

void zmianaHasla(){
    string stareHaslo, noweHaslo;

    cout << endl << "ZMIANA HASLA" << endl << endl;
    cout << endl << "Wprowadz nowe haslo: ";
    cin >> noweHaslo;

    fstream fileWriterUzytkownicy(nazwaPlikuUzytkownikow, ios::in | ios::out | ios::app);
    fstream fileWriterTymczasowy(nazwaPlikuTymczasowego, ios::in | ios::out | ios::trunc);

    string bufor;
    int n;
    int licznik = 1;

    while(getline(fileWriterUzytkownicy, bufor, '|')){
        bufor.erase(remove(bufor.begin(), bufor.end(), '\n'), bufor.end());
        switch(licznik){
        case 1:
            if (to_string(idZalogowanegoUzytkownika) == bufor){
                fileWriterTymczasowy << to_string(idZalogowanegoUzytkownika) << '|';
                getline(fileWriterUzytkownicy, bufor, '|');
                fileWriterTymczasowy << bufor << '|';
                getline(fileWriterUzytkownicy, bufor, '|');
                fileWriterTymczasowy << noweHaslo << '|' << endl;
                licznik = 0;
            } else {
                if (bufor != "\0"){
                    fileWriterTymczasowy << bufor << "|";
                }
            }
            break;
        case 2:
            fileWriterTymczasowy << bufor << "|";
            break;
        case 3:
            fileWriterTymczasowy << bufor << "|" << endl;
            licznik = 0;
            break;
        }
        licznik++;
    }

    fileWriterTymczasowy.close();
    fileWriterUzytkownicy.close();

    char charPlikUzytkownicy[nazwaPlikuUzytkownikow.size() + 1];
    strcpy(charPlikUzytkownicy, nazwaPlikuUzytkownikow.c_str());

    char charPlikTymczasowy[nazwaPlikuTymczasowego.size() + 1];
    strcpy(charPlikTymczasowy, nazwaPlikuTymczasowego.c_str());

    int rezultatUsuwania = remove(charPlikUzytkownicy);
    if (rezultatUsuwania == 0){
        rename(charPlikTymczasowy, charPlikUzytkownicy);
    }
    cout << "Haslo zmienione pomyslnie!";
}


void menuKsiazkiAdresowej() {
    vector<Kontakt> kontakty = zaladujKontakty();

    char wybor;
    bool petla = true;

    while (petla) {
        cout << endl << "KSIAZKA ADRESOWA" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "8. Wyloguj" << endl;
        cout << endl << "Twoj wybor: ";
        cin >> wybor;
        system("cls");

        switch(wybor) {
        case '1':
            stworzKontakt(kontakty);
            break;
        case '2':
            znajdzImie(kontakty);
            break;
        case '3':
            znajdzNazwisko(kontakty);
            break;
        case '4':
            wyswietlKontakty(kontakty);
            break;
        case '5':
            usunKontakt(kontakty);
            break;
        case '6':
            menuEdycjiKontaktu(kontakty);
            break;
        case '7':
            zmianaHasla();
            break;
        case '8':
            idZalogowanegoUzytkownika = -1;
            petla = false;
            break;
        }

    }
}

vector<Uzytkownik> zaladujUzytkownikow(){
    fstream fileWriter(nazwaPlikuUzytkownikow, ios::in | ios::out | ios::app);

    string bufor;
    int najwiekszeId = 0;
    Uzytkownik uzytkownik;
    vector<Uzytkownik> uzytkownicy;

    int licznik = 1;

    while(getline(fileWriter, bufor, '|')){
        bufor.erase(remove(bufor.begin(), bufor.end(), '\n'), bufor.end());
        switch(licznik){
        case 1:
            uzytkownik.id = atoi(bufor.c_str());
            if (uzytkownik.id > najwiekszeId){
                najwiekszeId = uzytkownik.id;
            }
            break;
        case 2:
            uzytkownik.nazwa = bufor;
            break;
        case 3:
            uzytkownik.haslo = bufor;
            licznik = 0;
            uzytkownicy.push_back(uzytkownik);
            break;
        }
        licznik++;
    }

    iteratorUzytkownikow = najwiekszeId + 1;
    return uzytkownicy;
}

bool rejestracja(vector<Uzytkownik> &uzytkownicy){
    string nazwa, haslo;
    bool poprawnoscLoginu = false;

    system("cls");
    while (poprawnoscLoginu != true){
        cout << "Podaj nazwe uzytkownika: ";
        cin >> nazwa;

        poprawnoscLoginu = true;
        for (int i = 0; i < uzytkownicy.size(); i++){
            if(uzytkownicy[i].nazwa == nazwa){
                cout << "Podana nazwa jest juz w uzyciu\n";
                poprawnoscLoginu = false;
            }
        }
    }

    cout << "Podaj haslo: ";
    cin >> haslo;
    Uzytkownik nowy;

    nowy.id = iteratorUzytkownikow;
    nowy.nazwa = nazwa;
    nowy.haslo = haslo;

    fstream fileWriter(nazwaPlikuUzytkownikow, ios::in | ios::out | ios::app);

    if (fileWriter.is_open()) {
        fileWriter << to_string(nowy.id) << '|';
        fileWriter << nowy.nazwa << '|';
        fileWriter << nowy.haslo << '|' << endl;
        fileWriter.close();

        uzytkownicy.push_back(nowy);
        iteratorUzytkownikow++;
    } else {
        cout << "Pliku [" + nazwaPlikuUzytkownikow + "] nie udalo sie odczytac.";
        return false;
    }

    cout<<"Konto uzytkownika zostalo pomyslnie utworzone"<<endl;
    return true;
}

bool logowanie(vector<Uzytkownik> &uzytkownicy){
    string nazwa, haslo;
    system("cls");

    int proba = 0;
    while(proba < 3){
        cout << "Podaj nazwe uzytkownika: ";
        cin >> nazwa;
        cout << "Podaj haslo: ";
        cin >> haslo;

        for (int i = 0; i < uzytkownicy.size(); i++){
            if ((uzytkownicy[i].nazwa == nazwa) && (uzytkownicy[i].haslo == haslo)){
                idZalogowanegoUzytkownika = uzytkownicy[i].id;
                cout << "Logowanie zakonczone pomyslnie\n";
                return true;
            }
        }
        cout << "Niepoprawne dane logowania. Sprobuj ponownie\n";
        proba++;
    }
    cout << "Wpisales bledne haslo 3 razy!. Operacja zakonczona niepowodzeniem";
    return false;
}

int main()
{
    vector<Uzytkownik> uzytkownicy = zaladujUzytkownikow();

    bool powodzenieRejestracji;
    bool powodzenieLogowania = false;

    char wybor;

    while (1) {
        cout << endl << "MENU REJESTRACJI/LOGOWANIA" << endl << endl;
        cout << "1. Rejestracja"<<endl;
        cout << "2. Logowanie"<<endl;
        cout << "9. Zakoncz program"<<endl;
        cout << endl << "Twoj wybor: ";
        cin >> wybor;
        system("cls");

        switch(wybor) {
        case '1':
            powodzenieRejestracji = rejestracja(uzytkownicy);
            break;
        case '2':
            powodzenieLogowania = logowanie(uzytkownicy);
            if ((powodzenieLogowania == true) && (idZalogowanegoUzytkownika >= 0)){
                menuKsiazkiAdresowej();
            }
            break;
        case '9':
            exit(0);
            break;
        }
    }
}
