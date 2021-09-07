#include "../include/DENGI/ModelWavefront.h"
#include "../include/DENGI/dengi.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <map>
#include "../include/DENGI/Image.h"
typedef std::map< string, unsigned int> mapAs;

namespace dengi{

    DENGIDEF WaveFront::WaveFront(){
        glGenVertexArrays(1,&Id);
        Mpos[0]  = 1.0;Mpos[1]  = 0.0;Mpos[2]  = 0.0;Mpos[3]  = 0.0;
        Mpos[4]  = 0.0;Mpos[5]  = 1.0;Mpos[6]  = 0.0;Mpos[7]  = 0.0;
        Mpos[8]  = 0.0;Mpos[9]  = 0.0;Mpos[10] = 1.0;Mpos[11] = 0.0;
        Mpos[12] = 0.0;Mpos[13] = 0.0;Mpos[14] = 0.0;Mpos[15] = 1.0;
        Mposs = Mpos;
    }

    int DENGIDEF WaveFront::LoadFromFile(char *src){

        unsigned int numVert;
        char type = 0;
        string buff;
        string temp;
        bool useMtl = false;
        unsigned int pos;
        unsigned int posf;
        vector<float> vertexs;
        vector<float> uvs;
        vector<float> normals;
        vector<int> faces;
        mapAs namesMat;
        string path = src;
        pos = path.rfind("/");
        if(pos!=(unsigned int)-1){
            path = path.substr(0,pos+1);
        }else{
            path.clear();
        }
            printf("hello");
        string command;
        ifstream file( src, std::ios::in );
        while(!file.eof()){
            file>>command;
            if(command=="#"){
                continue;
            }else if(command=="mtllib"){
                file>>srcMat;
                srcMat = path + srcMat;
                ifstream fileMat( srcMat, std::ios::in );
                string command2;
                string buff2;
                float r,g,b;
                Material *Mate = 0;
                while(!fileMat.eof()){
                    fileMat>>command2;
                    if(command2=="#"){
                        continue;
                    }else if(command2=="newmtl"){
                        if(Mate != 0){
                            materials.push_back(*Mate);
                            delete Mate;
                        }
                        fileMat>>buff2;
                        namesMat.insert( mapAs::value_type( buff2, materials.size() ) );
                        Mate = new Material;
                    }else if(command2=="Ka"){
                        fileMat>>r;
                        fileMat>>g;
                        fileMat>>b;
                        Mate->SetKa(r,g,b);
                    }else if(command2=="Kd"){
                        fileMat>>r;
                        fileMat>>g;
                        fileMat>>b;
                        Mate->SetKd(r,g,b);
                    }else if(command2=="Ks"){
                        fileMat>>r;
                        fileMat>>g;
                        fileMat>>b;
                        Mate->SetKs(r,g,b);
                    }else if(command2=="Ns"){
                        fileMat>>r;
                        Mate->SetNs(r);
                    }else if(command2=="d"){
                        fileMat>>r;
                        Mate->SetAlpha(r);
                    }else if(command2=="map_Kd"){
                        string srcMap_Kd;
                        fileMat>>srcMap_Kd;
                        srcMap_Kd = path + srcMap_Kd;
                        Mate->SetMap_Kd((char*)srcMap_Kd.c_str());
                    }
                    command2.clear();
                }
                if(Mate != 0){
                    materials.push_back(*Mate);
                    delete Mate;
                }
            }else if(command=="v"){
                std::getline(file,buff);
                posf = 0;
                while(pos = posf+1){
                    posf = buff.find(" ",pos);
                    if(posf == (unsigned int)-1)
                        vertexs.push_back(atof(buff.substr(pos, buff.size()-pos ).c_str()));
                    else
                        vertexs.push_back(atof(buff.substr(pos, posf-pos ).c_str()));

                }
            }else if(command=="vt"){
                std::getline(file,buff);
                posf = 0;
                while(pos = posf+1){
                    posf = buff.find(" ",pos);
                    if(posf ==(unsigned int)-1)
                        uvs.push_back(atof(buff.substr(pos, buff.size()-pos ).c_str()));
                    else
                        uvs.push_back(atof(buff.substr(pos, posf-pos ).c_str()));
                }
            }else if(command=="vn"){
                std::getline(file,buff);
                posf = 0;
                while(pos = posf+1){
                    posf = buff.find(" ",pos);
                    normals.push_back(atof(buff.substr(pos, posf-pos ).c_str()));
                }
            }else if(command=="usemtl"){
                file>>buff;
                mateInds.push_back(namesMat[buff]);
                useMtl = true;
            }else if(command=="f"){
                std::getline(file,buff);

                numVert = 0;
                if(type == 0){
                    temp = buff.substr( 1, buff.find(" ",1));
                    posf = temp.find("/");
                    type++;
                    if(posf !=(unsigned int)-1){
                        type++;
                        pos = posf;
                        posf = temp.find("/",pos+1);
                        if(posf !=(unsigned int)-1){
                            type++;
                            if(posf==(pos+1)){
                                type++;
                            }
                        }
                    }
                }
                posf = 0;
                if(type == 1){
                    while(pos = posf+1){
                        posf = buff.find(" ",pos);
                        if(posf ==(unsigned int) -1)
                            faces.push_back(atoi(buff.substr( pos, buff.size() - pos  ).c_str()));
                        else
                            faces.push_back(atoi(buff.substr( pos, posf - pos  ).c_str()));
                        numVert++;
                    }
                }else if(type == 2){
                    while(pos = posf+1){
                        posf = buff.find("/",pos);
                        faces.push_back(atoi(buff.substr(pos, posf-pos ).c_str()));
                        pos = posf+1;
                        posf = buff.find(" ",pos);
                        if(posf ==(unsigned int) -1)
                            faces.push_back(atoi(buff.substr( pos, buff.size() - pos  ).c_str()));
                        else
                            faces.push_back(atoi(buff.substr( pos, posf - pos  ).c_str()));
                        numVert++;
                    }
                }else if(type == 3){
                    while(pos = posf+1){
                        posf = buff.find("/",pos);
                        faces.push_back(atoi(buff.substr(pos, posf-pos ).c_str()));
                        pos = posf+1;
                        posf = buff.find("/",pos);
                        faces.push_back(atoi(buff.substr( pos, posf - pos ).c_str()));
                        pos = posf+1;
                        posf = buff.find(" ",pos);
                        if(posf ==(unsigned int) -1)
                            faces.push_back(atoi(buff.substr( pos, buff.size() - pos  ).c_str()));
                        else
                            faces.push_back(atoi(buff.substr( pos, posf - pos  ).c_str()));
                        numVert++;
                    }
                }else if(type == 4){
                    while(pos = posf+1){
                        posf = buff.find("/",pos);
                        faces.push_back(atoi(buff.substr(pos, posf-pos ).c_str()));
                        pos = posf+2;
                        posf = buff.find(" ",pos);
                        if(posf ==(unsigned int) -1)
                            faces.push_back(atoi(buff.substr( pos, buff.size() - pos  ).c_str()));
                        else
                            faces.push_back(atoi(buff.substr( pos, posf - pos  ).c_str()));
                        numVert++;
                    }
                }
                if(!typeFace.empty())
                    if((unsigned int)*typeFace.rbegin()!=numVert){
                        mateInds.push_back(*mateInds.rbegin());
                        typeFace.push_back(numVert);
                        numcoord.push_back(numVert);
                    }else if(useMtl){
                        typeFace.push_back(numVert);
                        numcoord.push_back(numVert);
                        useMtl = false;
                    }else{
                        (*numcoord.rbegin())+=numVert;
                    }
                else{
                    typeFace.push_back(numVert);
                    numcoord.push_back(numVert);
                    useMtl = false;
                }
            }
            else if(command=="l"){
                std::getline(file,buff);
                posf = 0;
                numVert = 0;
                while(pos = posf+1){
                    posf = buff.find(" ",pos);
                    faces.push_back(atoi(buff.substr(pos, posf-pos ).c_str()));
                    numVert++;
                }
                typeFace.push_back(1);
                numcoord.push_back(numVert);
                if(!useMtl)mateInds.push_back(*mateInds.rbegin());
            }
            command.clear();
        }

        file.close();

        vector<float> vert;
        vector<float> norm;
        vector<float> uv;
        unsigned int length = faces.size();

        for(unsigned int i = 0; i < length; i++){
            vert.push_back(vertexs[(faces[i]-1)*3]);
            vert.push_back(vertexs[(faces[i]-1)*3+1]);
            vert.push_back(vertexs[(faces[i]-1)*3+2]);
            if((type == 2)||(type == 3)){
                i++;
                uv.push_back(uvs[(faces[i]-1)*2]);
                uv.push_back(uvs[(faces[i]-1)*2+1]);
            }
            if(type > 2){
                i++;
                norm.push_back(normals[(faces[i]-1)*3]);
                norm.push_back(normals[(faces[i]-1)*3+1]);
                norm.push_back(normals[(faces[i]-1)*3+2]);
            }
        }
        vertexs.clear();
        uvs.clear();
        normals.clear();
        glGenBuffers(3,Buff);
        glBindVertexArray(Id);

        glBindBuffer(GL_ARRAY_BUFFER,Buff[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vert.size(),vert.data(), GL_STATIC_DRAW);
        SetVertexsAttribLocation(3 , GL_FLOAT);

        if((type == 2)||(type == 3)){
            glBindBuffer(GL_ARRAY_BUFFER,Buff[1]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*uv.size(),uv.data(), GL_STATIC_DRAW);
            SetUVsAttribLocation(2 , GL_FLOAT);
        }
        if(type > 2){
            glBindBuffer(GL_ARRAY_BUFFER,Buff[2]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*norm.size(),norm.data(), GL_STATIC_DRAW);
            SetNormalsAttribLocation(3 , GL_FLOAT);
        }

        return 0;
    }

    void DENGIDEF WaveFront::Draw(){
        Mposs.rotate(0.001,0,1,0);
        UseModelMatrix(Mposs.get());
        glBindVertexArray(Id);
        SetTypeObjectLocation(1);
        unsigned int num = 0;
        unsigned int length = typeFace.size();
        for(unsigned int i = 0; i < length; i++){

            if(i==0){
                materials[mateInds[0]].Use();
            }else if(mateInds[i] != mateInds[i-1]){
                materials[mateInds[i]].Use();
            }
            switch(typeFace[i]){
                case 4:
                    glDrawArrays(GL_QUADS,num,numcoord[i]);
                    break;
                case 3:
                    glDrawArrays(GL_TRIANGLES,num,numcoord[i]);
                    break;
                case 1:
                    glDrawArrays(GL_LINE_STRIP,num,numcoord[i]);
                    break;
                default:
                    glDrawArrays(GL_POLYGON,num,numcoord[i]);
            }
            num += numcoord[i];
        }
    }
}
