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

    UnitTestGroup::UnitTestGroup()
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

        Util::PrintLn("Added test group ", isRoot);
    }

    void ExecuteAllTests()
    {
        GroupTy group = GetTestGroups();

        while (group != nullptr)
        {
            Util::PrintLn("Executing test batch ", group->tests != nullptr);
            group = group->next;
        }
    }
}
