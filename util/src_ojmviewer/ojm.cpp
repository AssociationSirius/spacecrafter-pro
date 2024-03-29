#include "ojm.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>


// *****************************************************************************
// 
// CLASSE OJM
//
// *****************************************************************************

Ojm::Ojm( const std::string & _fileName, const std::string & _pathFile, float multiplier)
{
	fileName = _fileName;
	is_ok = false;
	pathFile = _pathFile;
	is_ok = init(multiplier);
}

Ojm::~Ojm()
{
    for(unsigned int i=0;i<shapes.size();i++){
		glDeleteBuffers(1,&shapes[i].dGL.pos);
		glDeleteBuffers(1,&shapes[i].dGL.tex);
		glDeleteBuffers(1,&shapes[i].dGL.norm);
		glDeleteBuffers(1,&shapes[i].dGL.elementBuffer);
		glDeleteVertexArrays(1,&shapes[i].dGL.vao);

        if (shapes[i].map_Ka!=nullptr) {
            delete shapes[i].map_Ka;
            shapes[i].map_Ka=nullptr;
        }
    	if (shapes[i].map_Kd!=nullptr) {
            delete shapes[i].map_Kd;
            shapes[i].map_Kd=nullptr;
        }
    	if (shapes[i].map_Ks!=nullptr) {
            delete shapes[i].map_Ks;
            shapes[i].map_Ks=nullptr;
        }
    }
	shapes.clear();
}

Ojm::Ojm(const std::string& _fileName)
{
	Ojm(_fileName, "", 1.0);
}

bool Ojm::init(float multiplier)
{
	is_ok = readOJM(fileName, multiplier);
	if (is_ok) {
		is_ok=testIndices();
		initGLparam();
	}
	return is_ok;
}

bool Ojm::testIndices()
{
	for(unsigned int i=0;i<shapes.size();i++){
		if (shapes[i].vertices.size() != shapes[i].normals.size()) {
			std::cout << "vertices.size != normals.size : abord"<<std::endl;
			return false;
		}
		if (shapes[i].uvs.size()==0) {
			glm::vec2 data{0.0,0.0};
			for(unsigned int k=0; k< shapes[i].vertices.size(); k++)
				shapes[i].uvs.push_back(data);
		}
		if (shapes[i].vertices.size() != shapes[i].uvs.size()) {
			std::cout << "vertices.size != uvs.size : abord"<<std::endl;
			return false;
		}
	}
	return true;
}

void Ojm::draw(shaderProgram * shader)
{
	for(unsigned int i=0;i<shapes.size();i++){
		//~ cout << "shape " << i << " name " << shapes[i].name <<  endl;
		shader->setUniform("Material.Ka", shapes[i].Ka);
		shader->setUniform("Material.Kd", shapes[i].Kd);
		shader->setUniform("Material.Ks", shapes[i].Ks);
		shader->setUniform("Material.Ns", shapes[i].Ns);
		if (shapes[i].T < 1.0)
			shader->setUniform("T", shapes[i].T);

		if (shapes[i].map_Ka != 0) {
			glBindTexture(GL_TEXTURE_2D, shapes[i].map_Ka->getID());
			shader->setUniform("useTexture", true);
			//~ cout << "avec texture" << endl;
		} else {
			shader->setUniform("useTexture", false);
			//~ cout << "sans texture" << endl;
		}

		glBindVertexArray(shapes[i].dGL.vao);
		glDrawElements(GL_TRIANGLES, shapes[i].indices.size(), GL_UNSIGNED_INT, (void*)0 );
	} 
}

