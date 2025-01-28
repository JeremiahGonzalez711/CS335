/*
Author: Jeremiah Gonzalez
Course: CSCI-335
Date: 9/24/2024
Instructor: Professor Justin Tojeira
Assignment: Project 1
*/
#pragma once

#include "File.hpp"
#include "InvalidFormatException.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

class Folder {
   private:
      std::string name_;
      std::vector<File> files_;

   public:
      /**
      * @brief Construct a new Folder object
      * @param name A string with alphanumeric characters
         If the folder name is empty / none is provided, default value of "NewFolder" is used. 
      * @throw If the name is invalid (eg. contains non-alphanumeric characters) an InvalidFormatException is thrown
      */
      Folder(const std::string& name = "NewFolder");

      /**
       * @brief Get the value stored in name_
       * @return std::string 
       */
      std::string getName() const;

      /**
       * @brief Sets the name_ member to the given parameter
       * 
       * @param name A string containing only alphanumeric characters
       *    - If the string is invalid the folder is not renamed
       * @return True if the folder was renamed sucessfully. False otherwise.
       */
      bool rename(const std::string& name);

      /**
       * @brief Sorts and prints the names of subfolder and file vectors lexicographically (ie. alphabetically)
       * The contents of subfolders are also printed.
       * Reference the following format (using 3 spaces to indent each directory layer)
       * (FOLDER) <CURRENT_FOLDER_NAME> 
       *    <FILENAME_1>
       *    <FILENAME_2>
       *     ...
       *    <FILENAME_N>
       * 
       */
      void display();

      //                       DO NOT EDIT ABOVE THIS LINE. 
      //                  (with exceptions to include statements)
      // =========================== YOUR CODE HERE ===========================

/**
* @brief Iterate through the files vector, calculating the total size of all child files
* @return size_t The total size of all child files
*/
size_t getSize() const;

/**
* @brief Appends the given file to the files_ vector using move_semantics on the parameter File object, if a file with the same name does not exist within the files_ vector
*    (HINT!) Consider push_back(). What happens when we give it an l-value vs. an r-value? Does it change anything?
* 
* @param new_file A reference to a File object to be added. If the name of the File object is empty (ie. its contents have been taken via move) the add fails  
* @return True if the file was added successfully. False otherwise.
* @post If the file was added, leaves the parameter File object in a valid but unspecified state
*/
bool addFile(File& new_file); //was passing in a r value instead of a regular reference 

/**
 * @brief Searches for a file within the files_ vector to be deleted.
 * If a file object with a matching name is found, erase it from the vector in linear [O(N)] time or better.
 * Order does not matter.
 * 
 * @param name A const reference to a string representing the filename to be deleted
 * @return True if the file was found & successfully deleted. 
 */
bool removeFile(const std::string& name);

/**
 * @brief Moves a file from the current folder to a specified folder 
 * If a matching name is found, use move semantics to move the object from the current directory to the file vector within the destination folder'
 *    and erase it from the current folder. 
 * If a matching name is not found within the source folder or an object with the same name already exists within the 
 *    destination folder, nothing is moved.
 * If the source folder and destination folders are the same, the move is always considered successful.
 * 
 * @param name The name of the file to be moved, as a const reference to a string
 * @param destination The target folder to be moved to, as a reference to a Folder object
 * @return True if the file was moved successfully. False otherwise.
 */
bool moveFileTo(const std::string& name, Folder& destination);

/**
* @brief Copies a file within the current folder to the destination folder.
* If there is already an object with the same name in the destination folder, 
*    or the object with the specified name does not exist, do nothing.                                                                                                                                                                                                                                                       
* Otherwise, if there exists a file with the given name from the source folder, 
*    use the copy constructor or assignment operations to create a deep copy of the 
*    the file into the destination.
* 
* @param name The name of the copied object, as a const string reference
* @param destination The destination folder, as a reference to a Folder object
* @return True if the file was copied successfully. False otherwise.
*/
bool copyFileTo(const std::string& name, Folder& destination);

};