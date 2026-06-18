import os
import csv
from datetime import datetime

def generate_advanced_report():
    raw_file = "patient_data.txt"
    csv_file = "patient_records.csv"
    
    # ensure backend data source exists before execution
    if not os.path.exists(raw_file):
        print("\n[ERROR] 'patient_data.txt' not found!")
        print("Please run your compiled C++ application first to capture patient symptoms.\n")
        return

    # metrics trackers for database summary
    stats = {"CRITICAL": 0, "HIGH": 0, "MODERATE": 0, "LOW": 0}
    total_patients = 0
    total_score_sum = 0
    
    # check state to manage table headers correctly
    file_exists = os.path.exists(csv_file)
    
    print("\n" + "="*70)
    print("      COVID-ASSOCIATED MUCORMYCOSIS (CAM) TRIAGE DASHBOARD       ")
    print("="*70)

    processed_records = []

    # Parse the streaming inputs from local filesystem
    with open(raw_file, "r") as file:
        for line in file:
            if not line.strip():
                continue
            
            name, score_str = line.strip().split(",")
            score = int(score_str)
            total_patients += 1
            total_score_sum += score

            # stratification rules mapped directly from clinical profiles
            if score > 12:
                category = "CRITICAL"
                action = "Immediate admission. Emergency MRI/CT of Brain & PNS. Initiate immediate clinical antifungal protocol."
            elif score >= 8:
                category = "HIGH"
                action = "Urgent ENT and Ophthalmology consultation for diagnostic nasal endoscopy (KOH mount)."
            elif score >= 4:
                category = "MODERATE"
                action = "Strict glycemic control and mandatory metabolic monitoring; monitor closely for facial signs."
            else:
                category = "LOW"
                action = "Standard post-COVID observation and routine hygiene protocols."

            stats[category] += 1
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            
            processed_records.append({
                "Timestamp": timestamp,
                "Patient Name": name.upper(),
                "Risk Score": score,
                "Risk Category": category,
                "Action Protocol": action
            })

            # pipe individual validation summary straight to terminal
            print(f" ID: {total_patients:02d} | PATIENT: {name.upper():<18} | SCORE: {score:<2} | STATUS: {category}")
            print(f" RECOMMENDED PROTOCOL: {action}")
            print("-"*70)

    # persist structured records into tracking ledger
    with open(csv_file, mode="a", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=["Timestamp", "Patient Name", "Risk Score", "Risk Category", "Action Protocol"])
        if not file_exists:
            writer.writeheader()
        writer.writerows(processed_records)

    #  baseline metrics calculation
    avg_score = total_score_sum / total_patients if total_patients > 0 else 0
    print("\n" + "═"*27 + " SYSTEM METRICS " + "═"*27)
    print(f" Total Records Processed      : {total_patients}")
    print(f" Mean Clinical Symptom Burden : {avg_score:.1f} / 49 points")
    print(f" Stratification Breakdown     : CRITICAL ({stats['CRITICAL']}) | HIGH ({stats['HIGH']}) | MODERATE ({stats['MODERATE']}) | LOW ({stats['LOW']})")
    print(f" Database Sync Status         : [SUCCESS] Appended logs to '{csv_file}'")
    print("═"*70 + "\n")

if __name__ == "__main__":
    generate_advanced_report()