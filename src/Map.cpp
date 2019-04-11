#include "Map.h"
#include "utilities.h"

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
    //TODO: maybe generate values at some grid points, and interpolate between them?
    //aim is to have smooth variation in noise
    for(int i=0; i<columns; i++){
        for(int j=0; j<rows; j++){
            tiles[i][j].value = ((1.0f * rand()) / RAND_MAX) * 255.0f;
        }
    }
}

float Map::tile_value_at(float x, float y){
    int c = floor((x * columns) / screenW);
    int r = floor((y * rows) / screenH);

    // cout << "(" << c << ", " << r << "): " << tiles[c][r].value << "\n";

    return tiles[c][r].value;
}

void Map::decrease_tile_value_at(std::pair<double, double> coords, double delta){
    int c = floor((coords.first * columns) / screenW);
    int r = floor((coords.second * rows) / screenH);

    tiles[c][r].value = clampValF(tiles[c][r].value - delta, 255.0);
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
            ofDrawRectangle(tiles[i][j].X_topleft,tiles[i][j].Y_topleft,0,width,height);
            ofPath pathB;
                pathB.moveTo(tiles[i][j].X_topleft,tiles[i][j].Y_topleft);
                pathB.lineTo(tiles[i][j].X_topleft,tiles[i][j].Y_topleft+height);
                pathB.lineTo(tiles[i][j].X_topleft+width,tiles[i][j].Y_topleft+height);
                pathB.lineTo(tiles[i][j].X_topleft+width,tiles[i][j].Y_topleft);
                pathB.close();
                pathB.setStrokeColor(ofColor(0,0,0));
                pathB.setFilled(false);
                pathB.setStrokeWidth(3);
                pathB.draw();
            ofPath pathW;
                pathW.moveTo(tiles[i][j].X_topleft,tiles[i][j].Y_topleft);
                pathW.lineTo(tiles[i][j].X_topleft,tiles[i][j].Y_topleft+height);
                pathW.lineTo(tiles[i][j].X_topleft+height,tiles[i][j].Y_topleft+height);
                pathW.lineTo(tiles[i][j].X_topleft+height,tiles[i][j].Y_topleft);
                pathW.close();
                pathW.setStrokeColor(ofColor(255,255,255));
                pathW.setFilled(false);
                pathW.setStrokeWidth(1.5);
                pathW.draw();
        }
    }
}
