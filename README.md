# Labs Management System (C++)

A comprehensive system to manage information about labs in a university. The system stores data about labs, sections, timings, instructors, TAs, venues (rooms and buildings), and handles timesheet management and makeup lab requests.

## Features

### User Roles

1. **Academic Officer**
   - Add/Manage Buildings and Rooms
   - Add/Manage Instructors and TAs
   - Add/Manage Lab Sections
   - Schedule Lab Sessions (with expected timings)
   - View all data
   - Approve Makeup Lab Requests

2. **Attendant** (One per Building)
   - Fill timesheet for lab sessions (actual start/end times)
   - View sessions in assigned building

3. **Head of Department**
   - Generate complete lab schedule for entire week
   - Generate filled timesheet for all labs in a given week
   - Generate timesheet for all sessions of a particular lab (with total contact hours and leaves)

4. **Instructor**
   - Request makeup labs
   - View assigned sections
   - View makeup requests status

## System Architecture

### Data Model
- **Building**: Contains building information and assigned attendant
- **Room**: Room details within a building
- **Instructor**: Instructor information
- **TA**: Teaching Assistant information
- **Section**: Lab section with instructor, TAs, and room assignment
- **LabSession**: Individual lab session with schedule and timesheet
- **Timing**: Expected and actual start/end times
- **MakeupRequest**: Instructor requests for makeup labs

### Storage
- All data is stored in binary files using C++ file I/O
- Data files are stored in the `data/` directory
- No database management system is used
- Custom serialization/deserialization for all entities

## Building and Running

### Prerequisites
- C++ compiler with C++11 support (g++, clang++, or MSVC)
- Windows: MinGW or Visual Studio
- Linux/Mac: g++ (usually pre-installed)

### Running in VS Code (Recommended)

**Easiest Method:**
1. Open VS Code in the project folder
2. Press `` Ctrl + ` `` (backtick) to open integrated terminal
3. Compile: `g++ -std=c++11 -I./include src/*.cpp -o labs_management.exe`
4. Run: `labs_management.exe`

**Or use keyboard shortcut:**
- Press `Ctrl + Shift + B` to build
- Then run: `labs_management.exe`

See `VSCODE_GUIDE.md` for detailed VS Code instructions.

### Running from Command Line

**Step 1: Compile the Project**

Open terminal/command prompt in the project directory and run:

**Windows:**
```cmd
g++ -std=c++11 -I./include src/*.cpp -o labs_management.exe
```

**Linux/Mac:**
```bash
g++ -std=c++11 -I./include src/*.cpp -o labs_management
```

**Alternative (if the above doesn't work, compile files individually):**
```bash
# Compile all source files to object files
g++ -std=c++11 -I./include -c src/Building.cpp -o Building.o
g++ -std=c++11 -I./include -c src/Room.cpp -o Room.o
g++ -std=c++11 -I./include -c src/Instructor.cpp -o Instructor.o
g++ -std=c++11 -I./include -c src/TA.cpp -o TA.o
g++ -std=c++11 -I./include -c src/Timing.cpp -o Timing.o
g++ -std=c++11 -I./include -c src/Section.cpp -o Section.o
g++ -std=c++11 -I./include -c src/LabSession.cpp -o LabSession.o
g++ -std=c++11 -I./include -c src/MakeupRequest.cpp -o MakeupRequest.o
g++ -std=c++11 -I./include -c src/StorageManager.cpp -o StorageManager.o
g++ -std=c++11 -I./include -c src/InputUtil.cpp -o InputUtil.o
g++ -std=c++11 -I./include -c src/AcademicOfficerUI.cpp -o AcademicOfficerUI.o
g++ -std=c++11 -I./include -c src/AttendantUI.cpp -o AttendantUI.o
g++ -std=c++11 -I./include -c src/HeadOfDepartmentUI.cpp -o HeadOfDepartmentUI.o
g++ -std=c++11 -I./include -c src/InstructorUI.cpp -o InstructorUI.o
g++ -std=c++11 -I./include -c src/MainMenu.cpp -o MainMenu.o
g++ -std=c++11 -I./include -c src/main.cpp -o main.o

# Link all object files
g++ *.o -o labs_management
```

### Step 2: Run the Application

**Windows:**
```cmd
labs_management.exe
```

**Linux/Mac:**
```bash
./labs_management
```

The application will start and show the main menu. The `data/` directory will be created automatically when you first save data.

## Code Quality Analysis with CCCC

CCCC (C and C++ Code Counter) is a tool for analyzing C/C++ code metrics.

### Installing CCCC

#### Windows
1. Download CCCC from: http://cccc.sourceforge.net/
2. Extract and add to PATH

#### Linux
```bash
sudo apt-get install cccc
# or
sudo yum install cccc
```

#### macOS
```bash
brew install cccc
```

### Running CCCC

```bash
# Basic usage
cccc --outdir=cccc_report src/**/*.cpp include/**/*.h

