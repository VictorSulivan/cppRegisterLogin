#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Temp {
    string userName, Email, password;
    string searchName, searchPass, searchEmail;
    fstream file;

public:
    void login();
    void signUp();
    void forgot();
};

Temp obj;

void showMenu();

int main() {
    char choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // Pour éviter des problèmes avec `getline` après `cin`.

        switch (choice) {
        case '1':
            obj.login();
            break;
        case '2':
            obj.signUp();
            break;
        case '3':
            obj.forgot();
            break;
        case '4':
            cout << "Merci d'avoir utilisé notre application ! Au revoir.\n";
            return 0;
        default:
            cout << "Sélection invalide, veuillez réessayer.\n";
        }

    } while (true);

    return 0;
}

void showMenu() {
    cout << "\n--------- MENU ---------\n";
    cout << "1 - Login\n";
    cout << "2 - Sign-Up\n";
    cout << "3 - Forgot Password\n";
    cout << "4 - Exit\n";
    cout << "Entrez votre choix : ";
}

void Temp::signUp() {
    cout << "\n--- Inscription ---\n";
    cout << "Entrez votre nom d'utilisateur : ";
    getline(cin, userName);
    cout << "Entrez votre adresse email : ";
    getline(cin, Email);
    cout << "Entrez votre mot de passe : ";
    getline(cin, password);

    file.open("loginData.txt", ios::out | ios::app);
    if (!file) {
        cerr << "Erreur lors de l'ouverture du fichier !\n";
        return;
    }
    file << userName << "*" << Email << "*" << password << endl;
    file.close();

    cout << "Inscription réussie !\n";
}

void Temp::login() {
    cout << "\n--- Connexion ---\n";
    cout << "Entrez votre nom d'utilisateur : ";
    getline(cin, searchName);
    cout << "Entrez votre mot de passe : ";
    getline(cin, searchPass);

    file.open("loginData.txt", ios::in);
    if (!file) {
        cerr << "Erreur lors de l'ouverture du fichier !\n";
        return;
    }

    bool found = false;
    while (getline(file, userName, '*') && getline(file, Email, '*') && getline(file, password)) {
        if (userName == searchName && password == searchPass) {
            cout << "\nConnexion réussie !\n";
            cout << "Nom d'utilisateur : " << userName << "\n";
            cout << "Email : " << Email << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Nom d'utilisateur ou mot de passe incorrect.\n";
    }
    file.close();
}

void Temp::forgot() {
    cout << "\n--- Mot de passe oublié ---\n";
    cout << "Entrez votre nom d'utilisateur : ";
    getline(cin, searchName);
    cout << "Entrez votre adresse email : ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);
    if (!file) {
        cerr << "Erreur lors de l'ouverture du fichier !\n";
        return;
    }

    bool found = false;
    while (getline(file, userName, '*') && getline(file, Email, '*') && getline(file, password)) {
        if (userName == searchName && Email == searchEmail) {
            cout << "\nCompte trouvé !\n";
            cout << "Votre mot de passe : " << password << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Nom d'utilisateur ou email non trouvé.\n";
    }
    file.close();
}
