#ifndef REMOVEMAXSNAPSHOT_H
#define REMOVEMAXSNAPSHOT_H

#include <vector>
#include <optional>

class RemoveMaxSnapshot
{
public:
    explicit RemoveMaxSnapshot(
        const std::vector<int>& tree,
        std::optional<int> greaterComparedNodeIndex,
        std::optional<int> smallerComparedNodeIndex,
        int extractedNodeKey
    )
        : m_tree(tree)
        , m_greaterComparedNodeIndex(greaterComparedNodeIndex)
        , m_smallerComparedNodeIndex(smallerComparedNodeIndex)
        , m_extractedNodeKey(extractedNodeKey)
    {}

    [[nodiscard]] const std::vector<int>& getTree() const { return m_tree; }

    [[nodiscard]] std::optional<int> getGreaterComparedNodeIndex() const { return m_greaterComparedNodeIndex; }

    [[nodiscard]] std::optional<int> getSmallerComparedNodeIndex() const { return m_smallerComparedNodeIndex; }

    [[nodiscard]] int getExtractedNodeKey() const { return m_extractedNodeKey; }

private:
    const std::vector<int> m_tree;
    const std::optional<int> m_greaterComparedNodeIndex;
    const std::optional<int> m_smallerComparedNodeIndex;
    const int m_extractedNodeKey;
};

#endif // REMOVEMAXSNAPSHOT_H
