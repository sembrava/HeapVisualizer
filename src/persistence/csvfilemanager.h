#ifndef CSVFILEMANAGER_H
#define CSVFILEMANAGER_H

#include "filemanager.h"

class CsvFileManager : public FileManager
{
public:
    explicit CsvFileManager(const std::string& path);

    TreeFileInfo load(const std::string &name) override;

    std::vector<TreeFileInfo> loadAll() override;

    void save(const std::string &name, const std::vector<int> &tree) override;

    void remove(const std::string &name) override;

private:
    const std::string m_path;
};

#endif // CSVFILEMANAGER_H
