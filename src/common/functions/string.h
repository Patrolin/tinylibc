internal void print(String str) {
    osPrint(str.msg, str.count);
}

// cstr
internal uint cstrCount(const char* start) {
    const char* end = start;
    while (*end != 0) {
        end++;
    }
    return end - start;
}
internal String sprint(const char* msg) { // TODO: should this talloc()?
    return String{ (u8*)msg, cstrCount(msg) };
}
internal void print(const char* msg) {
    print(sprint(msg));
}

// string builder
#include <initializer_list>
internal String sprint(std::initializer_list<String> strings) {
    uint count = 0;
    u8* buffer = (u8*)talloc(count);
    u8* curr = buffer;
    for (auto str = strings.begin(); str != strings.end(); str++) {
        count += str->count;
        for (uint j = 0; j < str->count; j++)
            *(curr++) = str->msg[j];
    }
    return String{ buffer, count };
}
internal void print(std::initializer_list<String> strings) {
    print(sprint(strings));
}
internal void printline(std::initializer_list<String> strings) {
    print({sprint(strings), sprint("\n")});
}

// generic print
template <typename T>
internal void print(T value) {
    print(sprint(value));
}
internal String sprint(u64 number); // WSL is cursed
template <typename T>
internal void printline(T value) {
    print({sprint(value), sprint("\n")});
}
internal void printline(String value) {
    print({value, sprint("\n")});
}
