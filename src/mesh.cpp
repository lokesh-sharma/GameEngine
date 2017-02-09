#include "../include/mesh.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include"../include/ObjLoader.h"


std::map<std::string, MeshData*> Mesh::meshResource;

MeshData::MeshData(const std::string& fileName)
{
    LoadMesh(fileName);
}
void MeshData::LoadMesh(const std::string & filename)
{
    counter=0;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texcord;

    ObjLoader loader(filename.c_str() , vertices , texcord , normals);
    m_verts = vertices;

    m_drawCount = vertices.size();

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
	glDrawArrays(GL_TRIANGLES , 0 , m_drawCount);

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
