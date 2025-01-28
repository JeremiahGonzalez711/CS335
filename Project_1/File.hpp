/*
Author: Jeremiah Gonzalez
Course: CSCI-335
Date: 9/24/2024
Instructor: Professor Justin Tojeira
Assignment: Project 1
*/
#pragma once

#include "InvalidFormatException.hpp"

class File {
   private:
      std::string filename_;
      std::string contents_;
      int* icon_;

      static const size_t ICON_DIM = 256; // Representing a 16 x 16 bitmap

   public: 
      /**
       * @brief Enables printing the object via std::cout
       */
      friend std::ostream& operator<< (std::ostream& os, const File& target);

      /**
       * @brief Overloads the less than comparison operator. 
       * @return True if the name of the File alphabetically precedes the name of the rhs. False otherwise.
       */
      bool operator<(const File& rhs) const;

      /**
       * @brief Get the value stored in name_
       */
      std::string getName() const;
      
      /**
       * @brief Get the value of contents_
       */
      std::string getContents() const;

      /**
       * @brief Set the value of contents_ to the provided string
       * 
       * @param new_contents A string representing the new contents of the file
       */
      void setContents(const std::string& new_contents);


      /**
       * @brief Gets the value of the icon_ member
       */
      int* getIcon() const;

      /**
       * @brief Sets the value of icon_ to the given parameter. De-allocates the previous array if necessary.
       * @param new_icon A pointer to a length 256 (ie. ICON_DIM) array of unsigned 8 bit integers
       */
      void setIcon(int* new_icon); 

      //                       DO NOT EDIT ABOVE THIS LINE. 
      //                  (with exceptions to include statements)
      // =========================== YOUR CODE HERE ===========================

/**
* @brief Constructs a new File object.
* 
* @param filename A const reference to a string containing alphanumeric characters and exactly one period in the format "filename" or "filename.extension"
*    - If the string contains any non-alphanumeric characters besides *exactly_one* period an InvalidFormatException is thrown
*    - If no extension is provided (e.g. there is no period within the provided filename) or nothing follows the period, then ".txt" is used as the extension
*    - Default value of "NewFile.txt" if none provided or if filename is empty 
* @param contents A string representing the contents of the file. Default to empty string if none provided.
* @param icon A pointer to an integer array with length ICON_DIM. Default to nullptr if none provided.
* @throws InvalidFormatException - An error that occurs if the filename is not valid by the above constraints.
* @note You'll notice we provide a default value for the first possible argument (filename)
*       Yes, this means we can define override the default constructor and define a parameterized one simultaneously.
*/
File(const std::string& filename = "NewFile.txt", const std::string& contents = "", int* icon = nullptr);

/**
* @brief Calculates and returns the size of the File Object (IN BYTES), using .size()
* @return size_t The number of bytes the File's contents consumes
* @note Consider this: how does this relate to the string's length? Why is that the case?
*/
size_t getSize() const;

/**
 * @brief (COPY CONSTRUCTOR) Constructs a new File object as a deep copy of the target File
 * @param rhs A const reference to the file to be copied from
 */
File(const File& rhs);

/**
 * @brief (COPY ASSIGNMENT) Replaces the calling File's data members using a deep copy of the rhs File.
 * 
 * @param rhs A const reference to the File object to be copied
 * @return A reference to the new File copy
 * @note If copy assignment operator is invoked upon itself, do nothing.
 */
File& operator=(const File& rhs);

/**
 * @brief (MOVE CONSTRUCTOR) Construct a new File object by moving the data from the righthand side File Object
 * @param rhs The File whose data is moved
 * @post The rhs File object is left in a valid, but ready to be deleted state:
 *    - All string members are themselves moved.
 *    - ALl pointers are set to nullptr
 */
File(File&& rhs);

/**
 * @brief (MOVE ASSIGNMENT) Move the rhs data to the calling file object
 * 
 * @param rhs The File whose data is moved
 * @return A reference to the object which the data was moved into
 * @post The rhs File object is left in a valid, but ready to be deleted state:
 *    - All string members are moved.
 *    - ALl pointers are set to nullptr
 * @note If move assignment operator is invoked upon itself, do nothing.
 */
File& operator=(File&& rhs);

/**
 * @brief (DESTRUCTOR) Routine for object deletion
 * @post All dynamically allocated memory is released
 */
~File();

};