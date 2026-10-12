#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class PropertySystem;   // forward declaration

// Reads and writes all data files.
class FileManager {
private:
    std::string peopleFile;
    std::string propertyFile;
    std::string requestFile;

public:
    FileManager();
    ~FileManager();

    void saveAll(const PropertySystem& system) const;
    void loadAll(PropertySystem& system) const;
};

#endif