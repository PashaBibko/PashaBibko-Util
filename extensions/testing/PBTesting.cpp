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
        /* Fetches the linked list of groups and stores the root */
        GroupTy group = GetTestGroups();
        const GroupTy root = group;

        /* Finds (and displays) global information of the tests */
        size_t groups = 0;
        size_t tests = 0;
        while (group != nullptr)
        {
            tests = tests + group->tests->m_Tests.size();
            groups++;

            group = group->next;
        }
        group = root;

        Util::Print<Util::Colour::LightGreen>("[ ====== ] ");
        Util::PrintLn("Found ", tests, " tests from ", groups, " different groups.", Util::NewLine);

        /* Executes the batches of tests */
        std::vector<UnitTest*> failures;
        while (group != nullptr)
        {
            Util::Print<Util::Colour::LightGreen>("[ ------ ] ");

            size_t testCount = group->tests->m_Tests.size();
            if (testCount == 1)
                Util::PrintLn(group->tests->m_Name, " ( 1 test )");

            else
                Util::PrintLn(group->tests->m_Name, " ( ", testCount, " tests )");
            
            group->tests->ExecuteBatch(failures);
            group = group->next;

            Util::Print(Util::NewLine);
        }

        /* Prints summary of all the tests */
        if (failures.size() == 0)
        {
            Util::Print<Util::Colour::LightGreen>("[ ====== ] ");
            Util::Print<Util::Colour::Green>("All tests passed.", Util::NewLine);
        }

        else
        {
            Util::Print<Util::Colour::Yellow>("[ ====== ] ");
            Util::Print<Util::Colour::Yellow>(failures.size(), " out of ", tests, " failed (listed below): ", Util::NewLine);

            for (UnitTest* failedTest : failures)
                Util::Print<Util::Colour::LightRed>("[ Failed ] ", failedTest->group, '.', failedTest->name, Util::NewLine);
        }

        Util::Print(Util::NewLine);
    }
}
