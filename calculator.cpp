#include <iostream>
#include <fstream>
#include <string>

void recordPatient() {
    std::string name;
    int score = 0;
    char choice;

    std::cout << "\nEnter Patient Name: ";
    std::getline(std::cin, name); // Reads the full line perfectly now

    std::cout << "Answer with 'y' (Yes) or 'n' (No):\n";

    std::cout << "- Uncontrolled diabetes/DKA? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 3;
    std::cout << "- High-dose systemic corticosteroids? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 3;
    std::cout << "- History of severe COVID-19 (< 6 weeks)? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 2;
    std::cout << "- Persistent headache/prolonged fever? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 1;
    std::cout << "- Unilateral facial pain/swelling? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 4;
    std::cout << "- Toothache or loosening of jaw bone? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 4;
    std::cout << "- Bloody/brown nasal discharge? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 4;
    std::cout << "- Visible black necrotic lesions? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 6;
    std::cout << "- Eye involvement (ptosis/blurred vision)? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 5;
    std::cout << "- Long-term oxygen therapy with unsterile humidifier water? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 2;
    std::cout << "- Laboratory confirmation of high serum ferritin/free iron levels? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 2;
    std::cout << "- Recent high-exposure to construction dust, soil, or decaying matter? "; std::cin >> choice; if (choice == 'y' || choice == 'Y') score += 1;

    // Open file in APPEND mode (std::ios::app)
    std::ofstream outFile("patient_data.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << name << "," << score << "\n";
        outFile.close();
        std::cout << "[DATA SAVED] " << name << " processed successfully.\n";
    }
}

int main() {
    char continueLoop;
    std::cout << "=== COVID & Black Fungus Triage System (C++ Engine) ===\n";
    
    // Clear the intermediate data file once at startup to reset the current pipeline run
    std::ofstream clearFile("patient_data.txt");
    clearFile.close();

    do {
        recordPatient();
        std::cout << "\nDo you want to add another patient? (y/n): ";
        std::cin >> continueLoop;
        std::cin.ignore(); // Clean out the newline character from the buffer here instead!
    } while (continueLoop == 'y' || continueLoop == 'Y');

    std::cout << "\n[SUCCESS] All data sent to data pipeline. Run reporter.py now.\n";
    return 0;
}