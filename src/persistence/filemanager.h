#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

#include "treefileinfo.h"

class FileManager
{
public:    
    virtual TreeFileInfo load(const std::string& name) = 0;

    virtual std::vector<TreeFileInfo> loadAll() = 0;

    virtual void save(const std::string& name, const std::vector<int>& tree) = 0;

    virtual void remove(const std::string& name) = 0;
};

#endif // FILEMANAGER_H
