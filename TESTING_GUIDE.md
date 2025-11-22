# Complete Testing Guide - Labs Management System

This guide provides step-by-step instructions to test all functionality with sample inputs.

## Prerequisites

1. Compile the project:
   ```cmd
   g++ -std=c++11 -I./include src/*.cpp -o labs_management.exe
   ```

2. Run the application:
   ```cmd
   labs_management.exe
   ```

---

## Test Scenario: Complete Workflow

### Phase 1: Setup (Academic Officer)

**Login:** Select `1` (Academic Officer)

#### Step 1: Add Building
```
Enter choice: 1
Enter Building ID: B1
Enter Building Name: Engineering Building
Enter Attendant ID: ATT1
```
**Expected:** "Building added successfully!"

#### Step 2: Add Another Building
```
Enter choice: 1
Enter Building ID: B2
Enter Building Name: Science Building
Enter Attendant ID: ATT2
```

#### Step 3: Add Rooms
```
Enter choice: 2
Enter Room ID: R1
Enter Room Number: 101
Enter Building ID: B1
Enter Capacity: 30

Enter choice: 2
Enter Room ID: R2
Enter Room Number: 102
Enter Building ID: B1
Enter Capacity: 25

Enter choice: 2
Enter Room ID: R3
Enter Room Number: 201
Enter Building ID: B2
Enter Capacity: 40
```

#### Step 4: Add Instructors
```
Enter choice: 3
Enter Instructor ID: INST1
Enter Name: Dr. John Smith
Enter Email: john.smith@university.edu
Enter Department: Computer Science

Enter choice: 3
Enter Instructor ID: INST2
Enter Name: Dr. Sarah Johnson
Enter Email: sarah.johnson@university.edu
Enter Department: Electrical Engineering
```

#### Step 5: Add TAs
```
Enter choice: 4
Enter TA ID: TA1
Enter Name: Jane Doe
Enter Email: jane.doe@university.edu
Enter Student ID: STU001

Enter choice: 4
Enter TA ID: TA2
Enter Name: Bob Wilson
Enter Email: bob.wilson@university.edu
Enter Student ID: STU002

Enter choice: 4
Enter TA ID: TA3
Enter Name: Alice Brown
Enter Email: alice.brown@university.edu
Enter Student ID: STU003
```

#### Step 6: Add Lab Sections
```
Enter choice: 5
Enter Section ID: SEC1
Enter Lab Name: Data Structures Lab
Enter Course Code: CS201
Enter Instructor ID: INST1
Enter Room ID: R1
Enter Semester: Fall 2024
Enter TA ID (or 'done' to finish): TA1
Enter TA ID (or 'done' to finish): TA2
Enter TA ID (or 'done' to finish): done

Enter choice: 5
Enter Section ID: SEC2
Enter Lab Name: Algorithms Lab
Enter Course Code: CS301
Enter Instructor ID: INST1
Enter Room ID: R2
Enter Semester: Fall 2024
Enter TA ID (or 'done' to finish): TA3
Enter TA ID (or 'done' to finish): done

Enter choice: 5
Enter Section ID: SEC3
Enter Lab Name: Circuit Analysis Lab
Enter Course Code: EE201
Enter Instructor ID: INST2
Enter Room ID: R3
Enter Semester: Fall 2024
Enter TA ID (or 'done' to finish): TA1
Enter TA ID (or 'done' to finish): done
```

#### Step 7: Schedule Lab Sessions (Week 1)
```
Enter choice: 6
Enter Session ID: SESS1
Enter Section ID: SEC1
Enter Date (YYYY-MM-DD): 2024-10-14
Select Day of Week
Enter choice (1-7): 1
Enter Expected Start Time (HH:MM): 14:00
Enter Expected End Time (HH:MM): 16:00

Enter choice: 6
Enter Session ID: SESS2
Enter Section ID: SEC1
Enter Date (YYYY-MM-DD): 2024-10-16
Select Day of Week
Enter choice (1-7): 3
Enter Expected Start Time (HH:MM): 14:00
Enter Expected End Time (HH:MM): 16:00

Enter choice: 6
Enter Session ID: SESS3
Enter Section ID: SEC2
Enter Date (YYYY-MM-DD): 2024-10-15
Select Day of Week
Enter choice (1-7): 2
Enter Expected Start Time (HH:MM): 10:00
Enter Expected End Time (HH:MM): 12:00

Enter choice: 6
Enter Session ID: SESS4
Enter Section ID: SEC3
Enter Date (YYYY-MM-DD): 2024-10-14
Select Day of Week
Enter choice (1-7): 1
Enter Expected Start Time (HH:MM): 09:00
Enter Expected End Time (HH:MM): 11:00
```

