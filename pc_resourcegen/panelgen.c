

#define PANEL_WH 8

#include "png_process.c"

png_structp panel_image;
png_infop   panel_info;
png_bytep   row;

// PANELDATAを作成/保存する。
int panelgen_process(int, int);

int main(){
    image_file = fopen("paneldata.png", "r");

    if(image_file == NULL){
        printf("Failed to open file.\n");
        return 0;
    }

    // mapdata.pngを読み込む。
    read_process();
    for(int iy=0; iy<image_height; iy += PANEL_WH){
        for(int ix=0; ix<image_width; ix += PANEL_WH){
            panelgen_process(ix, iy);
        }
    }
    
    png_write_end(panel_image, NULL);
    png_free_data(panel_image, panel_info, PNG_FREE_ALL, -1);
    png_destroy_write_struct(&panel_image, (png_infopp)NULL);
    free(row);

    free_process();   
}

int panelgen_process(int x, int y){
    
    char file_name[256] = {'\0'};
    sprintf(file_name, "../resources/panel/0_%d_%d.png", x/PANEL_WH, y/PANEL_WH);
    FILE *target_file = fopen(file_name, "w");

    if(target_file == NULL){
        printf("Failed to open file.\n");
        return 0;
    }

    panel_image = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    panel_info = png_create_info_struct(panel_image);
    png_init_io(panel_image, target_file);
    
    png_set_IHDR(panel_image, panel_info, PANEL_WH, PANEL_WH,
            8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(panel_image, panel_info);

    row = (png_bytep) malloc(4 * PANEL_WH * sizeof(png_byte));

    for (int iy=0 ; iy<PANEL_WH; iy++) {
        for (int ix=0 ; ix<PANEL_WH; ix++) {

            row[ix*4+0] = image_data[y+iy][(x+ix)*4+0];
            row[ix*4+1] = image_data[y+iy][(x+ix)*4+1];
            row[ix*4+2] = image_data[y+iy][(x+ix)*4+2];
            row[ix*4+3] = image_data[y+iy][(x+ix)*4+3];
            
        }
        png_write_row(panel_image, row);
    }

    fclose(target_file);

}