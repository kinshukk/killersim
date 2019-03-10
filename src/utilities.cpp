float clampVal(float val, int max){
    if(val > max){
        return val - max;
    }else if(val < 0){
        return val + max;
    }else{
        return val;
    }
}
