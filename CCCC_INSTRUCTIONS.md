# Running CCCC on Labs Management System

## About CCCC

CCCC (C and C++ Code Counter) is a software metrics tool designed specifically for C and C++ code. It provides comprehensive code analysis including CK metrics for object-oriented code.

## Installation

### Windows
1. Download CCCC from: http://cccc.sourceforge.net/
2. Extract the ZIP file
3. Add the `cccc.exe` directory to your system PATH
4. Or use the full path to `cccc.exe`

### Linux
```bash
sudo apt-get install cccc
# or
sudo yum install cccc
```

### macOS
```bash
brew install cccc
```

## Running CCCC

### Basic Command
```bash
cccc --outdir=cccc_report src/*.cpp include/*.h
```

### With HTML Output (Recommended)
```bash
cccc --html_outdir=cccc_report_html --outdir=cccc_report src/*.cpp include/*.h
```

### Windows Command
```cmd
cccc --outdir=cccc_report src\*.cpp include\*.h
```

### Recursive Directory (if supported)
```bash
cccc --outdir=cccc_report src/**/*.cpp include/**/*.h
```

## Understanding CCCC Output

CCCC generates several files in the output directory:
- **.html** files: HTML reports with metrics (open in browser)
- **.txt** files: Text-based metrics reports
- **index.html**: Main report page

### Viewing the Report

1. Navigate to the output directory:
   ```bash
   cd cccc_report
   ```

2. Open `index.html` in a web browser:
   ```bash
   # Linux/Mac
   open index.html
   # or
   xdg-open index.html
   
   # Windows
   start index.html
   ```

## Key Metrics Reported

### 1. Lines of Code (LOC)
- **Total Lines**: All lines in the file
- **Comment Lines**: Lines containing comments
- **Code Lines**: Executable code lines
- **Blank Lines**: Empty lines

### 2. Function/Method Metrics
- **Number of Functions**: Total function count
- **Average Complexity**: Average cyclomatic complexity
- **Maximum Complexity**: Most complex function
- **Lines per Function**: Average lines per function

### 3. File Metrics
- **Files Analyzed**: Total number of files
- **Total Lines**: Sum of all lines
- **Average Metrics**: Per-file averages

### 4. CK Metrics (Chidamber and Kemerer)
For object-oriented code, CCCC reports:

- **WMC (Weighted Methods per Class)**: Sum of complexities of all methods in a class
  - Lower is better
  - Indicates class complexity

- **DIT (Depth of Inheritance Tree)**: Maximum inheritance depth
  - Higher may indicate overuse of inheritance
  - Lower may indicate lack of code reuse

- **NOC (Number of Children)**: Number of direct subclasses
  - Indicates class reusability

- **CBO (Coupling Between Objects)**: Number of classes coupled to
  - Lower is better
  - Indicates class independence

- **RFC (Response For a Class)**: Number of methods that can be executed in response to a message
  - Lower is better
  - Indicates class complexity

- **LCOM (Lack of Cohesion of Methods)**: Measures cohesion
  - Lower is better (0 = perfect cohesion)
  - Indicates how well methods work together

## Expected Metrics for This Project

Based on the code structure:

- **Classes**: ~15 classes
- **Methods**: ~80-100 methods
- **Average Complexity**: Low to Medium (most methods are simple getters/setters)
- **Coupling**: Low (well-separated concerns)
- **Cohesion**: High (focused classes with single responsibilities)

### Typical Values:
- **WMC**: 5-15 per class (getters/setters are simple)
- **DIT**: 0 (no inheritance used)
- **NOC**: 0 (no inheritance)
- **CBO**: 2-5 (classes depend on StorageManager and model classes)
- **RFC**: 5-20 (methods per class)
- **LCOM**: 0-2 (high cohesion)

## Generating Report

1. **Build the project first:**
   ```bash
   make
   # or
   build.bat
   ```

2. **Run CCCC:**
   ```bash
   cccc --html_outdir=cccc_report_html --outdir=cccc_report src/*.cpp include/*.h
   ```

3. **View the report:**
   - Open `cccc_report_html/index.html` in a web browser
   - Or view the text files in `cccc_report/`

## Interpreting Results

### Good Metrics:
- Low cyclomatic complexity (< 10)
- Low coupling (CBO < 5)
- High cohesion (LCOM < 2)
- Reasonable WMC (< 20)

### Areas for Improvement:
- High complexity functions (> 20)
- High coupling (CBO > 10)
- Low cohesion (LCOM > 5)
- Very large classes (WMC > 30)

## Notes

- CCCC works best with C++ code
- Some metrics may not apply if inheritance is not used
- The tool helps identify:
  - Complex classes that need refactoring
  - High coupling between modules
  - Code maintainability issues
  - Potential bugs (high complexity)

## Troubleshooting

### CCCC not found
- Ensure CCCC is installed and in PATH
- Use full path to cccc executable

### No output generated
- Check file paths are correct
- Ensure source files exist
- Check write permissions for output directory

### Incomplete metrics
- Some metrics require complete compilation
- Ensure all dependencies are available

