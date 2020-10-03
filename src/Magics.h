struct Magics {
    Magics(const int h, const int w) :height{h}, width{w},
    mid_wall{width / 2}, mid_height{height / 2},
    right_most{width - 3}, left_most{2},
    up_most{3}, down_most{height-4}
    {}

    const int width, height,
    mid_wall,
    mid_height,
    right_most,
    left_most,
    up_most,
    down_most;
};

struct Config {
    int ball_speed;
    char wallTexture;
};