@echo off
echo Running CCCC on your project...
echo.

REM Run CCCC with explicit file list (Windows doesn't expand wildcards)
cccc --outdir=cccc_report ^
    src\Building.cpp ^
    src\Room.cpp ^
    src\Instructor.cpp ^
    src\TA.cpp ^
    src\Timing.cpp ^
    src\Section.cpp ^
    src\LabSession.cpp ^
    src\MakeupRequest.cpp ^
    src\StorageManager.cpp ^
    src\InputUtil.cpp ^
    src\AcademicOfficerUI.cpp ^
    src\AttendantUI.cpp ^
    src\HeadOfDepartmentUI.cpp ^
    src\InstructorUI.cpp ^
    src\MainMenu.cpp ^
    src\main.cpp ^
    include\Building.h ^
    include\Room.h ^
    include\Instructor.h ^
    include\TA.h ^
    include\Timing.h ^
    include\Section.h ^
    include\LabSession.h ^
    include\MakeupRequest.h ^
    include\StorageManager.h ^
    include\InputUtil.h ^
    include\AcademicOfficerUI.h ^
    include\AttendantUI.h ^
    include\HeadOfDepartmentUI.h ^
    include\InstructorUI.h ^
    include\MainMenu.h

echo.
echo ========================================
echo CCCC Analysis Complete!
echo ========================================
echo.

if exist "cccc_report" (
    echo Report generated in: cccc_report folder
    echo.
    echo Files created:
    dir cccc_report /b
    echo.
    echo Opening report folder...
    start cccc_report
) else (
    echo ERROR: Report folder not created. Check errors above.
)

echo.
pause

