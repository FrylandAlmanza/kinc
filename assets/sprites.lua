sprite_count = 8;

SPR_LINK = 0;
SPR_WALL_NW = 1;
SPR_WALL_N = 2;
SPR_WALL_NE = 3;
SPR_WALL_SW = 4;
SPR_WALL_S = 5;
SPR_WALL_SE = 6;
SPR_GROUND = 7;

sprites = {}
sprites[SPR_LINK] = {x = 0, y = 0, w = 16, h = 16}
sprites[SPR_WALL_NW] = {x = 32, y = 0, w = 16, h = 16}
sprites[SPR_WALL_N] = {x = 48, y = 0, w = 16, h = 16}
sprites[SPR_WALL_NE] = {x = 64, y = 0, w = 16, h = 16}
sprites[SPR_WALL_SW] = {x = 32, y = 16, w = 16, h = 16}
sprites[SPR_WALL_S] = {x = 48, y = 16, w = 16, h = 16}
sprites[SPR_WALL_SE] = {x = 64, y = 16, w = 16, h = 16}
sprites[SPR_GROUND] = {x = 32, y = 32, w = 16, h = 16}
