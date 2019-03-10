#include "Map.h"

void Map::init(int r, int c, int screenW, int screenH){
    rows = r;
    columns = c;

    printf("rows, columns set\n");

    //assume screen size is constant for now, maybe add event listener later

    width = (1.0 * screenW) / columns;
    height = (1.0 * screenH) / rows;

    printf("width and height calculated\n");

    for(int i=0; i<columns; i++){
        printf("inside outer loop\n");
        printf("before inner loop, i=%d\n", i);
        for(int j=0; j<rows; j++){
            //set all to 100 for now;
            tile t;
            t.value = 255.0f * (1.0f * i + j) / (rows + columns);
            t.X_topleft = (1.0f * i * screenW ) / columns;
            t.Y_topleft = (1.0f * j * screenH) / rows;

            tiles[i].push_back(t);
        }
    }
}

//update the tiles
void update(float dt, float screenW, float screenH){
    //nothing right now
}

void Map::draw(){
    for(int i=0; i<columns; i++){
        for(int j=0; j<rows; j++){
            ofSetColor(tiles[i][j].value);
            ofDrawRectangle(
                    tiles[i][j].X_topleft,
                    tiles[i][j].Y_topleft,
                    5,
                    width,
                    height
                );
        }
    }
}
