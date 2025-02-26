#include <sol/sol.hpp>
#include <cmath>

struct Point
{
    double x, y;

    explicit Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

    [[nodiscard]] double distance_to(const Point& other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    [[nodiscard]] double get_x() const { return x; }
    void set_x(double x_) { x = x_; }
    [[nodiscard]] double get_y() const { return y; }
    void set_y(double y_) { y = y_; }
};

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

        return module.push();
    }
}


