#include "../include/mesh.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include"assimp/Importer.hpp"
#include"assimp/scene.h"
#include"assimp/postprocess.h"
#include"ObjLoader.h"


std::map<std::string, MeshData*> Mesh::meshResource;

MeshData::MeshData(const std::string& fileName)
{
    LoadMesh(fileName);
}
void MeshData::LoadMesh(const std::string & filename)
{
    Assimp::Importer importer;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texcord;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;


    const aiScene* scene = importer.ReadFile(filename , aiProcess_Triangulate |

                                                        aiProcess_CalcTangentSpace
    );
    const aiMesh *model = scene->mMeshes[0];

    counter=0;

    std::vector<int> indices;

    const aiVector3D zero(0.0f , 0.0f , 0.0f);
    for(int i = 0 ; i < model->mNumVertices ; i++)
    {
        const aiVector3D* pPos = &(model->mVertices[i]);
        const aiVector3D* pNormal  = &(model->mNormals[i]);
        const aiVector3D* pTangent  = &(model->mTangents[i]);
        const aiVector3D* pTexcoord  = &(model->mTextureCoords[0][i]);
        vertices.push_back(glm::vec3(pPos->x , pPos->y , pPos->z));
        tangents.push_back(glm::vec3(pTangent->x , pTangent->y , pTangent->z));
        normals.push_back(glm::vec3(pNormal->x , pNormal->y , pNormal->z));
        texcord.push_back(glm::vec2(pTexcoord->x , pTexcoord->y));
    }
    for(int i = 0 ; i<model->mNumFaces ; i++)
    {
        const aiFace& face = model->mFaces[i];

        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    m_verts = vertices;

    m_drawCount = vertices.size();
    m_numIndices = indices.size();

    glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcord[0]) * texcord.size(), &texcord[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TANGENT_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tangents[0]) * tangents.size(), &tangents[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) *indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

}


MeshData::~MeshData()
{
    if(counter==0){
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	}
}

void MeshData::Draw()
{
	glBindVertexArray(m_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES , 0 , 2*m_drawCount);
	glBindVertexArray(0);
}
Mesh::Mesh(const std::string& fileName)
{
    m_fileName = fileName;
    std::map<std::string , MeshData*>::iterator it = meshResource.find(fileName);
    if(it == meshResource.end())
    {
        m_meshData= new MeshData(fileName);
        m_meshData->increment();
        meshResource[fileName] = m_meshData;
    }
    else
    {
        m_meshData = it->second;
        it->second->increment();
        std::cout<<"Already exists\n";
    }
}
void Mesh::Draw()
{
    m_meshData->Draw();
}
void Mesh::remove()
{
    m_meshData->decrement();
    m_meshData->~MeshData();
    meshResource.erase(m_fileName);
}
