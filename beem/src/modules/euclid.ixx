//
// Created by Aidan Jost on 2/26/25.
//
module;
#include <sol/sol.hpp>
#include <cmath>
export module euclid;

export namespace beem
{

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



    struct Size
    {
        double width, height;
        explicit Size(double width_ = 0, double height_ = 0) : width(width_), height(height_) {}
        [[nodiscard]] double get_width() const { return width; }
        void set_width(double width_) { width = width_; }
        [[nodiscard]] double get_height() const { return height; }

    };

    struct Rectangle
    {
        Point origin;
        Size size;

        explicit Rectangle(Point origin_ = Point(), Size size_ = Size()) : origin(origin_), size(size_) {}

        [[nodiscard]] Point get_origin() const { return origin; }
        void set_origin(Point origin_) { origin = origin_; }
        [[nodiscard]] Size get_size() const { return size; }
        void set_size(Size size_) { size = size_; }
    };








}


