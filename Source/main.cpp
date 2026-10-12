#include <iostream>
#include "PropertySystem.h"
#include "Input.h"
using namespace std;

static void showMenu() {
    cout << "\n=====================================\n";
    cout << "   PROPERTY MAINTENANCE MANAGEMENT\n";
    cout << "=====================================\n";
    cout << "1. Add Record\n";
    cout << "2. Display Records\n";
    cout << "3. Search Record\n";
    cout << "4. Update Record\n";
    cout << "5. Delete Record\n";
    cout << "6. Main Transaction (Maintenance Requests)\n";
    cout << "7. Report\n";
    cout << "8. Save/Load\n";
    cout << "9. Exit\n";
}

int main() {
    PropertySystem app;
    app.loadData();            // load existing records at start

    int choice = 0;
    do {
        showMenu();
        choice = readInt("Enter your choice (1-9): ");

        switch (choice) {
            case 1: app.addRecord(); break;
            case 2: app.displayRecords(); break;
            case 3: app.searchRecord(); break;
            case 4: app.updateRecord(); break;
            case 5: app.deleteRecord(); break;
            case 6: app.mainTransaction(); break;
            case 7: app.report(); break;
            case 8: {
                cout << "1. Save data\n2. Load data\n";
                int sub = readInt("Choose: ");
                if (sub == 1) app.saveData();
                else if (sub == 2) app.loadData();
                else cout << "Invalid choice.\n";
                break;
            }
            case 9:
                app.saveData();    // save updated records before exit
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter 1 to 9.\n";
        }
    } while (choice != 9);

    return 0;
}