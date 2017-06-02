#ifndef OBJLOADER_H
#define OBJLOADER_H
#include<vector>
#include<glm/glm.hpp>
class ObjLoader
{
public:
        ObjLoader(const char* fileName,std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals , std::vector<glm::vec3> & tangents);
        virtual ~ObjLoader();
protected:
private:
    //ObjLoader(const ObjLoader& other) {}
    //ObjLoader& operator=(const ObjLoader& other) {}
};

#endif // OBJLOADER_H