# With HTML output
cccc --html_outdir=cccc_report_html --outdir=cccc_report src/**/*.cpp include/**/*.h

# Windows
cccc --outdir=cccc_report src\**\*.cpp include\**\*.h
```

### Understanding CCCC Output

CCCC generates several files:
- **.html** files: HTML reports with metrics
- **.txt** files: Text-based metrics reports

### Key Metrics Reported

1. **Lines of Code (LOC)**
   - Total lines
   - Comment lines
   - Code lines

2. **Function/Method Metrics**
   - Number of functions/methods
   - Average complexity
   - Maximum complexity

3. **File Metrics**
   - Files analyzed
   - Average metrics per file

4. **CK Metrics** (for object-oriented code)
   - WMC (Weighted Methods per Class)
   - DIT (Depth of Inheritance Tree)
   - NOC (Number of Children)
   - CBO (Coupling Between Objects)
   - RFC (Response For a Class)
   - LCOM (Lack of Cohesion of Methods)

## Project Structure

```
SDA_PROJ/
├── include/
│   ├── Building.h
│   ├── Room.h
│   ├── Instructor.h
│   ├── TA.h
│   ├── Timing.h
│   ├── Section.h
│   ├── LabSession.h
│   ├── MakeupRequest.h
│   ├── StorageManager.h
│   ├── InputUtil.h
│   ├── AcademicOfficerUI.h
│   ├── AttendantUI.h
│   ├── HeadOfDepartmentUI.h
│   ├── InstructorUI.h
│   └── MainMenu.h
├── src/
│   ├── Building.cpp
│   ├── Room.cpp
│   ├── Instructor.cpp
│   ├── TA.cpp
│   ├── Timing.cpp
│   ├── Section.cpp
│   ├── LabSession.cpp
│   ├── MakeupRequest.cpp
│   ├── StorageManager.cpp
│   ├── InputUtil.cpp
│   ├── AcademicOfficerUI.cpp
│   ├── AttendantUI.cpp
│   ├── HeadOfDepartmentUI.cpp
│   ├── InstructorUI.cpp
│   ├── MainMenu.cpp
│   └── main.cpp
├── data/              (created at runtime)
│   ├── buildings.dat
│   ├── rooms.dat
│   ├── instructors.dat
│   ├── tas.dat
│   ├── sections.dat
│   ├── sessions.dat
│   └── makeup_requests.dat
└── README.md
```

## Usage Example

1. **Start the application** (after compilation)
   ```bash
   ./labs_management    # Linux/Mac
   # or
   labs_management.exe  # Windows
   ```

2. **As Academic Officer:**
   - Add a building (e.g., "B1", "Engineering Building", "ATT1")
   - Add rooms to the building
   - Add instructors and TAs
   - Create lab sections
   - Schedule lab sessions

3. **As Attendant:**
   - Enter attendant ID
   - Fill timesheet for lab sessions in your building

4. **As Instructor:**
   - Enter instructor ID
   - Request makeup labs if needed

5. **As Head of Department:**
   - Generate various reports

## Notes

- All data persists in binary files
- The system automatically creates the `data/` directory on first run
- Makeup labs are marked and included in contact hours calculations
- Timesheets track both expected (schedule) and actual (timesheet) timings
- Contact hours are calculated from actual start/end times
- Date format: YYYY-MM-DD
- Time format: HH:MM

## License

This project is developed for academic purposes.

