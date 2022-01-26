#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <locale.h>
using namespace std;

class Login {
    string login, haslo;
public:
    bool acces = false;
    void logg() {
        string log, has;
        fstream plikLogowanie;
   
        plikLogowanie.open("loginy.txt", ios::in);
        cout << "Wpisz login" << endl;
        cin >> login;
        cout << "Wpisz haslo" << endl;
        cin >> haslo;

        while (!plikLogowanie.eof()) {
            plikLogowanie >> log;
            plikLogowanie >> has;

            if ((login == log) && (haslo == has)) {
                acces = true;
                cout << "zalogowano pomyslnie" << endl;
                break;
            }

        }
        if (!acces) {
            cout << "nie udalo sie zalogowac" << endl;
            logg();
        }
        plikLogowanie.close();
    }

    void newacc() {
        string has, log;
        cout << "Wpisz login" << endl;
        cin >> log;
        cout << "Wpisz haslo" << endl;
        cin >> has;

        login = log;

        fstream plikLogowanie;
        plikLogowanie.open("loginy.txt", ios::in | ios::app);
        plikLogowanie << log << endl;
        plikLogowanie << has << endl;
        plikLogowanie.close();
        acces = true;
    }
    string getlogin() {
        return login;
    }
};

class User {
    int daysOfDiet;
    string name, lastname, login, password;
    double height, weight, wantWeight, startWeight;
public:
    void newUser(string log) {
        login = log;
        // dodawanie informacji poczatkowych
        cout << "Wpisz swoje imie" << endl;
        cin >> name;
        cout << "Wpisz swoje nazwisko" << endl;
        cin >> lastname;
        cout << "Wpisz swoja wage" << endl;
        cin >> startWeight;
        cout << "Wpisz swoj wzrost w cm" << endl;
        cin >> height;
        cout << "Wpisz swoja docelowa wage" << endl;
        cin >> wantWeight;
        cout << "Wpisz ile dni chcesz sie odchudzac" << endl;
        cin >> daysOfDiet;
        weight = startWeight;

        save();
        
    }

    void oldUser(string log) {
        login = log;
        fstream data;
        data.open(log + ".txt",ios::in);
        if (data.good() == false) {
            cout << "Plik nie istnieje" << endl;
        }
        else {
            string line;
            getline(data, name);
            getline(data, lastname);
            getline(data, line);
            startWeight = stod(line);
            getline(data, line);
            weight = stod(line);
            getline(data, line);
            height = stod(line);
            getline(data, line);
            wantWeight = stod(line);
            getline(data, line);
            daysOfDiet = stoi(line);

            data.close();
        }
    }

    void bmi() {
        double bmi;
        bmi = weight / (height / 100) * (height / 100);
        cout << "Twoje BMI wynosi: " << bmi << endl;
        cout << "-----------------------------" << endl;
        cout << "< 16 - wyglodzenie" << endl;
        cout << "16 - 16.99 - wychudzenie" << endl;
        cout << "17 - 18.49 - niedowaga" << endl;
        cout << "18.5 - 24.99 - waga prawidlowa" << endl;
        cout << "25 - 29.99 - nadwaga" << endl;
        cout << "30 - 34.99 - I stopien otylosci" << endl;
        cout << "35 - 39.99 - II stopieñ otylosci" << endl;
        cout << "> 40 - otylosc skrajna" << endl;


    }

    void changeWeight() {
        double a;
        cout << "Twoja waga: " << weight << endl;
        cout << "Wpisz nowa wage: ";
        cin >> a;
        weight = a;
        save();
    }
    void changeHeight() {
        double a;
        cout << "Twoj wzrost: " << height << endl;
        cout << "Wpisz nowy wzrost: ";
        cin >> a;
        height = a;
        save();
    }
    void changeWantweight() {
        double a;
        cout << "Twoja waga docelowa: " << wantWeight << endl;
        cout << "Wpisz nowa wage docelowa: ";
        cin >> a;
        wantWeight = a;
        save();
    }
    void changeName() {
        string a;
        cout << "Twoje imie: " << name << endl;
        cout << "Wpisz nowe imie: ";
        cin >> a;
        name = a;
        save();
    }
    void changeLastname() {
        string a;
        cout << "Twoje nazwisko: " << lastname << endl;
        cout << "Wpisz nowe nazwisko: ";
        cin >> a;
        lastname = a;
        save();
    }
    void showinfo() {
        cout << "Informacje o uzytkowniku" << endl;
        cout << "Imie: " << name << endl;
        cout << "Nazwisko: " << lastname << endl;
        cout << "Wzrost: " << height << endl;
        cout << "Waga na poczatku: " << startWeight << endl;
        cout << "Waga docelowa: " << wantWeight << endl;
        cout << "Waga w tym momencie: " << weight << endl;
        cout << "Do osiagniecia wagi docelowej brakuje " << weight - wantWeight <<"kg" << endl;
    }

