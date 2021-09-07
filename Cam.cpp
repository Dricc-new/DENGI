#include "../include/DENGI/Cam.h"
#include "../include/DENGI/dengi.h"

namespace dengi{
    DENGIDEF Cam::Cam(){
        R[0]  = 1.0; R[1]  = 0.0; R[2]  = 0.0; R[3]  = 0.0;
        R[4]  = 0.0; R[5]  = 1.0; R[6]  = 0.0; R[7]  = 0.0;
        R[8]  = 0.0; R[9]  = 0.0; R[10] = 1.0; R[11] = 0.0;
        R[12] = 0.0; R[13] = 0.0; R[14] = 0.0; R[15] = 1.0;
        T[0]  = 1.0; T[1]  = 0.0; T[2]  = 0.0; T[3]  = 0.0;
        T[4]  = 0.0; T[5]  = 1.0; T[6]  = 0.0; T[7]  = 0.0;
        T[8]  = 0.0; T[9]  = 0.0; T[10] = 1.0; T[11] = 0.0;
        T[12] = 0.0; T[13] = 0.0; T[14] = 0.0; T[15] = 1.0;
    }

    void DENGIDEF Cam::SetPos(float x, float y, float z){
        T[12]  = -x;
        T[13]  = -y;
        T[14] = -z;
        LookAt = R;
        LookAt *= T;
    }

    void DENGIDEF Cam::Use(){
        UseViewMatrix(LookAt.get());
    }
}
