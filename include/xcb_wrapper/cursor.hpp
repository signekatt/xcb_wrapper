// Copyright(c) 2019-present, Anton Lilja.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include "xcb_wrapper/common.hpp"
#include "xcb_wrapper/connection.hpp"
#include "xcb_wrapper/screen.hpp"
#include "xcb_wrapper/window.hpp"
#include "xcb_wrapper/drawable.hpp"

#include <optional>

namespace xcbw {
    void warp_pointer(const connection_t& c, std::optional<window_t> src_window,
                      std::optional<window_t> dst_window, point_t<int16_t> src_pos,
                      point_t<int16_t> src_size, point_t<int16_t> dst_pos);

    class cursor_context_t {
    public:
        cursor_context_t(const connection_t& c, screen_t s);
        ~cursor_context_t();

        cursor_context_t(const cursor_context_t& o) = delete;
        cursor_context_t& operator=(const cursor_context_t& o) = delete;

        cursor_context_t(cursor_context_t&& o) noexcept = default;
        cursor_context_t& operator=(cursor_context_t&& o) noexcept = default;

        inline operator void*() const { return m_pointer; }

    private:
        void* m_pointer;
    };

    class cursor_t {
    public:
        explicit cursor_t(uint32_t id) : m_id(id) {}
        cursor_t(const connection_t& c, pixmap_t source, pixmap_t mask, uint16_t fore_red,
                 uint16_t fore_green, uint16_t fore_blue, uint16_t back_red, uint16_t back_green,
                 uint16_t back_blue, uint16_t x, uint16_t y);

        cursor_t(const connection_t& c, pixmap_t source, pixmap_t mask, uint16_t fore_red,
                 uint16_t fore_green, uint16_t fore_blue, uint16_t back_red, uint16_t back_green,
                 uint16_t back_blue, point_t<uint16_t> pos)
            : cursor_t(c, source, mask, fore_red, fore_blue, fore_green, back_red, back_green,
                       back_blue, pos.x, pos.y) {}

        cursor_t(const connection_t& c, const cursor_context_t& context, const char* name);

        void free_cursor(const connection_t& c);

        inline operator uint32_t() const { return m_id; }

    private:
        uint32_t m_id = 0;
    };
} // namespace xcbw