# Exam Seating & Attendance System

Youtube Link: https://youtu.be/1gW1Ojz_Arg

## Project Overview
The **Exam Seating & Attendance System** is an end-to-end solution designed to streamline the logistical planning of university examinations. Built with **Python**, **Streamlit**, and **Docker**, this application automates the complex task of allocating students to exam rooms and generating print-ready attendance sheets.

The system is divided into two core modules:
1.  **Seating Optimization:** Allocates students to rooms based on capacity and schedule, ensuring no clashes.
2.  **Attendance Generation:** Creates professional PDF attendance sheets with student photos for every exam room.

---

## Key Features

### Module 1: Seating Arrangement Optimization
* **Intelligent Allocation:** Allocates students to rooms based on "Effective Capacity" (Total Capacity - Buffer), prioritizing larger cohorts for larger rooms to minimize fragmentation.
* **Clash Detection:** Automatically identifies if a student is scheduled for two exams in the same session. If a clash is found, it is logged, and the process halts to prevent errors.
* **Flexible Configuration:** Allows users to define **Buffer** (seats to leave empty) and **Filling Mode** (Sparse/50% or Dense/100%).
* **Day-wise Organization:** Generates a structured folder system for every exam day and session.

### Module 2: Attendance Sheet Generation
* **Automated PDFs:** Generates A4-sized PDF attendance sheets for every allocated room.
* **Visual Identification:** Includes a grid layout with student photos, names (bolded), roll numbers, and signature lines.
* **Robust Error Handling:** Skips missing photos or corrupt records without crashing, logging specific errors to `error.txt`.
* **Fallback Mechanism:** Automatically uses a placeholder image (`nopic.jpg`) if a student's photo is missing.
* **Standardized Naming:** Output files follow a strict convention for easy sorting: `YYYY_MM_DD_<SESSION>_<ROOM>_<SUBCODE>.pdf`.

---

## Tech Stack
* **Language:** Python 3.9+
* **Interface:** [Streamlit](https://streamlit.io/)
* **Data Processing:** Pandas, OpenPyXL
* **PDF Generation:** FPDF
* **Deployment:** Docker

---

## Project Structure

```text
exam_system/
├── app.py                   # Main Streamlit Application entry point
├── Dockerfile               # Docker configuration for containerization
├── requirements.txt         # Python dependencies
├── error.txt                # Auto-generated log file for errors
├── modules/
│   ├── __init__.py
│   ├── seating.py           # Logic for allocation, clashes, and Excel processing
│   └── attendance.py        # Logic for PDF generation and layout
|   |__ utils.py
├── photos/                  # [INPUT] Folder containing student images (ROLL.jpg)
├── input_data/              # [INPUT] Temporary storage for uploaded Excel files
└── output/                  # [OUTPUT] Generated files are stored here before zipping