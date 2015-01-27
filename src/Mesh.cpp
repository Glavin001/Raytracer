#include "Mesh.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <sstream>
bool Mesh::intersect( const Ray& r, Hit& h, float tmin ) {
    bool result = false;
    for( unsigned int i = 0; i < t.size(); i++) {
        Triangle triangle(v[t[i][0]],
                          v[t[i][1]],v[t[i][2]],material);
        for(int jj=0; jj<3; jj++) {
            triangle.normals[jj] = n[t[i][jj]];

        }
        if(texCoord.size()>0) {
            for(int jj=0; jj<3; jj++) {
                triangle.texCoords[jj] = texCoord[t[i].texID[jj]];
            }
            triangle.hasTex=true;
        }
        result |= triangle.intersect( r, h, tmin);
    }
    return result;
}

Mesh::Mesh(const char * filename,Material * material) : Object3D(material)
{
    std::ifstream f;
    f.open(filename);
    if(!f.is_open()) {
        std::cout<<"Cannot open "<<filename<<"\n";
        return;
    }
    std::string line;
    std::string vTok("v");
    std::string fTok("f");
    std::string texTok("vt");
    char bslash='/',space=' ';
    std::string tok;
    while(1) {
        std::getline(f,line);
        if(f.eof()) {
            break;
        }
        if(line.size()<3) {
            continue;
        }
        if(line.at(0)=='#') {
            continue;
        }
        std::stringstream ss(line);
        ss>>tok;
        if(tok==vTok) {
            Vector3f vec;
            ss>>vec[0]>>vec[1]>>vec[2];
            v.push_back(vec);
        } else if(tok==fTok) {
            if(line.find(bslash)!=std::string::npos) {
                std::replace(line.begin(),line.end(),bslash,space);
                std::stringstream facess(line);
                Trig trig;
                facess>>tok;
                for(int ii=0; ii<3; ii++) {
                    facess>>trig[ii]>>trig.texID[ii];
                    trig[ii]--;
                    trig.texID[ii]--;
                }
                t.push_back(trig);
            } else {
                Trig trig;
                for(int ii=0; ii<3; ii++) {
                    ss>>trig[ii];
                    trig[ii]--;
                    trig.texID[ii]=0;
                }
                t.push_back(trig);
            }
        } else if(tok==texTok) {
            Vector2f texcoord;
            ss>>texcoord[0];
            ss>>texcoord[1];
            texCoord.push_back(texcoord);
        }
    }
    compute_norm();

    f.close();
}

void Mesh::compute_norm()
{
    // std::cout << "Compute norm, " << n.size() << ", " << v.size() << endl;

    // FIXME: v.size() is not large enough for some tested high res .obj
    n.resize(v.size() + texCoord.size());

    // std::cout << "resize complete, " << n.size() << ", " << t.size() << endl;

    for(unsigned int ii=0; ii<t.size(); ii++) {
        // std::cout << "ii: "<<ii<<endl;

        Vector3f a = v[t[ii][1]] - v[t[ii][0]];
        // std::cout << "a: "<<a<<endl;

        Vector3f b = v[t[ii][2]] - v[t[ii][0]];
        // std::cout << "b1: "<<b<<endl;

        b=Vector3f::cross(a,b);
        // std::cout << "b2: "<<b<<endl;

        for(int jj=0; jj<3; jj++) {
            try {
                int p = t.at(ii)[jj];
                // std::cout << "ii: "<<ii<< ", " << "jj: " << jj << ", p: "<< p << ", n:"<<n.size() <<endl;

                n.at(p) += b;
            } catch (const std::out_of_range& oor) {
                std::cerr << "Out of Range error: " << oor.what() << '\n';
            }
        }

    }
    // std::cout << "done loop 1" << endl;

    for(unsigned int ii=0; ii<v.size(); ii++) {
        n[ii] = n[ii]/ n[ii].abs();
    }

    // std::cout << "done loop 2" << endl;

}
