#pragma once

#include <fstream>
#include <stdexcept>

// this class is very similar to the fileManager
class Logger {
    private:

        std::string filePath;
        std::fstream file;
        std::string content;
        bool debug;

        void startup() {
            file.close();
            file.open(filePath, std::ios::out | std::ios::trunc);
            if (!file.is_open())
                throw std::runtime_error("Could not write to file: " + filePath);
            file << "";
        }

    public:

        Logger(std::string filePath, bool debug)
          : filePath(filePath)
          , debug(debug) {

            startup();
        }

        ~Logger() { file.close(); }

        void log(std::string content) {
            if (!debug)
                return;

            file.close();

            file.open(filePath, std::ios::out | std::ios::app);

            if (!file.is_open())
                throw std::runtime_error("Could not write to file: " + filePath);

            file << content;
            file.close();
            return;
        }
};