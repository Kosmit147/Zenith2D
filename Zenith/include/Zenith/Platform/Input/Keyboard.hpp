#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <array>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

enum class Key : i16
{
    // keep this list consistent with the array below

    // copied from SFML scancodes
    Unknown = -1,       // Represents any scancode not present in this enum
    A = 0,              // Keyboard a and A key
    B,                  // Keyboard b and B key
    C,                  // Keyboard c and C key
    D,                  // Keyboard d and D key
    E,                  // Keyboard e and E key
    F,                  // Keyboard f and F key
    G,                  // Keyboard g and G key
    H,                  // Keyboard h and H key
    I,                  // Keyboard i and I key
    J,                  // Keyboard j and J key
    K,                  // Keyboard k and K key
    L,                  // Keyboard l and L key
    M,                  // Keyboard m and M key
    N,                  // Keyboard n and N key
    O,                  // Keyboard o and O key
    P,                  // Keyboard p and P key
    Q,                  // Keyboard q and Q key
    R,                  // Keyboard r and R key
    S,                  // Keyboard s and S key
    T,                  // Keyboard t and T key
    U,                  // Keyboard u and U key
    V,                  // Keyboard v and V key
    W,                  // Keyboard w and W key
    X,                  // Keyboard x and X key
    Y,                  // Keyboard y and Y key
    Z,                  // Keyboard z and Z key
    Num1,               // Keyboard 1 and ! key
    Num2,               // Keyboard 2 and @ key
    Num3,               // Keyboard 3 and # key
    Num4,               // Keyboard 4 and $ key
    Num5,               // Keyboard 5 and % key
    Num6,               // Keyboard 6 and ^ key
    Num7,               // Keyboard 7 and & key
    Num8,               // Keyboard 8 and * key
    Num9,               // Keyboard 9 and ) key
    Num0,               // Keyboard 0 and ) key
    Enter,              // Keyboard Enter/Return key
    Escape,             // Keyboard Escape key
    Backspace,          // Keyboard Backspace key
    Tab,                // Keyboard Tab key
    Space,              // Keyboard Space key
    Hyphen,             // Keyboard - and _ key
    Equal,              // Keyboard = and +
    LBracket,           // Keyboard [ and { key
    RBracket,           // Keyboard ] and } key
    Backslash,          // Keyboard \ and | key OR various keys for Non-US keyboards
    Semicolon,          // Keyboard ; and : key
    Apostrophe,         // Keyboard ' and " key
    Grave,              // Keyboard ` and ~ key
    Comma,              // Keyboard , and < key
    Period,             // Keyboard . and > key
    Slash,              // Keyboard / and ? key
    F1,                 // Keyboard F1 key
    F2,                 // Keyboard F2 key
    F3,                 // Keyboard F3 key
    F4,                 // Keyboard F4 key
    F5,                 // Keyboard F5 key
    F6,                 // Keyboard F6 key
    F7,                 // Keyboard F7 key
    F8,                 // Keyboard F8 key
    F9,                 // Keyboard F9 key
    F10,                // Keyboard F10 key
    F11,                // Keyboard F11 key
    F12,                // Keyboard F12 key
    F13,                // Keyboard F13 key
    F14,                // Keyboard F14 key
    F15,                // Keyboard F15 key
    F16,                // Keyboard F16 key
    F17,                // Keyboard F17 key
    F18,                // Keyboard F18 key
    F19,                // Keyboard F19 key
    F20,                // Keyboard F20 key
    F21,                // Keyboard F21 key
    F22,                // Keyboard F22 key
    F23,                // Keyboard F23 key
    F24,                // Keyboard F24 key
    CapsLock,           // Keyboard Caps %Lock key
    PrintScreen,        // Keyboard Print Screen key
    ScrollLock,         // Keyboard Scroll %Lock key
    Pause,              // Keyboard Pause key
    Insert,             // Keyboard Insert key
    Home,               // Keyboard Home key
    PageUp,             // Keyboard Page Up key
    Delete,             // Keyboard Delete Forward key
    End,                // Keyboard End key
    PageDown,           // Keyboard Page Down key
    Right,              // Keyboard Right Arrow key
    Left,               // Keyboard Left Arrow key
    Down,               // Keyboard Down Arrow key
    Up,                 // Keyboard Up Arrow key
    NumLock,            // Keypad Num %Lock and Clear key
    NumpadDivide,       // Keypad / key
    NumpadMultiply,     // Keypad * key
    NumpadMinus,        // Keypad - key
    NumpadPlus,         // Keypad + key
    NumpadEqual,        // keypad = key
    NumpadEnter,        // Keypad Enter/Return key
    NumpadDecimal,      // Keypad . and Delete key
    Numpad1,            // Keypad 1 and End key
    Numpad2,            // Keypad 2 and Down Arrow key
    Numpad3,            // Keypad 3 and Page Down key
    Numpad4,            // Keypad 4 and Left Arrow key
    Numpad5,            // Keypad 5 key
    Numpad6,            // Keypad 6 and Right Arrow key
    Numpad7,            // Keypad 7 and Home key
    Numpad8,            // Keypad 8 and Up Arrow key
    Numpad9,            // Keypad 9 and Page Up key
    Numpad0,            // Keypad 0 and Insert key
    NonUsBackslash,     // Keyboard Non-US \ and | key
    Application,        // Keyboard Application key
    Execute,            // Keyboard Execute key
    ModeChange,         // Keyboard Mode Change key
    Help,               // Keyboard Help key
    Menu,               // Keyboard Menu key
    Select,             // Keyboard Select key
    Redo,               // Keyboard Redo key
    Undo,               // Keyboard Undo key
    Cut,                // Keyboard Cut key
    Copy,               // Keyboard Copy key
    Paste,              // Keyboard Paste key
    VolumeMute,         // Keyboard Volume Mute key
    VolumeUp,           // Keyboard Volume Up key
    VolumeDown,         // Keyboard Volume Down key
    MediaPlayPause,     // Keyboard Media Play Pause key
    MediaStop,          // Keyboard Media Stop key
    MediaNextTrack,     // Keyboard Media Next Track key
    MediaPreviousTrack, // Keyboard Media Previous Track key
    LControl,           // Keyboard Left Control key
    LShift,             // Keyboard Left Shift key
    LAlt,               // Keyboard Left Alt key
    LSystem,            // Keyboard Left System key
    RControl,           // Keyboard Right Control key
    RShift,             // Keyboard Right Shift key
    RAlt,               // Keyboard Right Alt key
    RSystem,            // Keyboard Right System key
    Back,               // Keyboard Back key
    Forward,            // Keyboard Forward key
    Refresh,            // Keyboard Refresh key
    Stop,               // Keyboard Stop key
    Search,             // Keyboard Search key
    Favorites,          // Keyboard Favorites key
    HomePage,           // Keyboard Home Page key
    LaunchApplication1, // Keyboard Launch Application 1 key
    LaunchApplication2, // Keyboard Launch Application 2 key
    LaunchMail,         // Keyboard Launch Mail key
    LaunchMediaSelect,  // Keyboard Launch Media Select key
};

