#include <fstream>
#include <stdexcept>

class FileManager {
private:
  std::string filePath;
  std::fstream file;
  std::string content;

public:
  FileManager(std::string filePath) : filePath(filePath) {}
  ~FileManager() { file.close(); }

  std::string read() {
    file.open(filePath, std::ios::in);
    if (!file.is_open())
      throw std::runtime_error("Could not read file: " + filePath);

    std::string line;
    this->content = "";

    while (std::getline(file, line)) {
      this->content += line + " ";
    }

    file.close();
    return this->content;
  }
  void write(std::string content, bool append = false) {
    file.close();

    if (append)
      file.open(filePath, std::ios::out | std::ios::app);
    else
      file.open(filePath, std::ios::out | std::ios::trunc);

    if (!file.is_open())
      throw std::runtime_error("Could not write to file: " + filePath);

    file << content;
    file.close();
    return; 
  }
};