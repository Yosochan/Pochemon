
#define RULE_ARG(C,X,Y) mapgen_panel_container* C, int X, int Y
#define RULE_ARG_P RULE_ARG(cont, x, y);
#define RULES_NUM 5

void rule_119_181_133(RULE_ARG_P); // 森
void rule_243_255_195(RULE_ARG_P); // 平原
void rule_157_221_225(RULE_ARG_P); // 水
void rule_225_229_147(RULE_ARG_P); // 道
void rule_181_227_167(RULE_ARG_P); // 草原
void rule_otherwise  (RULE_ARG_P); // 上記以外

mapgen_rule rules[RULES_NUM] = {
    {119, 181, 133, rule_119_181_133},
    {243, 255, 195, rule_243_255_195},
    {157, 221, 225, rule_157_221_225},
    {225, 229, 147, rule_225_229_147},
    {181, 227, 167, rule_181_227_167}
};

void rule_119_181_133(RULE_ARG(cont, x, y)){ // 森
    container_insert(cont, x, y, 0x040, 0x02, 0);
    container_insert(cont, x, y, 0x030, 0x01, 0);
    container_insert(cont, x, y, 0x076, 0x00, 1);
}
void rule_243_255_195(RULE_ARG(cont, x, y)){ // 平原
    container_insert(cont, x, y, 0x076, 0x00, 0);
}
void rule_157_221_225(RULE_ARG(cont, x, y)){ // 水
    container_insert(cont, x, y, 0x041, 0x00, 0);
}
void rule_225_229_147(RULE_ARG(cont, x, y)){ // 道
    container_insert(cont, x, y, 0x016, 0x00, 0);
}
void rule_181_227_167(RULE_ARG(cont, x, y)){ // 草原
    container_insert(cont, x, y, 0x040, 0x02, 0);
    container_insert(cont, x, y, 0x030, 0x01, 0);
    container_insert(cont, x, y, 0x076, 0x00, 0);
}
void rule_otherwise(RULE_ARG(cont, x, y)){
    container_insert(cont, x, y, 0x000, 0x00, 1);
}

