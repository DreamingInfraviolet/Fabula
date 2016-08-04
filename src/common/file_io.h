#pragma once
#include <string>

/** A series of functions to help with reading and writing files. */
namespace FileIO {
/** Reads a file to string */
std::string readFile(const std::string& path);

/** Writes a string to file */
void writeFile(const std::string& path, const std::string& content);

/** Returns true if a folder exists */
bool folderExists(const std::string& path);
}

