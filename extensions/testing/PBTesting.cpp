#include <extensions/testing/PBTesting.h>

namespace PashaBibko::Util::Testing
{
    struct GroupLinkedListNode
    {
        GroupLinkedListNode* next;
        UnitTestGroup* tests;
    };

    using GroupTy = GroupLinkedListNode*;

    static GroupTy GetTestGroups()
    {
        static GroupLinkedListNode root;
        return &root;
    }

    UnitTestGroup::UnitTestGroup(const char* name)
        : m_Name(name)
    {
        /* Finds the last node in the linked list */
        GroupTy group = GetTestGroups();
        const bool isRoot = group->tests == nullptr;
        while (group->next != nullptr)
        {
            group = group->next;
        }

        /* Adds the new node */
        if (!isRoot)
        {
            group->next = new GroupLinkedListNode;
            group = group->next;
        }

        group->next = nullptr;
        group->tests = this;
    }

    void ExecuteAllTests()
    {
        GroupTy group = GetTestGroups();

        while (group != nullptr)
        {
            Util::PrintLn("Executing test batch [", group->tests->m_Name, "]");
            group->tests->ExecuteBatch();

            group = group->next;
        }
    }
}