#### Step 8: Schedule More Sessions (Week 2)
```
Enter choice: 6
Enter Session ID: SESS5
Enter Section ID: SEC1
Enter Date (YYYY-MM-DD): 2024-10-21
Select Day of Week
Enter choice (1-7): 1
Enter Expected Start Time (HH:MM): 14:00
Enter Expected End Time (HH:MM): 16:00

Enter choice: 6
Enter Session ID: SESS6
Enter Section ID: SEC1
Enter Date (YYYY-MM-DD): 2024-10-23
Select Day of Week
Enter choice (1-7): 3
Enter Expected Start Time (HH:MM): 14:00
Enter Expected End Time (HH:MM): 16:00
```

**Exit Academic Officer:** Enter `0`

---

### Phase 2: Fill Timesheets (Attendant)

**Login:** Select `2` (Attendant)
```
Enter Attendant ID: ATT1
```

#### Fill Timesheet for Session 1
```
Enter choice: 1
Enter Session ID: SESS1
Enter Actual Start Time (HH:MM): 14:05
Enter Actual End Time (HH:MM): 16:10
```
**Expected:** "Timesheet filled successfully!"

#### Fill Timesheet for Session 2
```
Enter choice: 1
Enter Session ID: SESS2
Enter Actual Start Time (HH:MM): 14:00
Enter Actual End Time (HH:MM): 16:05
```

#### Fill Timesheet for Session 4
```
Enter choice: 1
Enter Session ID: SESS4
Enter Actual Start Time (HH:MM): 09:10
Enter Actual End Time (HH:MM): 11:00
```

#### View Sessions in Building
```
Enter choice: 2
```
**Expected:** Should show all sessions in Engineering Building (B1)

**Exit Attendant:** Enter `0`

---

### Phase 3: Request Makeup Lab (Instructor)

**Login:** Select `4` (Instructor)
```
Enter Instructor ID: INST1
```

#### Request Makeup Lab
```
Enter choice: 1
Enter Section ID: SEC1
Enter Date of Missed Lab (YYYY-MM-DD): 2024-10-23
Enter Reason: Holiday
```
**Expected:** "Makeup lab request submitted successfully!"  
**Note the Request ID** (e.g., REQ_1234567890)

#### View My Sections
```
Enter choice: 2
```
**Expected:** Should show SEC1 and SEC2

#### View My Makeup Requests
```
Enter choice: 3
```
**Expected:** Should show the request you just created

**Exit Instructor:** Enter `0`

---

### Phase 4: Approve Makeup Request (Academic Officer)

**Login:** Select `1` (Academic Officer)

#### View Makeup Requests
```
Enter choice: 12
```
**Expected:** Should show the makeup request

#### Approve Makeup Request
```
Enter choice: 13
Enter Request ID: REQ_1234567890
Enter Makeup Date (YYYY-MM-DD): 2024-10-25
```
**Expected:** "Makeup request approved and session created!"  
**Note the Makeup Session ID** (e.g., MAKEUP_REQ_1234567890)

**Exit Academic Officer:** Enter `0`

---

### Phase 5: Fill Makeup Timesheet (Attendant)

**Login:** Select `2` (Attendant)
```
Enter Attendant ID: ATT1
```

#### Fill Timesheet for Makeup Session
```
Enter choice: 1
Enter Session ID: MAKEUP_REQ_1234567890
Enter Actual Start Time (HH:MM): 14:00
Enter Actual End Time (HH:MM): 16:00
```

**Exit Attendant:** Enter `0`

---

### Phase 6: Generate Reports (Head of Department)

**Login:** Select `3` (Head of Department)

#### Report 1: Complete Lab Schedule for Week
```
Enter choice: 1
Enter Week Start Date (YYYY-MM-DD): 2024-10-14
```
**Expected Output:**
- Should show SESS1, SESS2, SESS3, SESS4
- All sessions sorted by date
- Shows expected timings
- Shows instructor names and room numbers

#### Report 2: Filled Timesheet for Week
```
Enter choice: 2
Enter Week Start Date (YYYY-MM-DD): 2024-10-14
```
**Expected Output:**
- Should show SESS1, SESS2, SESS4 (only filled ones)
- Shows expected vs actual times
- Shows contact hours for each
- Sorted by date

#### Report 3: Lab Section Timesheet (All Sessions)
```
Enter choice: 3
Enter Section ID: SEC1
```
**Expected Output:**
- Should show SESS1, SESS2, SESS5, SESS6, and makeup session
- Shows all sessions with dates
- Shows expected and actual times
- **Total Sessions:** 5 (including makeup)
- **Filled Sessions:** 2 (SESS1, SESS2)
- **Leaves:** 3 (SESS5, SESS6 not filled, makeup not filled yet)
- **Makeup Sessions:** 1
- **Total Contact Hours:** Sum of filled sessions

**After filling makeup session, run again:**
```
Enter choice: 3
Enter Section ID: SEC1
```
**Expected Output:**
- **Filled Sessions:** 3 (now includes makeup)
- **Leaves:** 2 (reduced!)
- **Total Contact Hours:** Updated (includes makeup hours)

