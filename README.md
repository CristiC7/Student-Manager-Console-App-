# Student-Manager-Console-App-C++-
This is a complete student management system written in C++ for the console. It allows the user to add, edit, delete, sort, search, and save student data, as well as load it from a file.


### Features:

✅ Add a student (name and average grade between 1–10)

✅ Display all students

✅ Sort students by average (descending order)

✅ Edit student information (name and/or average)

✅ Delete a student by index

✅ Search for students by name (partial match, case-insensitive)

✅ Save student list to a text file (`students.txt`)

✅ Load student list from a text file (`students.txt`)

✅ Input validation and user-friendly prompts

## Technologies Used
- C++17 (compatible with C++11 and later)
- STL: `vector`, `algorithm`, `fstream`, `string`
- OOP: classes, encapsulation, static methods

##  How to Compile

### Using g++ (Linux/macOS/Windows via MinGW):

```bash
g++ -std=c++17 -o student_manager Student_Manager_Console_App.cpp
./student_managerr
```
## File Format
The program saves and loads data from a file named students.txt using this format:

Name,Average

John Doe,9.5

Maria Popescu,8.3

## Sample Menu

=== STUDENT MANAGER MENU ===

1. Add student

2. Display all students

3. Sort by average

4. Edit student

5. Delete student

6. Search student

7. Save to file

8. Load from file

0. Exit

## Project Structure
Student_Manager_Console_App.cpp   # Main source file

students.txt                      # (optional) Text file used for saving/loading students

README.md                         # This documentation

## Example Use Case
Add 3 students

Sort them by average

Edit one student

Save to file

Exit and restart the program

Load from file and continue

## Input Protection
Rejects invalid averages (must be between 1 and 10)

Verifies file operations succeed

Prevents out-of-bounds index access

## Author
Developed by CristiC7