inline constexpr std::array key_enumerations = {
    Key::Unknown,
    Key::A,
    Key::B,
    Key::C,
    Key::D,
    Key::E,
    Key::F,
    Key::G,
    Key::H,
    Key::I,
    Key::J,
    Key::K,
    Key::L,
    Key::M,
    Key::N,
    Key::O,
    Key::P,
    Key::Q,
    Key::R,
    Key::S,
    Key::T,
    Key::U,
    Key::V,
    Key::W,
    Key::X,
    Key::Y,
    Key::Z,
    Key::Num1,
    Key::Num2,
    Key::Num3,
    Key::Num4,
    Key::Num5,
    Key::Num6,
    Key::Num7,
    Key::Num8,
    Key::Num9,
    Key::Num0,
    Key::Enter,
    Key::Escape,
    Key::Backspace,
    Key::Tab,
    Key::Space,
    Key::Hyphen,
    Key::Equal,
    Key::LBracket,
    Key::RBracket,
    Key::Backslash,
    Key::Semicolon,
    Key::Apostrophe,
    Key::Grave,
    Key::Comma,
    Key::Period,
    Key::Slash,
    Key::F1,
    Key::F2,
    Key::F3,
    Key::F4,
    Key::F5,
    Key::F6,
    Key::F7,
    Key::F8,
    Key::F9,
    Key::F10,
    Key::F11,
    Key::F12,
    Key::F13,
    Key::F14,
    Key::F15,
    Key::F16,
    Key::F17,
    Key::F18,
    Key::F19,
    Key::F20,
    Key::F21,
    Key::F22,
    Key::F23,
    Key::F24,
    Key::CapsLock,
    Key::PrintScreen,
    Key::ScrollLock,
    Key::Pause,
    Key::Insert,
    Key::Home,
    Key::PageUp,
    Key::Delete,
    Key::End,
    Key::PageDown,
    Key::Right,
    Key::Left,
    Key::Down,
    Key::Up,
    Key::NumLock,
    Key::NumpadDivide,
    Key::NumpadMultiply,
    Key::NumpadMinus,
    Key::NumpadPlus,
    Key::NumpadEqual,
    Key::NumpadEnter,
    Key::NumpadDecimal,
    Key::Numpad1,
    Key::Numpad2,
    Key::Numpad3,
    Key::Numpad4,
    Key::Numpad5,
    Key::Numpad6,
    Key::Numpad7,
    Key::Numpad8,
    Key::Numpad9,
    Key::Numpad0,
    Key::NonUsBackslash,
    Key::Application,
    Key::Execute,
    Key::ModeChange,
    Key::Help,
    Key::Menu,
    Key::Select,
    Key::Redo,
    Key::Undo,
    Key::Cut,
    Key::Copy,
    Key::Paste,
    Key::VolumeMute,
    Key::VolumeUp,
    Key::VolumeDown,
    Key::MediaPlayPause,
    Key::MediaStop,
    Key::MediaNextTrack,
    Key::MediaPreviousTrack,
    Key::LControl,
    Key::LShift,
    Key::LAlt,
    Key::LSystem,
    Key::RControl,
    Key::RShift,
    Key::RAlt,
    Key::RSystem,
    Key::Back,
    Key::Forward,
    Key::Refresh,
    Key::Stop,
    Key::Search,
    Key::Favorites,
    Key::HomePage,
    Key::LaunchApplication1,
    Key::LaunchApplication2,
    Key::LaunchMail,
    Key::LaunchMediaSelect,
};

Key to_key(sf::Keyboard::Scancode code);
const char* to_string(Key key);

} // namespace zth
