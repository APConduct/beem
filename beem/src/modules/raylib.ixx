//
// Created by Aidan Jost on 2/26/25.
//

module;
#include <raylib.h>
#include <sol/sol.hpp>
#include <Vector>
#include <functional>

export module raylib;

export namespace beem
{

    class Window
    {
    public:
        using EventHandler = std::function<void()>;

        Window(int width, int height, const char* title)
            : width_(width), height_(height), title_(title), is_current_(false)
        {
            InitWindow(width, height, title);
            SetTargetFPS(60);
            is_current_ = true;
        }
        ~Window()
        {
            if (is_current_)
            {
                EndDrawing();
            }
            CloseWindow();
        };

        void begin_frame()
        {
            SetTargetFPS(60);
            BeginDrawing();
            is_current_ = true;
        }
        void end_frame()
        {
            EndDrawing();
            is_current_ = false;
        }


        [[nodiscard]] bool should_close()
        {
            return WindowShouldClose();
        }


        void clear_background(Color color)
        {
            ClearBackground(color);
        };
        void draw_circle(int x, int y, float radius, Color color)
        {
            DrawCircle(x, y, radius, color);
        }


        void on_update(sol::function handler)
        {
            update_handler_ = std::move(handler);
        }

        void on_draw(sol::function handler)
        {
            draw_handler_ = std::move(handler);
        }

        void handle_events() const
        {
            if (update_handler_)
            {
                update_handler_();
            }
            if (draw_handler_)
            {
                draw_handler_();
            }
        };

    private:
        int width_;
        int height_;
        const char* title_;
        bool is_current_;

        sol::function update_handler_;
        sol::function draw_handler_;
    };

    class RaylibModule
    {
    public:



        static void register_module(sol::table& module);
        static void init();
        static void shutdown();


        static Window* create_window(int width, int height, const char* title)
        {
            auto window = std::make_unique<Window>(width, height, title);
            windows_.push_back(std::move(window));
            return windows_.back().get();
        }

    private:
        static std::vector<std::unique_ptr<Window>> windows_;
    };

    std::vector<std::unique_ptr<Window>> RaylibModule::windows_;

