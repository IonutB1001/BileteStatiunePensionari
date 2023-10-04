#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>


struct BILET {
    int id;
    std::string stat;
    char nume[24];
    std::string luna;
};

std::list<BILET> bilete;

struct compare {
    bool operator()(const BILET& a, const BILET& b) {
        return std::string(a.nume) < std::string(b.nume);
    }
};



//==================START  method to check ID is unique in list START======================================================
bool idExists(int id) {
    for (const auto& bilet : bilete) {
        if (bilet.id == id) {
            return true;
        }
    }
    return false;
}
//==================END method to check ID is unique in listEND========================================================

//==================START          START======================================================
bool statExists(std::string stat) {
    for (const auto& bilet : bilete) {
        if (bilet.stat == stat) {
            return true;
        }
    }
    return false;
}
//==================END                     END========================================================

//==================START          START======================================================
bool numeExists(std::string nume) {
    for (const auto& bilet : bilete) {
        if (std::string(bilet.nume) == nume) {
            return true;
        }
    }
    return false;
}
//==================END                     END========================================================

//==================START method to populate list of bilete START======================================================
void populeazaListaBilete() {
    for (int i = 0; i < 70; i++) {
        BILET bilet;

        // Ensure ID is unique and not empty
        do {
            bilet.id = rand() % 1000 + 1; // Generate a random ID between 1 and 1000
        } while (idExists(bilet.id));

        // Populate 'stat' with random resort names
        std::string stati[] = { "Baile Felix", "Hotel Alpin", "Techirghiol", "Slanic Moldova", "Zarnesti", "Gura Portitei", "Sulina", "Chilia", "Lacu Sarat" };
        bilet.stat = stati[rand() % 9];

        // Populate 'nume' with random names
        std::string nume[] = { "Ion Barbu", "Vasile Metin", "Maria Tanase", "Elena Lasconi", "Mihai Marcu", "Gigel Malai-Mare", "Radu Pascali", "Alina Verstoy", "Adriana Ispas" };
        strncpy_s(bilet.nume, sizeof(bilet.nume), nume[rand() % 9].c_str(), _TRUNCATE);
        bilet.nume[sizeof(bilet.nume) - 1] = 0;

        // Populate 'luna' with random months
        std::string luni[] = { "Ianuarie", "Februarie", "Martie", "Aprilie", "Mai", "Iunie",
                               "Iulie", "August", "Septembrie", "Octombrie", "Noiembrie", "Decembrie" };
        bilet.luna = luni[rand() % 12];

        // Add the ticket to the list
        bilete.push_back(bilet);
    }

    std::cout << "Au fost adaugate " << bilete.size() << " persoane." << std::endl;
}

//==================END  method to populate list of bilete END========================================================

//==================START method that counts number of people going to a certain resort input          START==============================================================

int numaraPensionariStatiune(std::string stat) {
    // Validate the resort name
    while (!statExists(stat)) {
        std::cout << "Statiunea nu este in baza de date, va rugam incercati alta statiune" << std::endl;
        std::cout << "Introduceți numele statiunii: ";
        std::getline(std::cin, stat);
    }

    // Count how many people go to the given resort
    int count = 0;
    for (const auto& bilet : bilete) {
        if (bilet.stat == stat) {
            count++;
        }
    }

    std::cout << "La statiunea " << stat << " pleaca " << count << " persoane." << std::endl;
    return count;
}
//==================END  method that counts number of people going to a certain resort input  END========================================================

//==================START  Method that lists all the people that go to input resort ordered alphabetically START==============================================================
void listeazaPensionariAlfabeticDupaStat(std::string stat) {
    // Validate the resort name
    while (!statExists(stat)) {
        std::cout << "Statiunea nu este in baza de date, va rugam incercati alta statiune" << std::endl;
        std::cout << "Introduceți numele stațiunii: ";
        std::getline(std::cin, stat);
    }

    // Store all the people that go to the given resort in a list
    std::list<BILET> pensionari;
    for (const auto& bilet : bilete) {
        if (bilet.stat == stat) {
            pensionari.push_back(bilet);
        }
    }

    // Sort the list alphabetically
    pensionari.sort(compare());

    // Output the list line by line
    for (const auto& bilet : pensionari) {
        std::cout << "Persoana " << bilet.nume << " cu ID " << bilet.id << " merge la statiunea " << stat << " in luna " << bilet.luna << std::endl;
    }

    // Print the number of people
    std::cout << "La statiunea " << stat << " pleaca " << pensionari.size() << " persoane.\n";
}
//==================END Method that lists all the people that go to input resort ordered alphabetically END========================================================


//==================START Method that lists ticket information based on input name START==============================================================
void listeazaInformatiiBilet(std::string nume) {
    // Validate the name
    while (!numeExists(nume)) {
        std::cout << "Nu avem in baza de date persoana cu numele " << nume << std::endl;
        std::cout << "Introduceți numele persoanei: ";
        std::getline(std::cin, nume);
    }

    // List all tickets for the given person
    for (const auto& bilet : bilete) {
        if (std::string(bilet.nume) == nume) {
            std::cout << "Persoana " << bilet.nume << " are bilet cu ID " << bilet.id << ", merge la statiunea " << bilet.stat << " in luna " << bilet.luna << std::endl;
        }
    }
}
//==================END Method that lists ticket information based on input name END========================================================


//==================START   main function        START==============================================================
int main() {
    //declaring variables
    int option;
    std::string stat;
    std::string nume;
    do {
        std::cout << "1. Populeaza lista de bilete " << std::endl;
        std::cout << "2. Numara pensionari statiune, introduceti statiunea: " << std::endl;
        std::cout << "3. Listeaza pensionari alfabetic dupa statiune " <<std::endl;
        std::cout << "4. Listeaza informatii bilet dupa nume persoana " << std::endl;
        std::cout << "5. Iesire program: " << std::endl;
        std::cout << "Alegeti o optiune: ";
        std::cin >> option;

        switch (option) {
        case 1:
            populeazaListaBilete();
            break;
        case 2:
            std::cout << "Introduceti numele statiunii: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover
            std::getline(std::cin, stat);
            numaraPensionariStatiune(stat);
            break;
        case 3:
            std::cout << "Introduceti numele statiunii: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover
            std::getline(std::cin, stat);
            listeazaPensionariAlfabeticDupaStat(stat);
            break;
        case 4:
            std::cout << "Introduceti numele persoanei: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover
            std::getline(std::cin, nume);
            listeazaInformatiiBilet(nume);
            break;
        case 5:
            std::cout << "Iesire program" << std::endl;
            break;
        default:
            std::cout << "Optiune invalida. Revenire la meniul principal." << std::endl;
        }
    } while (option != 5);

    return 0;
}
//==================END main function END========================================================