    void save() {
        ofstream File3;
        File3.open(login + ".txt");
        if (File3.is_open()) {
            File3 << name << endl;
            File3 << lastname << endl;
            File3 << startWeight << endl;
            File3 << weight << endl;
            File3 << height << endl;
            File3 << wantWeight << endl;
            File3 << daysOfDiet << endl;
            File3.close();
        }
    }

};

class Plan {
    int kcalTarget, kcalLeft;
public:
    void show(int kcalFood, int kcalAc) {
        cout << "Podaj dzienny cel kaloryczny: " << endl;
        cin >> kcalTarget;
        kcalLeft = kcalTarget - kcalFood + kcalAc;
        cout << "Ilosc kalorii zjedzonych: " << kcalFood << endl;
        cout << "Ilosc spalonych kalorii " << kcalAc << endl;
        cout << "Pozostalo dzisiaj kcal do zjedzenia: " << kcalLeft << endl;
        // system kary i nagrody
        if (kcalLeft > 0) {
            cout << "Gratuluje, nie przekroczyles celu kalorycznego" << endl;
        }
        else {
            cout << "Przekroczyles cel kaloryczny, postaraj sie bardziej" << endl;
        }


    }
};
// dodaje jedzenie i ma kalkulator kalorii
class Food {
    int protein, carbs, fats;
    int kcalToday = 0;
public:
    int cal;
    string kind;
    void addFood(string login) {
        ofstream File;
        File.open(login +"mojadieta.txt", ios::app);
        if (File.is_open()) {
            cout << "Podaj rodzaj jedzenia" << endl;
            cin >> kind;
            cout << "Podaj ilosc zjedzonych kalorii" << endl;
            cin >> cal;
            File << kind << endl;
            File << cal<< endl;
            File.close();
            kcalToday += cal;
        }
    }
    void calories() {
        cout << "Podaj ilosc bialka" << endl;
        cin >> protein;
        cout << "Podaj ilosc tluszczu" << endl;
        cin >> fats;
        cout << "Podaj ilosc weglowodanow" << endl;
        cin >> carbs;
        cal = fats * 9 + protein * 4 + carbs * 4;
        cout << "Iloœæ spozytych kalorii: " << cal << "cal" << endl;
   
    }
    int getKcalFood() {
        return kcalToday;
    }

};
// dodajesz aktywnosci
class Activity {
    int kcal;
    int kcalToday = 0;
public:
    void addActivity(string login) {
        ofstream File;
        File.open(login +"mojtrening.txt", ios::app);
        if (File.is_open()) {
            cout << "Podaj aktywnosc: ";
            string tekst;
            cin >> tekst;
            File << tekst << endl;
            cout << "Podaj ilosc spalonych kalorii" << endl;
            cin >> kcal;
            File << kcal << endl;
            File.close();
            cout << "Podaj ilosc spalonych kalorii" << endl;
            cin >> kcal;
            kcalToday += kcal;
        }
    }
    int getKcalAc() {
        return kcalToday;
    }

};
// wyswietla historie jedzenia i treningow
class History {
public:
    void showtrening(string login) {
        ifstream FileOpen(login +"mojtrening.txt");
        if (FileOpen.is_open()) {
            string line;
            while (getline(FileOpen, line)) {
                cout << line << "\n";
            }
            FileOpen.close();
        }
    }
    void showdiet(string login) {
        ifstream FileOpen(login + "mojadieta.txt");
        if (FileOpen.is_open()) {
            string line;
            while (getline(FileOpen, line)) {
                cout << line << "\n";
            }
            FileOpen.close();
        }
    }


};



