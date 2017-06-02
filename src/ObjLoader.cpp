#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<cstring>
#include<iostream>
#include"../include/ObjLoader.h"
ObjLoader::ObjLoader(const char* fileName,std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals , std::vector<glm::vec3> & out_tangents)
{
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    FILE* file = fopen(fileName , "r");

    while(true)
    {
        char lineheader[128];
        if(fscanf(file , "%s" , lineheader) == EOF)
            break;
        if(strcmp(lineheader , "v") == 0)
        {
            glm::vec3 vertex;
            fscanf(file , "%f %f %f\n" , &vertex.x , &vertex.y , &vertex.z);

            temp_vertices.push_back(vertex);
        }
        else if(strcmp(lineheader , "vt") == 0)
        {
            glm::vec2 uv;
            fscanf(file , "%f %f\n" , &uv.x , &uv.y);
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineheader , "vn") == 0)
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if(strcmp(lineheader , "f") == 0)
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }

    for(int i = 0 ; i<vertexIndices.size(); i++)
    {
        unsigned int vertex_index = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertex_index-1];
        out_vertices.push_back(vertex);
    }
    for(int i = 0 ; i<uvIndices.size(); i++)
    {
        unsigned int uv_index = uvIndices[i];
        glm::vec2 uv = temp_uvs[uv_index-1];
        out_uvs.push_back(uv);
    }
    for(int i = 0 ; i<normalIndices.size(); i++)
    {
        unsigned int normal_index = normalIndices[i];
        glm::vec3 normal = temp_normals[normal_index-1];
        out_normals.push_back(normal);
    }
    for(int i  = 0; i <out_vertices.size() ; i++)
    {
        glm::vec3 & v0 = out_vertices[i+0];
        glm::vec3 & v1 = out_vertices[i+1];
        glm::vec3 & v2 = out_vertices[i+2];

        // Shortcuts for UVs
        glm::vec2 & uv0 = out_uvs[i+0];
        glm::vec2 & uv1 = out_uvs[i+1];
        glm::vec2 & uv2 = out_uvs[i+2];

        // Edges of the triangle : postion delta
        glm::vec3 deltaPos1 = v1-v0;
        glm::vec3 deltaPos2 = v2-v0;

        // UV delta
        glm::vec2 deltaUV1 = uv1-uv0;
        glm::vec2 deltaUV2 = uv2-uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        out_tangents.push_back(tangent);
        out_tangents.push_back(tangent);
        out_tangents.push_back(tangent);
    }


}

ObjLoader::~ObjLoader()
{
    //dtor
}
