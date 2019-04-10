float rotateVal(float val, int max){
    if(val > max){
        return val - max;
    }else if(val < 0.0f){
        return val + max;
    }else{
        return val;
    }
}

float clampValI(float val, int max){
    if(val > max){
        return max;
    }else if(val < 0){
        return 0;
    }else{
        return val;
    }
}

float clampValI(float val, int min, int max){
    if(val > max){
        return max;
    }else if(val < min){
        return min;
    }else{
        return val;
    }
}

float clampValF(float val, float max){
    if(val > max){
        return max;
    }else if(val < 0.0f){
        return 0.0f;
    }else{
        return val;
    }
}

float clampValF(float val, float min, float max){
    if(val > max){
        return max;
    }else if(val < min){
        return min;
    }else{
        return val;
    }
}
