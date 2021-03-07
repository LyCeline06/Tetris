#include"../include/Shape.h"

Shape transpose(Shape s)
{
    Shape s2 =s;
    for (int i=0;i<s.size;++i){
        for (int j=0;j<s.size;++j)
            s2.matrix[i][j] = s.matrix[j][i];
		}

    return s2;
}

Shape miror(Shape s)
{
    Shape s2=s;
    for (int i=0;i<s.size;++i){
        for (int j=0;j<s.size;++j)
            s2.matrix[i][j] = s.matrix[i][s.size-j-1];
		}
    return s2;
}
int counter = 0;
Shape rotate(Shape s)
{
    counter++;    
    printf("did rotate %d\n",counter);
    return miror(transpose(s));

}