void Ojm::initGLparam()
{
	for(unsigned int i=0;i<shapes.size();i++){


		glGenVertexArrays(1,&shapes[i].dGL.vao);
		glBindVertexArray(shapes[i].dGL.vao);

		glGenBuffers(1,&shapes[i].dGL.pos);
		glGenBuffers(1,&shapes[i].dGL.tex);
		glGenBuffers(1,&shapes[i].dGL.norm);
		glGenBuffers(1,&shapes[i].dGL.elementBuffer);

		glBindBuffer(GL_ARRAY_BUFFER,shapes[i].dGL.pos);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*3*shapes[i].vertices.size(), shapes[i].vertices.data(),GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER,shapes[i].dGL.tex);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*2*shapes[i].uvs.size(), shapes[i].uvs.data(),GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER,shapes[i].dGL.norm);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*3*shapes[i].normals.size(), shapes[i].normals.data(),GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,shapes[i].dGL.elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*shapes[i].indices.size(), shapes[i].indices.data(),GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, shapes[i].dGL.pos);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
		glBindBuffer(GL_ARRAY_BUFFER, shapes[i].dGL.tex);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,NULL);
		glBindBuffer(GL_ARRAY_BUFFER, shapes[i].dGL.norm);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapes[i].dGL.elementBuffer);
		glVertexAttribPointer(3,1,GL_FLOAT,GL_FALSE,0,NULL);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
	} 
}

bool Ojm::readOJM(const std::string& filename, float multiplier)
{
    std::cout<<"OJM: Reading file "<<filename << std::endl;
    std::ifstream stream;
    char line[265];

    stream.open(filename.c_str(),std::ios_base::in);

    if(stream.is_open())
    {
        int shapeIter=-1;

        do{
            stream.getline(line,256);

            switch(line[0])
            {
                case 'o':
                    // //////////////////////////////////////////////////////////////////////////////////////////////
                    shapeIter++;
                    shapes.push_back({});
                    shapes[shapeIter].name = line+2;
                    shapes[shapeIter].name = shapes[shapeIter].name.substr(0,shapes[shapeIter].name.find('\n'));
                    // //////////////////////////////////////////////////////////////////////////////////////////////
                break;

                case 'v':
                    {
                        glm::vec3 vertex;
                        std::stringstream ss(std::string(line+2));
                        ss>>vertex.x;
                        ss>>vertex.y;
                        ss>>vertex.z;
                        shapes[shapeIter].vertices.push_back(vertex * multiplier);
                    }
                break;

                case 'u':
                    {
                        glm::vec2 uv;
                        std::stringstream ss(std::string(line+2));
                        ss>>uv.x;
                        ss>>uv.y;
                        shapes[shapeIter].uvs.push_back(uv);
                    }
                break;

                case 'n':
                    {
                        glm::vec3 normal;
                        std::stringstream ss(std::string(line+2));
                        ss>>normal.x;
                        ss>>normal.y;
                        ss>>normal.z;
                        shapes[shapeIter].normals.push_back(normal);
                    }
                break;

                case 'T':
                    {
                        float tmp;
                        std::stringstream ss(std::string(line+2));
						ss >> tmp;
						std::cout << "T " << tmp << std::endl;
                        shapes[shapeIter].T = tmp;
                    }
                break;

                case 'j':
                    {
                        unsigned int indice[9];
                        std::stringstream ss(std::string(line+2));
                        ss>>indice[0] >> indice[1] >> indice[2] >> indice[3] >> 
                            indice[4] >> indice[5] >> indice[6] >> indice[7] >> 
                            indice[8];
                        for(unsigned int k=0; k<9; k++)
							shapes[shapeIter].indices.push_back(indice[k]);
                    }
                    break;

                case 'i':
                    {
                        unsigned int indice1, indice2, indice3;
                        std::stringstream ss(std::string(line+2));
                        ss>>indice1 >> indice2 >> indice3;
                        shapes[shapeIter].indices.push_back(indice1);
                        shapes[shapeIter].indices.push_back(indice2);
                        shapes[shapeIter].indices.push_back(indice3);
                    }
                break;

                case 'k':
                    switch(line[1])
                    {
                        case 'a':
                            {
                                std::stringstream ss(std::string(line+3));
                                ss>>shapes[shapeIter].Ka.x;
                                ss>>shapes[shapeIter].Ka.y;
                                ss>>shapes[shapeIter].Ka.z;
                            }
                        break;
                        case 'd':
                            {
                                std::stringstream ss(std::string(line+3));
                                ss>>shapes[shapeIter].Kd.x;
                                ss>>shapes[shapeIter].Kd.y;
                                ss>>shapes[shapeIter].Kd.z;
                            }
                        break;
                        case 's':
                            {
                                std::stringstream ss(std::string(line+3));
                                ss>>shapes[shapeIter].Ks.x;
                                ss>>shapes[shapeIter].Ks.y;
                                ss>>shapes[shapeIter].Ks.z;
                            }
                        break;
                    }
                break;

                case 'N':
					if (line[1]=='s') {
						std::stringstream ss(std::string(line+3));
						ss>> shapes[shapeIter].Ns;
					}
					break;

                case 'm':
                    if(line[1]=='a'&& line[2]=='p' && line[3]=='_' && line[4]=='k')
                    switch(line[5])
                    {
                        case 'a':
                            {
                                std::string map_ka_filename(line+7);
                                //~ cout << "line |" << line << "|" << map_ka_filename << "|" << endl;
                                //~ map_ka_filename = map_ka_filename.substr(0,map_ka_filename.find('\n'));
                                //~ cout << "map_ka : |"<<map_ka_filename << "|" << endl;
                                if ( ! map_ka_filename.empty() && map_ka_filename!="0")
									shapes[shapeIter].map_Ka = new s_texture(pathFile+map_ka_filename, true);
                            }
                        break;
                        case 'd':
                            {
                                std::string map_kd_filename(line+7);
                                //~ map_kd_filename = map_kd_filename.substr(0,map_kd_filename.find('\n'));
                                //~ cout << "map_kd : |"<<map_kd_filename << "|" << endl;
                                if ( ! map_kd_filename.empty() && map_kd_filename!="0")
									shapes[shapeIter].map_Kd = new s_texture(pathFile+map_kd_filename, true);
                            }
                        break;
                        case 's':
                            {
                                std::string map_ks_filename(line+7);
                                //~ map_ks_filename = map_ks_filename.substr(0,map_ks_filename.find('\n'));
                                //~ cout << "map_ks : |"<<map_ks_filename << "|" << endl;
                                if ( ! map_ks_filename.empty() && map_ks_filename!="0")
									shapes[shapeIter].map_Ks = new s_texture(pathFile+map_ks_filename, true);
                            }
                        break;

						default: break;
                    }
                break;

                default: break;
            }
        }while(!stream.eof());
        std::cout<<"OJM: reached end of file"<<std::endl;
        return true;
    }
    std::cout<<"OJM: error reading file"<<std::endl;
	return false;
}


