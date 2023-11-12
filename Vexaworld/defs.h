#pragma once
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr int CHUNK_SIZE = 16;
constexpr int BLOCK_SIZE = 48;
constexpr int CHUNK_SIZE_PIXELS = CHUNK_SIZE * BLOCK_SIZE;

constexpr int PLAYER_WIDTH = 24;
constexpr int PLAYER_HEIGHT = (int)(PLAYER_WIDTH * 1.5);

constexpr int WINDOW_TITLEBAR_HEIGHT = 24;

constexpr int HOTBAR_PADDING = 4;
constexpr int HOTBAR_BLOCKCOUNT = 10;
constexpr int HOTBAR_WIDTH = HOTBAR_PADDING * (HOTBAR_BLOCKCOUNT + 1) + BLOCK_SIZE * HOTBAR_BLOCKCOUNT;

struct Dimensions {
    int width, height;
};

struct Point {
    int x, y;
};