    void RaylibModule::register_module(sol::table& module)
    {

        module.new_usertype<Color>("Color",
            sol::constructors<Color(unsigned char, unsigned char, unsigned char, unsigned char)>(),
            "r", &Color::r,
            "g", &Color::g,
            "b", &Color::b,
            "a", &Color::a
        );

        module.new_usertype<Vector2>("Vector2",
            sol::constructors<Vector2(float, float)>(),
            "x", &Vector2::x,
            "y", &Vector2::y
        );

        module.new_usertype<Rectangle>("Rectangle",
            sol::constructors<Rectangle(float, float, float, float)>(),
            "x", &Rectangle::x,
            "y", &Rectangle::y,
            "width", &Rectangle::width,
            "height", &Rectangle::height,
            "draw", DrawRectangle,
            "draw_lines", DrawRectangleLines,
            "draw_rec", DrawRectangleRec,
            "draw_rec_lines", DrawRectangleLinesEx,
            "draw_gradient", DrawRectangleGradientEx,
            "draw_radient_v", DrawRectangleGradientV,
            "draw_gradient_h", DrawRectangleGradientH,
            "draw_billboard", DrawBillboardRec,
            "draw_v", DrawRectangleV
        );


        module.set_function("rect", [](float x, float y, float width, float height) {
            return Rectangle{x, y, width, height};
        });



        module.new_usertype<Image>("Image",
            sol::constructors<Image()>(),
            "data", &Image::data,
            "width", &Image::width,
            "height", &Image::height,
            "mipmaps", &Image::mipmaps,
            "format", &Image::format,
            "resize", ImageResize,
            "copy", ImageCopy,
            "crop", ImageCrop,
            "draw", ImageDraw
            );

        module.new_usertype<Texture2D>("Texture2D",
            sol::constructors<Texture2D()>(),
            "id", &Texture2D::id,
            "width", &Texture2D::width,
            "height", &Texture2D::height,
            "mipmaps", &Texture2D::mipmaps,
            "format", &Texture2D::format
        );

        module.new_usertype<GlyphInfo>("GlyphInfo",
            sol::constructors<GlyphInfo()>(),
            "value", &GlyphInfo::value,
            "offset_x", &GlyphInfo::offsetX,
            "offset_y", &GlyphInfo::offsetY,
            "advance_x", &GlyphInfo::advanceX,
            "image", &GlyphInfo::image
        );

        module.new_usertype<Font>("Font",
            sol::constructors<Font()>(),
            "base_size", &Font::baseSize,
            "glyph_count", &Font::glyphCount,
            "texture", &Font::texture,
            "recs", &Font::recs,
            "glyphs", &Font::glyphs
        );


        module.new_usertype<Vector3>("Vector3",
            sol::constructors<Vector3(float, float, float)>(),
            "x", &Vector3::x,
            "y", &Vector3::y,
            "z", &Vector3::z
        );

        module.new_usertype<Vector4>("Vector4",
            sol::constructors<Vector4(float, float, float, float)>(),
            "x", &Vector4::x,
            "y", &Vector4::y,
            "z", &Vector4::z,
            "w", &Vector4::w
        );

        module.new_usertype<Matrix>("Matrix",
            sol::constructors<Matrix(float, float, float, float,
                                     float, float, float, float,
                                     float, float, float, float,
                                     float, float, float, float)>(),
            "m0", &Matrix::m0,
            "m1", &Matrix::m1,
            "m2", &Matrix::m2,
            "m3", &Matrix::m3,
            "m4", &Matrix::m4,
            "m5", &Matrix::m5,
            "m6", &Matrix::m6,
            "m7", &Matrix::m7,
            "m8", &Matrix::m8,
            "m9", &Matrix::m9,
            "m10", &Matrix::m10,
            "m11", &Matrix::m11,
            "m12", &Matrix::m12,
            "m13", &Matrix::m13,
            "m14", &Matrix::m14,
            "m15", &Matrix::m15
        );
        module.new_usertype<Quaternion>("Quaternion",
            sol::constructors<Quaternion(float, float, float, float)>(),
            "x", &Quaternion::x,
            "y", &Quaternion::y,
            "z", &Quaternion::z,
            "w", &Quaternion::w
        );

        module.new_usertype<RenderTexture>("RenderTexture",
            sol::constructors<RenderTexture()>(),
            "texture", &RenderTexture::texture
        );

        module.new_usertype<Camera>("Camera",
            sol::constructors<Camera(Vector3, Vector3, Vector3, float)>(),
            "position", &Camera::position,
            "target", &Camera::target,
            "up", &Camera::up,
            "fovy", &Camera::fovy
        );

        module.new_usertype<Camera2D>("Camera2D",
            sol::constructors<Camera2D(Vector2, Vector2, float, float)>(),
            "offset", &Camera2D::offset,
            "target", &Camera2D::target,
            "rotation", &Camera2D::rotation,
            "zoom", &Camera2D::zoom
        );

        module.new_usertype<Ray>("Ray",
            sol::constructors<Ray(Vector3, Vector3)>(),
            "position", &Ray::position,
            "direction", &Ray::direction
        );

        module.new_usertype<AudioStream>("AudioStream",
            sol::constructors<AudioStream()>(),
            "sample_rate", &AudioStream::sampleRate,
            "channels", &AudioStream::channels,
            "sample_size", &AudioStream::sampleSize
            );

        module.new_usertype<Sound>("Sound",
            sol::constructors<Sound()>(),
            "stream", &Sound::stream,
            "frame_count", &Sound::frameCount
            );

        module.new_usertype<Music>("Music",
            sol::constructors<Music()>(),
            "stream", &Music::stream,
            "ctx_type", &Music::ctxType,
            "ctx_data", &Music::ctxData,
            "looping", &Music::looping,
            "frame_count", &Music::frameCount
        );

        module.new_usertype<Wave>("Wave",
            sol::constructors<Wave()>(),
            "frame_count", &Wave::frameCount,
            "sample_rate", &Wave::sampleRate,
            "channels", &Wave::channels,
            "sample_size", &Wave::sampleSize,
            "data", &Wave::data
        );

        module.new_usertype<FilePathList>("FilePathList",
            sol::constructors<FilePathList()>(),
            "paths", &FilePathList::paths,
            "count", &FilePathList::count,
            "capacity", &FilePathList::capacity
        );

        module.new_usertype<Shader>("Shader",
            sol::constructors<Shader()>(),
            "id", &Shader::id,
            "locs", &Shader::locs
        );

        module.new_usertype<AutomationEvent>("AutomationEvent",
            sol::constructors<AutomationEvent()>(),
            "type", &AutomationEvent::type,
            "frame", &AutomationEvent::frame,
            "params", &AutomationEvent::params
        );

        module.new_usertype<AutomationEventList>("AutomationEventList",
            sol::constructors<AutomationEventList()>(),
            "events", &AutomationEventList::events,
            "count", &AutomationEventList::count,
            "capacity", &AutomationEventList::capacity
        );

        module.new_usertype<Window>("Window",
            sol::constructors<Window(int, int, const char*)>(),
            "begin_frame", &Window::begin_frame,
            "end_frame", &Window::end_frame,
            "clear_background", &Window::clear_background,
            "draw_circle", &Window::draw_circle,
            "on_update", &Window::on_update,
            "on_draw", &Window::on_draw,
            "should_close", &Window::should_close,
            "handle_events", &Window::handle_events

        );

        module.new_usertype<RaylibModule>("RaylibModule",
            sol::constructors<RaylibModule()>(),
            "init", &RaylibModule::init,
            "shutdown", &RaylibModule::shutdown,
            "create_window", &RaylibModule::create_window
        );

        sol::table raylib = module.create();
        raylib["init"] = &RaylibModule::init;
        raylib["shutdown"] = &RaylibModule::shutdown;
        raylib["create_window"] = &RaylibModule::create_window;
        module["raylib"] = raylib;
        module["MOUSE_BUTTON_LEFT"] = MouseButton::MOUSE_BUTTON_LEFT;
        module["MOUSE_BUTTON_RIGHT"] = MouseButton::MOUSE_BUTTON_RIGHT;
        module["MOUSE_BUTTON_MIDDLE"] = MouseButton::MOUSE_BUTTON_MIDDLE;
        module["MOUSE_BUTTON_SIDE"] = MouseButton::MOUSE_BUTTON_SIDE;
        module["MOUSE_BUTTON_EXTRA"] = MouseButton::MOUSE_BUTTON_EXTRA;
        module["MOUSE_BUTTON_FORWARD"] = MouseButton::MOUSE_BUTTON_FORWARD;
        module["MOUSE_BUTTON_BACK"] = MouseButton::MOUSE_BUTTON_BACK;
        module["KEY_SPACE"] = KEY_SPACE;
        module["KEY_APOSTROPHE"] = KEY_APOSTROPHE;
        module["KEY_COMMA"] = KEY_COMMA;
        module["KEY_MINUS"] = KEY_MINUS;
        module["KEY_PERIOD"] = KEY_PERIOD;
        module["KEY_SLASH"] = KEY_SLASH;
        module["KEY_0"] = KEY_ZERO;
        module["KEY_1"] = KEY_ONE;
        module["KEY_2"] = KEY_TWO;
        module["KEY_3"] = KEY_THREE;
        module["KEY_4"] = KEY_FOUR;
        module["KEY_5"] = KEY_FIVE;
        module["KEY_6"] = KEY_SIX;
        module["KEY_7"] = KEY_SEVEN;
        module["KEY_8"] = KEY_EIGHT;
        module["KEY_9"] = KEY_NINE;
        module["KEY_SEMICOLON"] = KEY_SEMICOLON;
        module["KEY_EQUAL"] = KEY_EQUAL;
        module["KEY_A"] = KEY_A;
        module["KEY_B"] = KEY_B;
        module["KEY_C"] = KEY_C;
        module["KEY_D"] = KEY_D;
        module["KEY_E"] = KEY_E;
        module["KEY_F"] = KEY_F;
        module["KEY_G"] = KEY_G;
        module["KEY_H"] = KEY_H;
        module["KEY_I"] = KEY_I;
        module["KEY_J"] = KEY_J;
        module["KEY_K"] = KEY_K;
        module["KEY_L"] = KEY_L;
        module["KEY_M"] = KEY_M;
        module["KEY_N"] = KEY_N;
        module["KEY_O"] = KEY_O;
        module["KEY_P"] = KEY_P;
        module["KEY_Q"] = KEY_Q;
        module["KEY_R"] = KEY_R;
        module["KEY_S"] = KEY_S;
        module["KEY_T"] = KEY_T;
        module["KEY_U"] = KEY_U;
        module["KEY_V"] = KEY_V;
        module["KEY_W"] = KEY_W;
        module["KEY_X"] = KEY_X;
        module["KEY_Y"] = KEY_Y;
        module["KEY_Z"] = KEY_Z;
        module["KEY_LEFT_BRACKET"] = KEY_LEFT_BRACKET;
        module["KEY_BACKSLASH"] = KEY_BACKSLASH;
        module["KEY_RIGHT_BRACKET"] = KEY_RIGHT_BRACKET;
        module["KEY_GRAVE"] = KEY_GRAVE;
        module["KEY_ESCAPE"] = KEY_ESCAPE;
        module["KEY_ENTER"] = KEY_ENTER;
        module["KEY_TAB"] = KEY_TAB;
        module["KEY_BACKSPACE"] = KEY_BACKSPACE;
        module["KEY_INSERT"] = KEY_INSERT;
        module["KEY_DELETE"] = KEY_DELETE;
        module["KEY_RIGHT"] = KEY_RIGHT;
        module["KEY_LEFT"] = KEY_LEFT;
        module["KEY_DOWN"] = KEY_DOWN;
        module["KEY_UP"] = KEY_UP;
        module["KEY_PAGE_UP"] = KEY_PAGE_UP;
        module["KEY_PAGE_DOWN"] = KEY_PAGE_DOWN;
        module["KEY_HOME"] = KEY_HOME;
        module["KEY_END"] = KEY_END;
        module["KEY_CAPS_LOCK"] = KEY_CAPS_LOCK;
        module["KEY_SCROLL_LOCK"] = KEY_SCROLL_LOCK;
        module["KEY_NUM_LOCK"] = KEY_NUM_LOCK;
        module["KEY_PRINT_SCREEN"] = KEY_PRINT_SCREEN;
        module["KEY_PAUSE"] = KEY_PAUSE;
        module["KEY_F1"] = KEY_F1;
        module["KEY_F2"] = KEY_F2;
        module["KEY_F3"] = KEY_F3;
        module["KEY_F4"] = KEY_F4;
        module["KEY_F5"] = KEY_F5;
        module["KEY_F6"] = KEY_F6;
        module["KEY_F7"] = KEY_F7;
        module["KEY_F8"] = KEY_F8;
        module["KEY_F9"] = KEY_F9;
        module["KEY_F10"] = KEY_F10;
        module["KEY_F11"] = KEY_F11;
        module["KEY_F12"] = KEY_F12;
        module["KEY_LEFT_SHIFT"] = KEY_LEFT_SHIFT;
        module["KEY_LEFT_CONTROL"] = KEY_LEFT_CONTROL;
        module["KEY_LEFT_ALT"] = KEY_LEFT_ALT;
        module["KEY_LEFT_SUPER"] = KEY_LEFT_SUPER;
        module["KEY_RIGHT_SHIFT"] = KEY_RIGHT_SHIFT;
        module["KEY_RIGHT_CONTROL"] = KEY_RIGHT_CONTROL;
        module["KEY_RIGHT_ALT"] = KEY_RIGHT_ALT;
        module["KEY_RIGHT_SUPER"] = KEY_RIGHT_SUPER;
        module["KEY_KB_MENU"] = KEY_KB_MENU;
        module["KEY_LEFT_BRACKET"] = KEY_LEFT_BRACKET;
        module["KEY_RIGHT_BRACKET"] = KEY_RIGHT_BRACKET;
        module.set_function("app_dir", &GetApplicationDirectory);
        module.set_function("working_dir", &GetWorkingDirectory);
        module.set_function("get_time", &GetTime);
        module.set_function("get_random_value", &GetRandomValue);
        module.set_function("open_url", &OpenURL);
        module.set_function("set_random_seed", &SetRandomSeed);
        module.set_function("get_mouse_x", &GetMouseX);
        module.set_function("get_mouse_y", &GetMouseY);
        module.set_function("get_mouse_wheel_move", &GetMouseWheelMove);
        module.set_function("get_mouse_delta", GetMouseDelta);
        module.set_function("get_mouse_position", &GetMousePosition);
        module.set_function("is_mouse_button_pressed", &IsMouseButtonPressed);
        module.set_function("is_mouse_button_released", &IsMouseButtonReleased);
        module.set_function("ist_mouse_button_down", &IsMouseButtonDown);
        module.set_function("is_mouse_button_up", &IsMouseButtonUp);
        module.set_function("load_font", &LoadFont);
        module.set_function("load_image", &LoadImage);
        module.set_function("load_image_from_memory", &LoadImageFromMemory);
        module.set_function("get_codepoint", &GetCodepoint);
        module.set_function("set_exit_key", &SetExitKey);
        module.set_function("get_key_pressed", &GetKeyPressed);
        module.set_function("is_key_pressed", &IsKeyPressed);
        module.set_function("is_key_released", &IsKeyReleased);
        module.set_function("is_key_down", &IsKeyDown);
        module.set_function("is_key_up", &IsKeyUp);
        module.set_function("is_cursor_hidden", &IsCursorHidden);
        module.set_function("hide_cursor", &HideCursor);
        module.set_function("show_cursor", &ShowCursor);
        module.set_function("set_target_fps", &SetTargetFPS);
        module.set_function("get_fps", &GetFPS);
        module.set_function("get_frame_time", &GetFrameTime);
        module.set_function("get_clipboard_text", &GetClipboardText);
        module.set_function("set_clipboard_text", &SetClipboardText);
        module.set_function("get_char_pressed", &GetCharPressed);
        module.set_function("get_monitor_count", &GetMonitorCount);
        module.set_function("get_current_monitor", &GetCurrentMonitor);
        module.set_function("get_monitor_name", &GetMonitorName);
        module.set_function("get_monitor_width", &GetMonitorWidth);
        module.set_function("get_monitor_height", &GetMonitorHeight);
        module.set_function("get_monitor_x", &GetMasterVolume);
        module.set_function("draw_text", DrawText);
        module.set_function("draw_text_ex", DrawTextEx);
        module.set_function("measure_text", MeasureText);
        module.set_function("text_format", TextFormat);
        module.set_function("text_split", TextSplit);
        module.set_function("text_join", TextJoin);
        module.set_function("text_length", TextLength);
        module.set_function("measure_text_ex", MeasureTextEx);



    }

    void RaylibModule::init()
    {
        InitWindow(800, 600, "Raylib Module");
        SetTargetFPS(60);
    }

    void RaylibModule::shutdown()
    {
        for (auto& window : windows_)
        {
            window.reset();
        }
        CloseWindow();
    }

}

