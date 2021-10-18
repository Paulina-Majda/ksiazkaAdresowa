#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int idIterator;

struct Contact {
    int id;
    string firstName;
    string lastName;
    string email;
    string phoneNumber;
    string address;
};

int findMaxId(vector<Contact> contacts) {
    int iterator;
    if (contacts.size() > 0) {
        iterator = contacts[0].id;
    } else {
        return 1;
    }
    for (int i = 0; i < contacts.size(); i++) {
        if (iterator < contacts[i].id) iterator = contacts[i].id;
    }
    return iterator + 1;
}

void saveContactToFile(Contact contact) {
    fstream fileWriter("ksiazkaAdresowa.txt", ios::in | ios::out | ios::app);

    if (fileWriter.is_open()) {
        fileWriter << to_string(contact.id) << '|';
        fileWriter << contact.firstName << '|';
        fileWriter << contact.lastName << '|';
        fileWriter << contact.email << '|';
        fileWriter << contact.phoneNumber << '|';
        fileWriter << contact.address << '|' << endl;
        fileWriter.close();
    } else cout << "Pliku nie udalo sie odczytac.";
}

void showContacts(vector<Contact> contacts) {
    cout << endl << "LISTA WSZYSTKICH KONTAKTOW" << endl << endl;
    for (int i = 0; i < contacts.size(); i++) {
        cout << endl << "Id: " << contacts[i].id;
        cout << endl << "Imie: " << contacts[i].firstName;
        cout << endl << "Nazwisko: " << contacts[i].lastName;
        cout << endl << "Email: " << contacts[i].email;
        cout << endl << "Numer telefonu: " << contacts[i].phoneNumber;
        cout << endl << "Adres zamieszkania: " << contacts[i].address << endl;
    }
    cout << endl;
}

void createContact(vector<Contact> &contacts) {

    Contact contact;

    cout << endl << "ZAPISZ NOWY KONTAKT" << endl << endl;
    cout << "Wpisz imie: ";
    cin >> contact.firstName;
    cout << "Wpisz nazwisko: ";
    cin >> contact.lastName;
    cout << "Wpisz adres email: ";
    cin >> contact.email;
    cout << "Wpisz numer telefonu: ";
    cin.sync();
    getline(cin, contact.phoneNumber);
    cout << "Wpisz adres zamieszkania: ";
    cin.sync();
    getline(cin, contact.address);

    contact.id = idIterator;
    idIterator++;
    contacts.push_back(contact);

    saveContactToFile(contact);

    system("cls");
}

void findWithFirstName(vector<Contact> contacts) {
    string firstName;

    cout << endl << "WYSZUKIWANIE KONTAKTOW PO IMIENIU" << endl << endl;
    cout << "Wpisz imie kontaktu, ktorego szukasz: ";
    cin >> firstName;

    system("cls");
    cout << endl << "KONTAKTY ZAWIERAJACE PODANE IMIE: " << firstName << endl << endl;
    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].firstName == firstName) {
            cout << endl << "Id: " << contacts[i].id;
            cout << endl << "Imie: " << contacts[i].firstName;
            cout << endl << "Nazwisko: " << contacts[i].lastName;
            cout << endl << "Email: " << contacts[i].email;
            cout << endl << "Numer telefonu: " << contacts[i].phoneNumber;
            cout << endl << "Adres zamieszkania: " << contacts[i].address << endl;
        }
    }
    cout << endl << endl;
}

void findWithLastName(vector<Contact> contacts) {
    string lastName;

    cout << endl << "WYSZUKIWANIE KONTAKTOW PO NAZWISKU" << endl << endl;
    cout << "Wpisz nazwisko kontaktu, ktorego szukasz: ";
    cin >> lastName;

    system("cls");
    cout << endl << "KONTAKTY ZAWIEAJACE PODANE NAZWISKO: " << lastName << endl << endl;
    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].lastName == lastName) {
            cout << endl << "Id: " << contacts[i].id;
            cout << endl << "Imie: " << contacts[i].firstName;
            cout << endl << "Nazwisko: " << contacts[i].lastName;
            cout << endl << "Email: " << contacts[i].email;
            cout << endl << "Numer telefonu: " << contacts[i].phoneNumber;
            cout << endl << "Adres zamieszkania: " << contacts[i].address << endl;
        }
    }
    cout << endl << endl;
}

void saveWholeVectorAsFile(vector<Contact> contacts){
    fstream fileWriter("ksiazkaAdresowa.txt", ios::in | ios::out | ios::trunc);

    if (fileWriter.is_open()){
        for (int i = 0; i < contacts.size(); i++){
            fileWriter << contacts[i].id << "|";
            fileWriter << contacts[i].firstName << "|";
            fileWriter << contacts[i].lastName << "|";
            fileWriter << contacts[i].email << "|";
            fileWriter << contacts[i].phoneNumber << "|";
            fileWriter << contacts[i].address << "|" << endl;
        }
        fileWriter.close();
    } else cout << "Pliku nie udalo sie odczytac.";
}

