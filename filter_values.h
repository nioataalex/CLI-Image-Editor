#define KERNEL 3
const double edge[KERNEL][KERNEL] = {{-1, -1, -1},
{-1, 8, -1},
{-1, -1, -1}};

const double sharpen[KERNEL][KERNEL] = {{0, -1, 0},
{-1, 5, -1},
{0, -1, 0}};

const double blur[KERNEL][KERNEL] = {{1.0 / 9, 1.0 / 9, 1.0 / 9},
{1.0 / 9, 1.0 / 9, 1.0 / 9},
{1.0 / 9, 1.0 / 9, 1.0 / 9}};

const double gaussian_blur[KERNEL][KERNEL] = {{0.0625, 0.125, 0.0625},
{0.125, 0.25, 0.125},
{0.0625, 0.125, 0.0625}};

