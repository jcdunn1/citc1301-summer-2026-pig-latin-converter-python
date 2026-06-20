/* echo_input.h  – drop in repo, compile with  -include echo_input.h  */
#pragma once
#include <iostream>          // std::cin
#include <streambuf>
#include <unistd.h>          // write()

class echo_buf : public std::streambuf {
    std::streambuf* src_;
    int pending = traits_type::eof();   // char that was already echoed in peek
protected:
    /* ---------- peek without consume ---------- */
    int_type underflow() override {
        int_type ch = src_->sgetc();
        if (ch != traits_type::eof() && ch != pending) {
            ::write(STDOUT_FILENO, &ch, 1);   // echo once
            pending = ch;                     // mark as echoed
        }
        return ch;
    }
    /* ---------- consume 1 char ---------- */
    int_type uflow() override {
        int_type ch = src_->sbumpc();
        if (ch != traits_type::eof()) {
            if (ch == pending)                // already echoed during peek
                pending = traits_type::eof(); // clear the cache
            else
                ::write(STDOUT_FILENO, &ch, 1);
        }
        return ch;
    }
    /* ---------- bulk consume ---------- */
    std::streamsize xsgetn(char_type* s, std::streamsize n) override {
        std::streamsize got = src_->sgetn(s, n);
        if (got > 0) {
            size_t start = 0;
            if (pending != traits_type::eof() && s[0] == pending) {
                pending = traits_type::eof(); // first byte was already echoed
                start = 1;
            }
            if (got > static_cast<std::streamsize>(start))
                ::write(STDOUT_FILENO, s + start,
                        static_cast<size_t>(got - start));
        }
        return got;
    }
public:
    explicit echo_buf(std::streambuf* src) : src_(src) {}
};

/* install before main() */
struct _echo_installer {
    echo_buf buf;
    _echo_installer() : buf(std::cin.rdbuf()) { std::cin.rdbuf(&buf); }
} _echo_installer_instance;

inline _echo_installer _echo_installer_instance;