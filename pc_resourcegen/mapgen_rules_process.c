
typedef struct {
    int size;
    struct { int image, depth; bool collision; } panel[PANEL_SEGMENTS_IN_DATA];
} mapgen_panel_container;



typedef struct {
    int r, g, b;
    void (*func)(mapgen_panel_container*, int, int);
} mapgen_rule;

char hexchar(int n){
    return n + (n<10 ? '0':'a'-10);
}

void format_panel(char *target, mapgen_panel_container *cont, int adress){
    
    int point=0, value;
    
    // 画像番号
    for(int i=0; i<PANEL_SEGMENTS_IN_DATA; i++){
        value = cont[adress].panel[i].image;
        for(int j=0; j<3; j++){
            int n = value%16;
            target[point++] = hexchar(n);
            value /= 16;
        }

        value = cont[adress].panel[i].depth;
        for(int j=0; j<2; j++){
            int n = value%16;
            target[point++] = hexchar(n);
            value /= 16;
        }
        target[point++] = hexchar(cont[adress].panel[i].collision);
        target[point++] = ',';
    }

    while(++point < PANEL_DATA_SIZE){
        target[point] = '0';
    }
    
}

void container_insert(mapgen_panel_container *cont, int x, int y, int image, int depth, bool collision){
    cont[y*image_width+x].panel[cont[y*image_width+x].size].image = image;
    cont[y*image_width+x].panel[cont[y*image_width+x].size].depth = depth;
    cont[y*image_width+x].panel[cont[y*image_width+x].size].collision = collision;
    cont[y*image_width+x].size++;
}


// quoted from : https://it-ojisan.tokyo/c-str-reverse/
void reverse(char* str){
	int size = strlen(str);
	int i,j;
	char tmp = {0};
	
	for(i = 0, j = size - 1; i < size / 2; i++, j--){
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
	return;	
}