int main()
{
    setlocale(LC_CTYPE, "Polish");
    //Tworzymy obiekty
    Login loginojb;
    Activity activityobj;
    Food foodobj;
    User userobj;
    Plan planobj;
    History historyobj;

    //Pierwszy interface
    char c, c1, c2, back;
    bool newuser = 0;
    cout << "1. Logowanie" << endl;
    cout << "2. Nowy uzytkownik" << endl;
    cin >> c;
    system("CLS");

    switch (c) {
    case '1':
        loginojb.logg();
        userobj.oldUser(loginojb.getlogin());
        break;
    case '2':
        newuser = 1;
        loginojb.newacc();
        userobj.newUser(loginojb.getlogin());
        
        break;
    default:
        break;
    }
    system("CLS");


    // jesli nowy uzytkownik dodaj informacje poczatkowe
    //Drugi interface
    while (loginojb.acces == true) {
        system("CLS");
        cout << "MENU" << endl;
        cout << "1. Dodaj aktywnosc" << endl;//
        cout << "2. Dodaj jedzenie" << endl;//
        cout << "3. Profil" << endl;//
        cout << "4. Sprawdz cele" << endl;//
        cout << "5. Sprawdz plan" << endl;//
        cout << "6. Kalkulator kalorii" << endl;//
        cout << "7. Sprawdz BMI" << endl;//
        cout << "8. Test jednostkowy" << endl;//

        cin >> c1;

        switch (c1)
        {
        case '1':
            system("CLS");
            activityobj.addActivity(loginojb.getlogin());
            break;
        case '2':
            system("CLS");
            foodobj.addFood(loginojb.getlogin());
            break;
        case '3':
            system("CLS");
            //Interface 3
            cout << "PROFIL" << endl;
            cout << "1. Wyswietl informacje" << endl;
            cout << "2. Zmien wage" << endl;
            cout << "3. Zmien wzrost" << endl;
            cout << "4. Zmien imie" << endl;
            cout << "5. Zmien nazwisko" << endl;
            cout << "6. Zmien wage docelowa" << endl;
            cout << "7. Cofnij" << endl;
            cin >> c2;
            switch (c2)
            {
            case '1':
                system("CLS");
                userobj.showinfo();
                cout << endl << endl << "|Naciœnij 1 by wyjsc|" << endl;
                cin >> back;
                if (back == 1) {
                    back = 0;
                    system("CLS");
                }
                break;
            case '2':
                system("CLS");
                userobj.changeWeight();
                system("CLS");
                break;
            case '3':
                system("CLS");
                userobj.changeHeight();
                system("CLS");
                break;
            case '4':
                system("CLS");
                userobj.changeName();
                system("CLS");
                break;
            case '5':
                system("CLS");
                userobj.changeLastname();
                system("CLS");
                break;
            case '6':
                system("CLS");
                userobj.changeWantweight();
                system("CLS");
            case '7':
                system("CLS");
                break;
            default:
                break;
            }

            break;
        case '4':
            system("CLS");
            planobj.show(foodobj.getKcalFood(),activityobj.getKcalAc());
            cout << endl << endl << "|Naciœnij 1 by wyjsc|" << endl;
            cin >> back;
            if (back == 1) {
                back = 0;
                system("CLS");
            }
            break;
        case '5':

            system("CLS");
            historyobj.showtrening(loginojb.getlogin());
            historyobj.showdiet(loginojb.getlogin());
            cout << endl << endl << "|Naciœnij 1 by wyjsc|" << endl;
            cin >> back;
            if (back == 1) {
                back = 0;
                system("CLS");
            }
            break;
        case '6':
            system("CLS");
            foodobj.calories();
            cout << endl << endl << "|Naciœnij 1 by wyjsc|" << endl;
            cin >> back;
            if (back == 1) {
                back = 0;
                system("CLS");
            }
            break;
        case '7':
            system("CLS");
            userobj.bmi();
            cout << endl << endl << "|Nacisnij 1 by wyjsc|" << endl;
            cin >> back;
            if (back == 1) {
                back = 0;
                system("CLS");
            }
            break;
            case '8':
            system("CLS");
            for(int i = 0; i<1000; i++){
                userobj.bmi();
            }
            cout << endl << endl << "|Nacisnij 1 by wyjsc|" << endl;
            cin >> back;
            if (back == 1) {
                back = 0;
                system("CLS");
            }
            break;
        default:
            break;
        }


    }
}

/* STANDARDY KODOWANIA:
- Tabulacje - wcięcia przy kolejnych zagnieżdżenach
- Nazwy klas zapisywane dużymi literami
- Brak stosowania obok siebie podobnych cyfr i liter - czytelność kodu
- Wszytskie nazwy funkcji zapisane w standardzie camelCase
*/

/*REFAKTORYZACJA
- Zmiana wszystkich nazw funkcji na takie, które nie zawierają dużych liter - BMI() ->bmi() oraz na standard camelCase w przypadku
nazw dwuczłonoych 
- usunięcie poskich znaków - brak kodowania UTF-8 w GitHub

*/