void Ojm::print()
{
	std::cout<< "Number of shape " << shapes.size() << std::endl;
	for(unsigned int i=0; i< shapes.size();i++) {
		std::cout<< "***** shapes n°"<< i<< std::endl;
		std::cout<< "Number of vectrices " << shapes[i].vertices.size() << std::endl;
		std::cout<< "Nombre Number of uvs        " << shapes[i].uvs.size() << std::endl;
		std::cout<< "Number of normales  " << shapes[i].normals.size() << std::endl;
		std::cout<< "Nombre Number of indices  " << shapes[i].indices.size() << std::endl;
		std::cout << "v ";
/*		for(unsigned int j=0; j< shapes[i].vertices.size() ; j++)
			std::cout << " " << shapes[i].vertices[j];
		std::cout << std::endl;
		std::cout << "uv ";
		for(unsigned int j=0; j< shapes[i].uvs.size() ; j++)
			std::cout << " " << shapes[i].uvs[j];
		std::cout << std::endl;
		std::cout << "n ";
		for(unsigned int j=0; j< shapes[i].normals.size() ; j++)
			std::cout << " " << shapes[i].normals[j];
		std::cout << std::endl;
		std::cout << "i ";
		for(unsigned int j=0; j< shapes[i].indices.size() ; j++)
			std::cout << " " << shapes[i].indices[j];
*/
		std::cout << std::endl;
	}
}