**Exit Head of Department:** Enter `0`

---

## Test Cases for Edge Cases

### Test Case 1: Week Spanning Month Boundary
```
Academic Officer → Schedule Lab Session
Enter Session ID: SESS_MONTH
Enter Section ID: SEC1
Enter Date (YYYY-MM-DD): 2024-01-28
Select Day of Week: 1
Enter Expected Start Time: 14:00
Enter Expected End Time: 16:00

Head of Department → Generate Weekly Schedule
Enter Week Start Date: 2024-01-28
```
**Expected:** Should show sessions from Jan 28 to Feb 3

### Test Case 2: Empty Reports
```
Head of Department → Generate Weekly Schedule
Enter Week Start Date: 2025-01-01
```
**Expected:** Should show "No sessions" or empty table

### Test Case 3: Invalid Time Entry
```
Attendant → Fill Timesheet
Enter Session ID: SESS1
Enter Actual Start Time: 16:00
Enter Actual End Time: 14:00
```
**Expected:** "Error: End time must be after start time!"

### Test Case 4: Attendant Access Control
```
Attendant (ATT1) → Fill Timesheet
Enter Session ID: SESS4
```
**Expected:** "You don't have access to this building!"  
(Because SESS4 is in B2, but ATT1 is for B1)

### Test Case 5: Section with No Sessions
```
Head of Department → Generate Lab Section Timesheet
Enter Section ID: SEC2
```
**Expected:** Should show only SESS3 (if that's the only session for SEC2)

---

## Expected Results Summary

### Contact Hours Calculation
- **SESS1:** 14:05 to 16:10 = 2.08 hours (125 minutes / 60)
- **SESS2:** 14:00 to 16:05 = 2.08 hours (125 minutes / 60)
- **SESS4:** 09:10 to 11:00 = 1.83 hours (110 minutes / 60)
- **Makeup:** 14:00 to 16:00 = 2.00 hours

### Leaves Calculation
For SEC1 with 5 sessions:
- If 2 filled: Leaves = 5 - 2 = 3
- If 3 filled (with makeup): Leaves = 5 - 3 = 2

### Makeup Session Verification
- Makeup session should appear in all reports
- Should be marked as "Yes" in Makeup column
- Should be included in contact hours
- Should reduce leaves count when filled

---

## Quick Test Checklist

- [ ] Add building, room, instructor, TA, section
- [ ] Schedule multiple lab sessions
- [ ] Fill timesheet for some sessions
- [ ] Request makeup lab
- [ ] Approve makeup request
- [ ] Fill makeup session timesheet
- [ ] Generate weekly schedule (all sessions)
- [ ] Generate weekly timesheet (filled only)
- [ ] Generate section timesheet (verify contact hours and leaves)
- [ ] Verify makeup sessions included in reports
- [ ] Verify contact hours updated after makeup
- [ ] Verify leaves updated after makeup

---

## Troubleshooting

**If reports show wrong data:**
- Check that sessions are scheduled correctly
- Verify dates are in correct format (YYYY-MM-DD)
- Check that timesheets are filled

**If contact hours are wrong:**
- Verify actual times are filled
- Check that end time > start time
- Calculate manually: (end - start) in hours

**If leaves are wrong:**
- Count total sessions for the section
- Count filled sessions
- Leaves = Total - Filled

**If week reports miss sessions:**
- Verify week start date is correct
- Check that session dates are within the week
- Test with a week that has known sessions

---

## Sample Data Summary

**Buildings:**
- B1: Engineering Building (ATT1)
- B2: Science Building (ATT2)

**Rooms:**
- R1: Room 101, Building B1, Capacity 30
- R2: Room 102, Building B1, Capacity 25
- R3: Room 201, Building B2, Capacity 40

**Instructors:**
- INST1: Dr. John Smith (CS)
- INST2: Dr. Sarah Johnson (EE)

**TAs:**
- TA1: Jane Doe
- TA2: Bob Wilson
- TA3: Alice Brown

**Sections:**
- SEC1: Data Structures Lab (INST1, R1, TAs: TA1, TA2)
- SEC2: Algorithms Lab (INST1, R2, TA: TA3)
- SEC3: Circuit Analysis Lab (INST2, R3, TA: TA1)

**Sessions:**
- SESS1: SEC1, 2024-10-14 (Mon), 14:00-16:00
- SESS2: SEC1, 2024-10-16 (Wed), 14:00-16:00
- SESS3: SEC2, 2024-10-15 (Tue), 10:00-12:00
- SESS4: SEC3, 2024-10-14 (Mon), 09:00-11:00
- SESS5: SEC1, 2024-10-21 (Mon), 14:00-16:00
- SESS6: SEC1, 2024-10-23 (Wed), 14:00-16:00

Use this guide to systematically test all functionality!

