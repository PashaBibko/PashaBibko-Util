#include <core/ReturnVal.h>

namespace PashaBibko::Util::Internal
{
    void* ReturnValMemoryAdresses::s_FailAddress = (void*)0x0;
    void* ReturnValMemoryAdresses::s_SuccAddress = (void*)0x1;
}
