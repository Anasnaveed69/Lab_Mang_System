# Quick Start Guide - Labs Management System

## How to Run the Project

### Step 1: Compile

Open terminal/command prompt in the project root directory (`D:\SDA_PROJ`).

**Windows (Command Prompt or PowerShell):**
```cmd
g++ -std=c++11 -I./include src/*.cpp -o labs_management.exe
```

**Linux/Mac:**
```bash
g++ -std=c++11 -I./include src/*.cpp -o labs_management
```

**If compilation fails**, try compiling files individually (see README.md for full list).

### Step 2: Run

**Windows:**
```cmd
labs_management.exe
```

**Linux/Mac:**
```bash
./labs_management
```

### Step 3: Use the System

1. **Main Menu** will appear with options:
   - 1. Academic Officer
   - 2. Attendant
   - 3. Head of Department
   - 4. Instructor
   - 0. Exit

2. **First Time Setup (Academic Officer):**
   - Select option 1
   - Add a Building (e.g., ID: B1, Name: Engineering Building, Attendant: ATT1)
   - Add a Room (e.g., ID: R1, Number: 101, Building: B1, Capacity: 30)
   - Add an Instructor (e.g., ID: INST1, Name: Dr. John Smith)
   - Add a TA (e.g., ID: TA1, Name: Jane Doe)
   - Add a Lab Section (e.g., ID: SEC1, Lab: Data Structures, Instructor: INST1, Room: R1)
   - Schedule a Lab Session (e.g., ID: SESS1, Section: SEC1, Date: 2024-10-15, Time: 14:00-16:00)

3. **Fill Timesheet (Attendant):**
   - Select option 2
   - Enter Attendant ID: ATT1
   - Select option 1 to fill timesheet
   - Enter Session ID: SESS1
   - Enter actual start and end times

4. **Generate Reports (Head of Department):**
   - Select option 3
   - Choose report type (weekly schedule, weekly timesheet, or lab section timesheet)

5. **Request Makeup Lab (Instructor):**
   - Select option 4
   - Enter Instructor ID: INST1
   - Select option 1 to request makeup lab

## Troubleshooting

**Compilation Error: "g++ not found"**
- Windows: Install MinGW or use Visual Studio Developer Command Prompt
- Linux: Install g++: `sudo apt-get install g++` (Ubuntu/Debian) or `sudo yum install gcc-c++` (CentOS/RHEL)
- Mac: Install Xcode Command Line Tools: `xcode-select --install`

**Runtime Error: "Permission denied" (Linux/Mac)**
- Make executable: `chmod +x labs_management`

**Data not saving**
- Check that you have write permissions in the project directory
- The `data/` folder will be created automatically

## File Structure After Compilation

```
SDA_PROJ/
├── include/          (header files)
├── src/             (source files)
├── data/            (created automatically - binary data files)
├── labs_management  (executable - Linux/Mac)
├── labs_management.exe  (executable - Windows)
└── *.o              (object files - can be deleted)
```

## Notes

- Date format: YYYY-MM-DD (e.g., 2024-10-15)
- Time format: HH:MM (e.g., 14:00)
- All data is stored in binary files in the `data/` directory
- No database required - everything uses binary file storage

