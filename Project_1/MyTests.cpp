/*
Author: Jeremiah Gonzalez
Course: CSCI-335
Date: 9/24/2024
Instructor: Professor Justin Tojeira
Assignment: Project 1
*/

#include <iostream>
#include "Folder.hpp"
#include "File.hpp"
#include "InvalidFormatException.hpp" 

int main() {

    // 1 testing the paramconstructor and getsize function (first instance of testing)
    // int *new_icon = new int[128];

    // File New_file("test_file.txt", "This is wack.", new_icon);
    // File File_2("test_file2.txt", "This is wack kinda.", new_icon);

    // std::cout << New_file.getName() << std::endl;
    // std::cout << New_file.getSize() << std::endl;
    // std::cout << New_file.getContents() << std::endl;
    // std::cout << New_file.getIcon() << std::endl;

    // std::cout << File_2.getName() << std::endl;
    // std::cout << File_2.getSize() << std::endl;
    // std::cout << File_2.getContents() << std::endl;
    // std::cout << File_2.getIcon() << std::endl;

    //testing copy constructor and assignment operator 
    //Create a sample icon array for testing
    // int* iconArray1 = new int[256];
    // for (int i = 0; i < 256; ++i) {
    //     iconArray1[i] = i;  // Fill the array with some test data
    // }

    // // Create a File object using the parameterized constructor
    // File file1("TestFile.txt", "This is the content of file1.", iconArray1);


    // 2 Test the copy constructor
    // File file2(file1);  // file2 is a deep copy of file1 using the copy constructor

    // // Modify file1's contents and icon to see if file2 remains unaffected
    // file1.setContents("Modified content of file1.");
    // int* newIcon = new int[256];
    // for (int i = 0; i < 256; ++i) {
    //     newIcon[i] = i * 2;  
    // }
    // file1.setIcon(newIcon);

    // std::cout << "File 1 Contents: " << file1.getContents() << std::endl;
    // std::cout << "File 2 Contents (after copy): " << file2.getContents() << std::endl;

    // // Test copy assignment operator
    // File file3;  // Default constructor
    // file3 = file1;  

    // std::cout << "File 3 Contents (after assignment): " << file3.getContents() << std::endl;

    // // Modify file3's contents to ensure file1 is unaffected
    // file3.setContents("Modified content of file3.");
    // std::cout << "File 3 Contents (after modification): " << file3.getContents() << std::endl;
    // std::cout << "File 1 Contents (should remain unchanged): " << file1.getContents() << std::endl;

    // std::cout << file3.getContents() << std::endl;

    // //clear dynamically allocated memory
    // delete[] iconArray1;
    // delete[] newIcon;

    //testing all function in the files.cpp
    //Test 1: Default constructor and parameterized constructor (second instance of testing)
    int icon1[] = {1, 2, 3};  //icon data 
    File file1("TestFile.txt", "This is a test file.", icon1);
    std::cout << "File 1 details: \n" << file1 << std::endl;

    // Test 2: Copy constructor
    File file2 = file1; 
    std::cout << "\nFile 2 (copy of file 1) details: \n" << file2 << std::endl;

    // Test 3: Modify file2 contents and verify file1 remains unchanged (2nd instance of using the copy constructor)
    file2.setContents("This is the modified contents of file2.");
    std::cout << "\nAfter modifying file 2 contents: " << std::endl;
    std::cout << "File 1 contents: " << file1.getContents() << std::endl;
    std::cout << "File 2 contents: " << file2.getContents() << std::endl;

    // Test 4: Copy assignment
    File file3;
    file3 = file1; 
    std::cout << "\nFile 3 (copy assigned from file 1) details: \n" << file3 << std::endl;

    // Test 5: Move constructor
    File file4 = std::move(file1); 
    std::cout << "\nFile 4 (moved from file 1) details: \n" << file4 << std::endl;
    std::cout << "File 1 details after being moved: \n" << file1 << std::endl;  

    // Test 6: Move assignment
    File file5;
    file5 = std::move(file2);  
    std::cout << "\nFile 5 (moved from file 2) details: \n" << file5 << std::endl;
    std::cout << "File 2 details after being moved: \n" << file2 << std::endl;  // File 2 should be in a valid but empty state

    return 0;
}