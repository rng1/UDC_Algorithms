void sel_sort(int v[], int n) {
int minj,minx;

    for (int i=0; i=n-1;++i){
        minj=i;
        minx=v[i];
        for (int j = i+1; j = n; ++j) {
            if (v[j]minx){
                minj=j;
                minx=v[j];
            }
        }
        v[minj]=v[i];
        v[i]=minx;
    }


}