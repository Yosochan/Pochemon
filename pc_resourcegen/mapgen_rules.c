
#define RULE_ARG(C,X,Y) mapgen_panel_container* C, int X, int Y
#define RULE_ARG_P RULE_ARG(cont, x, y);
#define RULES_NUM 5

void rule_119_181_133(RULE_ARG_P); // 森
void rule_243_255_195(RULE_ARG_P); // 平原
void rule_157_221_225(RULE_ARG_P); // 水
void rule_255_229_147(RULE_ARG_P); // 道
void rule_181_227_167(RULE_ARG_P); // 草原
void rule_otherwise  (RULE_ARG_P); // 上記以外

mapgen_rule rules[RULES_NUM] = {
    {119, 181, 133, rule_119_181_133},
    {243, 255, 195, rule_243_255_195},
    {157, 221, 225, rule_157_221_225},
    {255, 229, 147, rule_255_229_147},
    {181, 227, 167, rule_181_227_167}
};

void rule_119_181_133(RULE_ARG(cont, x, y)){ // 森
    if(y != 0){
        panel_container_insert(cont, x, y-1, 0x050, 0x06, 0);
    }
    panel_container_insert(cont, x, y  , 0x051, 0x05, 0);
    panel_container_insert(cont, x, y  , 0x076, 0x00, 1);
}
void rule_243_255_195(RULE_ARG(cont, x, y)){ // 平原
    panel_container_insert(cont, x, y, 0x076, 0x00, 0);
}
void rule_157_221_225(RULE_ARG(cont, x, y)){ // 水
    panel_container_insert(cont, x, y, 0x041, 0x00, 0);
}
void rule_255_229_147(RULE_ARG(cont, x, y)){ // 道

    panel_container_insert_9(cont, x, y, 0x01, 0,
        0x005, 0x015, 0x025,
        0x006, 0x016, 0x026,
        0x007, 0x017, 0x027,
        0x013, 0x003,
        0x004, 0x014
        );
    

}
void rule_181_227_167(RULE_ARG(cont, x, y)){ // 草原
    panel_container_insert(cont, x, y, 0x040, 0x03, 0);
    panel_container_insert(cont, x, y, 0x030, 0x02, 0);
    panel_container_insert(cont, x, y, 0x076, 0x00, 0);
}
void rule_otherwise(RULE_ARG(cont, x, y)){
    panel_container_insert(cont, x, y, 0x000, 0x00, 1);
}

