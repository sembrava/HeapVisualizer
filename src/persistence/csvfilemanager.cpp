#include <fstream>
#include <filesystem>

#include "csvfilemanager.h"
#include "../utils/utils.h"

CsvFileManager::CsvFileManager(const std::string& path)
    : m_path(path)
{}

TreeFileInfo CsvFileManager::load(const std::string& name)
{
    std::ifstream reader(m_path + "/" + name + ".csv");

    if (!reader.is_open())
        throw std::ios_base::failure("Failed to open file " + name + ".csv");

    std::string line;

    if (std::getline(reader, line))
    {
        const std::vector<std::string> keys = Utils::split(line, ',');
        std::vector<int> tree;

        try
        {
            for (const std::string& key : keys)
                tree.push_back(std::stoi(key));
        }
        catch (const std::invalid_argument& e)
        {
            throw std::ios_base::failure("File " + name + ".csv is incorrectly formatted");
        }

        return TreeFileInfo(name, tree);
    }

    throw std::ios_base::failure("File " + name + ".csv is empty");
}

std::vector<TreeFileInfo> CsvFileManager::loadAll()
{
    std::vector<TreeFileInfo> trees;

    for (const auto& entry : std::filesystem::directory_iterator(m_path))
    {
        try
        {
            trees.push_back(load(entry.path().stem().string()));
        }
        catch (...) { }
    }

    return trees;
}

void CsvFileManager::save(const std::string& name, const std::vector<int>& tree)
{
    std::ofstream writer(m_path + "/" + name + ".csv");

    if (!writer.is_open())
        throw std::ios_base::failure("Failed to open file " + name + ".csv");

    for (int i = 0; i < tree.size(); i++)
    {
        if (i != 0)
            writer << ",";

        writer << std::to_string(tree[i]);
    }
}

void CsvFileManager::remove(const std::string& name)
{
    try
    {
        if (!std::filesystem::remove(m_path + "/" + name + ".csv"))
            throw std::ios_base::failure("File " + name + ".csv not found");
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        throw std::ios_base::failure("Failed to delete file " + name + ".csv");
    }
}
