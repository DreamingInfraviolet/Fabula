#include "file_io.h"
#include <fstream>
#include <algorithm>
#include <sys/stat.h>

namespace FileIO {

/** Error to be thrown in a file could not be opened for io. */
class CouldNotOpenFile : public std::runtime_error {
 public:
  CouldNotOpenFile(const std::string& message) : std::runtime_error(message) {}
};


std::string readFile(const std::string& path) {
  std::ifstream stream(path);
  if (!stream)
    throw CouldNotOpenFile(std::string("Could not open '") + path +
                           "' for reading.");
  std::string str;

  // Preallocate memory
  stream.seekg(0, std::ios::end);
  str.reserve(stream.tellg());
  stream.seekg(0, std::ios::beg);

  // Apparently the extra parentheses are required
  str.assign((std::istreambuf_iterator<char>(stream)),
             std::istreambuf_iterator<char>());
  return str;
}

void writeFile(const std::string& path, const std::string& content) {
  std::ofstream stream(path, std::ios::trunc);
  if (!stream)
    throw CouldNotOpenFile(
        std::string("Could not open '") + path +
        "' for writing. Ensure that we have write permission.");
  stream << content;
  stream.flush();
}

bool folderExists(const std::string& path) {
  struct stat st;
  return (stat(path.c_str(), &st) == 0);
}

}

