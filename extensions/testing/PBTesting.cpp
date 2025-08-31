#include <extensions/testing/PBTesting.h>

#include <core/Log.h>

namespace PashaBibko::Util::Testing
{
    UnitTest::UnitTest(const char* testGroup, const char* testName, const char* filename)
        : group(testGroup), name(testName)
    {}
    
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

    UnitTestGroup::UnitTestGroup(const char* name, const std::vector<UnitTestGroup*>& deps)
        : m_Name(name)
    {
        /* Adds the group dependencies */
        for (const auto& dep : deps)
            m_GroupDependencies.push_back(dep);

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

    void UnitTestGroup::ExecuteBatch(std::vector<UnitTest*>& failures)
    {   
        /* Runs the tests and counts all the failures */
        size_t testsFailed = 0;
        for (UnitTest* test : m_Tests)
        {
            /* Runs the test and captures all the errors */
            std::vector<TestError*> errors;
            test->Dispatch(errors);

            if (errors.size() == 0)
            {
                /* Prints the sucess to the console */
                Util::Print<Util::Colour::LightGreen>("[ Passed ] ");
                Util::Print(test->name, Util::NewLine);
            }
            
            else
            {
                /* Prints the failure to the console */
                Util::Print<Util::Colour::LightRed>("[ Failed ] ");
                Util::Print(test->name, Util::NewLine);
                
                /* Prints all errors collected to the console */
                for (TestError* error : errors)
                    error->PrintToConsole();

                /* Registers the test as a failure */
                failures.push_back(test);
                testsFailed++;
            }
        }
        
        /* Displays a summary to the console */
        if (testsFailed == 0)
        {
            Util::Print<Util::Colour::LightGreen>("[ ------ ] ");
            Util::Print<Util::Colour::Green>("All tests in ", m_Name, " group passed.", Util::NewLine);
        }
        
        else
        {
            Util::Print<Util::Colour::Yellow>("[ ------ ] ");
            
            if (m_Tests.size() != 1)
                Util::Print<Util::Colour::Yellow>(testsFailed, " out of ", m_Tests.size(), " tests failed.", Util::NewLine);
            else
                Util::Print<Util::Colour::Yellow>("1 out of 1 test failed.", Util::NewLine);
        }
    }

    int ExecuteAllTests()
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
            Util::Print<Util::Colour::Green>("All tests passed.", Util::NewLine, Util::NewLine);

            return EXIT_SUCCESS; // 0
        }

        else
        {
            Util::Print<Util::Colour::Yellow>("[ ====== ] ");
            Util::Print<Util::Colour::Yellow>(failures.size(), " out of ", tests, " failed (listed below): ", Util::NewLine);

            for (UnitTest* failedTest : failures)
                Util::Print<Util::Colour::LightRed>("[ Failed ] ", failedTest->group, '.', failedTest->name, Util::NewLine);

            Util::Print(Util::NewLine);
            return EXIT_FAILURE; // 1
        }
    }
}
