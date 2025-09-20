#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
class SolBindTest
{
public:
    sol::state lua;
    SolBindTest()
    {
        lua.open_libraries
        (
            sol::lib::base
        );
    }
    void DoSome()
    {
        lua.script("print(\"Hello lua!\");");
    }
};


