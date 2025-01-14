# Employee Management System

This is a simple console-based **Employee Management System** implemented in **C**. The system helps manage and organize employee-related information efficiently. It allows users to perform basic CRUD (Create, Read, Update, Delete) operations on employee records, such as adding new employees, viewing all employees, searching for an employee, updating employee details, and deleting employee records.

## Features

- Add a new employee to the system.
- View all employee records stored in the system.
- Search for an employee by their unique ID.
- Update existing employee details.
- Delete employee records.
- Data is stored persistently in a text file (`emp.txt`) using file handling in C.

## Purpose and Scope

This project was created to:
- Learn and practice file handling in C programming.
- Implement basic operations to manage employee data.
- Provide a beginner-friendly solution for small businesses or educational purposes that do not require complex databases or graphical interfaces.

## Technologies Used

- **Programming Language**: C
- **File Handling**: The employee data is stored and retrieved using file handling in C, specifically using the `fopen`, `fwrite`, `fread`, `fseek`, `remove`, and `rename` functions.
- **Data Structure**: A structure (`struct`) is used to organize employee details such as ID, name, salary, etc.

## Installation

To use this project:

1. Clone this repository to your local machine:

    ```bash
    git clone https://github.com/yourusername/employee-management-system.git
    ```

2. Navigate to the project directory:

    ```bash
    cd employee-management-system
    ```

3. Compile the C program using a C compiler (e.g., GCC):

    ```bash
    gcc main.c -o employee_management
    ```

4. Run the compiled program:

    ```bash
    ./employee_management
    ```

## Usage

After running the program, the user will be prompted with the following options:
- **Add Employee**: Add a new employee to the system.
- **View Employees**: View all the stored employee records.
- **Search Employee**: Search for an employee by their unique ID.
- **Update Employee**: Update the details of an existing employee.
- **Delete Employee**: Delete an employee from the system.

The system will perform the selected action, and the results will be shown in the terminal/console.

## Example Output

Here are a few sample outputs for different operations:

- **Adding a New Employee**:  
  ```text
  Enter employee ID: 101
  Enter employee name: John Doe
  Enter employee age: 30
  Enter employee salary: 50000
  Employee added successfully!
