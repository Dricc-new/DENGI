#include "../include/DENGI/Matrix.h"
#include <math.h>

namespace dengi{
    DENGIDEF Matrix::Matrix(){
        M[0]  = 1.0; M[1]  = 0.0; M[2]  = 0.0; M[3]  = 0.0;
        M[4]  = 0.0; M[5]  = 1.0; M[6]  = 0.0; M[7]  = 0.0;
        M[8]  = 0.0; M[9]  = 0.0; M[10] = 1.0; M[11] = 0.0;
        M[12] = 0.0; M[13] = 0.0; M[14] = 0.0; M[15] = 1.0;
    }

    float* DENGIDEF Matrix::operator*(float *m){
        float *Temp =  new float[16];
        float sum;
        for(int row = 0; row < 4; row++){
            for(int col = 0; col < 4; col++){
                sum = 0;
                for(int k = 0; k < 4; k++){
                    sum += M[row*4+k]*m[k*4+col];
                }
                Temp[ row*4+col] = sum;
            }
        }
        return Temp;
    }

    void DENGIDEF Matrix::operator=(float *m){
        for(int i = 0; i < 16; i++){
            M[i] = m[i];
        }
    }
    void DENGIDEF Matrix::operator*=(float *m){
        float *Temp = this->operator*(m);
        this->operator=(Temp);
        delete Temp;
    }

    void DENGIDEF Matrix::translate(float x, float y, float z){
        float Temp[16] = {  1.0, 0.0, 0.0, x,
                            0.0, 1.0, 0.0, y,
                            0.0, 0.0, 1.0, z,
                            0.0, 0.0, 0.0, 1.0};
        this->operator*=(Temp);
    }

    void DENGIDEF Matrix::rotate(float angle,float x, float y, float z){
        float Cos = cos(angle*3.14);
        float Sin = sin(angle*3.14);
        float Cosu = 1-Cos;
        float XY = x*y;
        float YZ = z*y;
        float XZ = x*z;
        float Temp[16] = {  Cos+(x*x*Cosu), (XY*Cosu)-(z*Sin), (XZ*Cosu)+(y*Sin), 0.0,
                            (XY*Cosu)+z*Sin, Cos+(y*y*Cosu), (YZ*Cosu)-(x*Sin), 0.0,
                            (XZ*Cosu)-y*Sin, (YZ*Cosu)-(x*Sin), Cos-(z*z*Cosu), 0.0,
                            0.0, 0.0, 0.0, 1.0};
        this->operator*=(Temp);
    }

    float* DENGIDEF Matrix::get(){
        return M;
    }
}
