#include "Map.h"
#include "utilities.h"
#include "Simplex.h"

void Map::init(int r, int c, int screenWidth, int screenHeight){
    //random seed
    srand(42);

    delta_food_per_sec = 1;

    screenW = screenWidth;
    screenH = screenHeight;

    rows = r;
    columns = c;

    //assume screen size is constant for now, maybe add event listener later

    width = (1.0 * screenW) / columns;
    height = (1.0 * screenH) / rows;

    for(int i=0; i<columns; i++){
        for(int j=0; j<rows; j++){
            //set all to 100 for now;
            tile t;
            t.X_topleft = (1.0f * i * screenW ) / columns;
            t.Y_topleft = (1.0f * j * screenH) / rows;

            tiles[i].push_back(t);
            // cout <<"i " << i << " j " << j << endl;
        }
    }

    regenerate_values();
}


void Map::regenerate_values(){
    //TODO: add some averaging with adjacent tiles to 'smooth' out randomness
    //ideal would be to have some coherent noise (Simplex perhaps)

    for(int i=0; i<columns; i++){
        for(int j=0; j<rows; j++){
            tiles[i][j].value = SimplexNoise::noisegen((double)i,(double)j);
        }
    }
}

tile Map::tile_value_at(float x, float y){
    int c = floor((x * columns) / screenW);
    int r = floor((y * rows) / screenH);

    // cout << "(" << c << ", " << r << "): " << tiles[c][r].value << "\n";

    return tiles[c][r];
}

void Map::increase_delta_food(){
    delta_food_per_sec = clampValI(delta_food_per_sec + 1, 50);
}

void Map::decrease_delta_food(){
    delta_food_per_sec = clampValI(delta_food_per_sec - 1, 50);
}

//update the tiles
void Map::update(float dt, float screenW, float screenH){
    for(int i=0; i<columns; i++){
        for(int j=0; j<rows; j++){
            //make sure value is between 0 and 255
            tiles[i][j].value = clampValF(tiles[i][j].value + (delta_food_per_sec * dt), 255.0f);
        }
    }
}

//TODO: draw black, white concentric borders as well
//so that we can distinguish neighboring cells that are the same color
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