void removeById(vector<Contact> &contacts){

    int indexToRemove = 0;
    char removeContact;

    int idToRemove;

    cout << endl << "USUWANIE KONTAKTU O PODANYM ID" << endl << endl;
    cout << "Podaj id kontaktu, ktory chcesz usunac: ";
    cin >> idToRemove;

    for (int i = 0; i < contacts.size(); i++){
        if (contacts[i].id == idToRemove){
            indexToRemove = i;
        }
    }

    cout << "Potwierdz chec usuniecia tego kontaktu poprzez wcisniecie litery t: ";
    cin >> removeContact;
    if(removeContact == 't'){
        contacts.erase(contacts.begin() + indexToRemove);
        saveWholeVectorAsFile(contacts);
    }

    system("cls");
}

void readFileToVector(vector<Contact> &contacts) {
    fstream fileWriter("ksiazkaAdresowa.txt", ios::in | ios::out | ios::app);

    string line;
    Contact contact;

    int counter = 1;

    while(getline(fileWriter, line, '|')){
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        switch(counter){
        case 1:
            contact.id = atoi(line.c_str());
            break;
        case 2:
            contact.firstName = line;
            break;
        case 3:
            contact.lastName = line;
            break;
        case 4:
            contact.email = line;
            break;
        case 5:
            contact.phoneNumber = line;
            break;
        case 6:
            contact.address = line;
            contacts.push_back(contact);
            counter = 0;
            break;
        }
        counter++;
    }
}

void editContact(int idToEdit, char editOption, string input, vector<Contact> &contacts){
    Contact *contact;

    for (int i = 0; i < contacts.size(); i++){
        if (contacts[i].id == idToEdit){
            contact = &contacts[i];
        }
    }

    switch (editOption){
        case '1':
            contact->firstName = input;
            break;
        case '2':
            contact->lastName = input;
            break;
        case '3':
            contact->email = input;
            break;
        case '4':
            contact->phoneNumber = input;
            break;
        case '5':
            contact->address = input;
            break;
    }

    saveWholeVectorAsFile(contacts);
}

void editContactMenu(vector<Contact> &contacts){

    int idToEdit;
    char editOption;
    string input;

    cout << endl << "EDYCJA KONTAKTU CZ 1" << endl << endl;
    cout << endl << "1. Wybierz id uzytkownika do edycji" << endl;
    cout << endl << "Twoj wybor: ";

    cin >> idToEdit;

    cout << endl << "EDYCJA KONTAKTU CZ 2" << endl << endl;
    cout << "1. Zmien imie" << endl;
    cout << "2. Zmien nazwisko" << endl;
    cout << "3. Zmien adres email" << endl;
    cout << "4. Zmien telefon" << endl;
    cout << "5. Zmien adres" << endl;
    cout << "6. Powrot do menu" << endl;
    cout << endl << "Twoj wybor: ";

    cin >> editOption;

    cout << endl << "EDYCJA KONTAKTU CZ 3" << endl << endl;
    cout << "1. Wprowadz ";

    switch (editOption){
        case '1':
            cout << "nowe imie\nTwoj wybor: ";
            cin >> input;
            break;
        case '2':
            cout << "nowe nazwisko\nTwoj wybor: ";
            cin >> input;
            break;
        case '3':
            cout << "nowy adres email\nTwoj wybor: ";
            cin >> input;
            break;
        case '4':
            cout << "nowy telefon\nTwoj wybor: ";
            cin >> input;
            break;
        case '5':
            cout << "nowy adres\nTwoj wybor: ";
            cin >> input;
            break;
    }

    editContact(idToEdit, editOption, input, contacts);
}

void showMenu() {
    cout << endl << "KSIAZKA ADRESOWA" << endl << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zakoncz program" << endl;
    cout << endl << "Twoj wybor: ";
}

int main() {
    system("cls");
    vector<Contact> contacts;

    readFileToVector(contacts);
    idIterator = findMaxId(contacts);

    char option, editOption;
    int editId;

    while (1) {
        showMenu();
        cin >> option;
        system("cls");

        switch(option) {
        case '1':
            createContact(contacts);
            break;
        case '2':
            findWithFirstName(contacts);
            break;
        case '3':
            findWithLastName(contacts);
            break;
        case '4':
            showContacts(contacts);
            break;
        case '5':
            removeById(contacts);
            break;
        case '6':
            editContactMenu(contacts);
            break;
        case '7':
            exit(0);
            break;
        }
    }

    system("pause");
    return 0;
}
