#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void recordPatient() {
    string name;
    int score = 0;
    char choice;

    cout << "\nEnter Patient Name: ";
    getline(cin, name); // catches full string including spaces properly

    cout << "Answer with 'y' (Yes) or 'n' (No):\n";

    cout << "- Uncontrolled diabetes/DKA? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 3;
    cout << "- High-dose systemic corticosteroids? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 3;
    cout << "- History of severe COVID-19 (< 6 weeks)? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 2;
    cout << "- Persistent headache/prolonged fever? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 1;
    cout << "- Unilateral facial pain/swelling? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 4;
    cout << "- Toothache or loosening of jaw bone? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 4;
    cout << "- Bloody/brown nasal discharge? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 4;
    cout << "- Visible black necrotic lesions? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 6;
    cout << "- Eye involvement (ptosis/blurred vision)? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 5;
    cout << "- Long-term oxygen therapy with unsterile humidifier water? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 2;
    cout << "- Laboratory confirmation of high serum ferritin/free iron levels? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 2;
    cout << "- Recent high-exposure to construction dust, soil, or decaying matter? "; cin >> choice; if (choice == 'y' || choice == 'Y') score += 1;
    
    cin.ignore(); // flush character trailing markers before reading next patient string

    // persistent storage in append mode
    ofstream outFile("patient_data.txt", ios::app);
    if (outFile.is_open()) {
        outFile << name << "," << score << "\n";
        outFile.close();
        cout << "[DATA SAVED] " << name << " processed successfully.\n";
    }
}

int main() {
    char continueLoop;
    cout << "=== COVID & Black Fungus Triage System (C++ Engine) ===\n";
    
    // for wiping local logging file at launch to fresh start session pipeline
    ofstream clearFile("patient_data.txt");
    clearFile.close();

    do {
        recordPatient();
        cout << "\nDo you want to add another patient? (y/n): ";
        cin >> continueLoop;
        cin.ignore(); // to flush remaining trailing newline characters from input stream
    } while (continueLoop == 'y' || continueLoop == 'Y');

    cout << "\n[SUCCESS] All data sent to data pipeline. Run reporter.py now.\n";
    return 0;
}