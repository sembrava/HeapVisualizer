#ifndef CSVFILEMANAGER_H
#define CSVFILEMANAGER_H

#include "filemanager.h"

class CsvFileManager : FileManager
{
public:
    explicit CsvFileManager(const std::string& path);

    TreeFileInfo load(const std::string &name);

    std::vector<TreeFileInfo> loadAll();

    void save(const std::string &name, const std::vector<int> &tree);

    void remove(const std::string &name);

private:
    const std::string m_path;
};

#endif // CSVFILEMANAGER_H
