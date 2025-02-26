//
// Created by Aidan Jost on 2/26/25.
//
module;
#include <sol/sol.hpp>
export module beem;

export import raylib;
export import euclid;

export namespace beem
{
    extern "C"
{
    __attribute__((visibility("default"))) int luaopen_beem(lua_State* L) {
        sol::state_view lua(L);
        sol::table module = lua.create_table();

        // Simple function
        module.new_usertype<Point>("Point",
            sol::constructors<Point(), Point(double, double)>(),
            "x", sol::property(&Point::get_x, &Point::set_x),
            "y", sol::property(&Point::get_y, &Point::set_y),
            "distance_to", &Point::distance_to
        );

        RaylibModule::register_module(module);

        return module.push();
    }
}
}
