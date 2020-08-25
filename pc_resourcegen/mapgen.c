

#define PANEL_DATA_SIZE 25
#define PANEL_SEGMENTS_IN_DATA 3

#define PANEL_VOID 0x00

#include "png_process.c"
#include "mapgen_rules_process.c"
#include "mapgen_rules.c"

FILE *map_file;

// MAPDATAを作成/保存する。
int mapgen_process();

// メイン関数。
int main(){

    image_file = fopen("mapdata.png", "r");
    map_file   = fopen("../docs/resources/mapdata.pcmap", "w");

    if(image_file == NULL || map_file == NULL){
        printf("Failed to open file.\n");
        return 0;
    }

    // mapdata.pngを読み込む。
    read_process();
    mapgen_process();
    free_process();

    fclose(map_file);
}


int mapgen_process(){

    int r, g, b;
    mapgen_panel_container cont[image_width*image_height];
    
    for (int i=0; i<image_width*image_height; i++){
        cont[i].size = 0;
        for(int j=0; j<PANEL_SEGMENTS_IN_DATA; j++){
            cont[i].panel[j].image = 0;
            cont[i].panel[j].depth = 0;
            cont[i].panel[j].collision = 0;
        }
    }

    for (int iy=0; iy<image_height; iy++){
        for (int ix=0; ix<image_width; ix++){

            // image_data からrgb値を取得。
            r = image_data[iy][ix*4+0];
            g = image_data[iy][ix*4+1];
            b = image_data[iy][ix*4+2];

            // 全てのrulesを検索し、適合したらそれに応じたパネル。しなければrule_otherwiseで定義したパネル。
            for(int ir=0; ir<=RULES_NUM; ir++){
                if(
                    ir != RULES_NUM  &&
                    r == rules[ir].r &&
                    g == rules[ir].g &&
                    b == rules[ir].b
                    ){
                    rules[ir].func(cont, ix, iy);
                    break;
                }

                if(ir == RULES_NUM){
                    rule_otherwise(cont, ix, iy);
                    break;
                }
            }
        }
    }


    // 書き込む。
    char code[PANEL_DATA_SIZE];

    for (int iy=0; iy<image_height; iy++){
        for (int ix=0; ix<image_width; ix++){
            format_panel(code, cont, iy*image_width+ix);
            reverse(code);
            fprintf(map_file, "%s|", code);
        }
        fprintf(map_file, "\n");
    }
    
}

