
#ifndef SHADER_H
#define SHADER_H

#include "includes.h"

/*
* Singleton for a GLuint shaderProgram
*/
class Shader
{
private:
	GLuint shaderProgram;

	Shader(void)
	{
		// Initalize the shader
		shaderProgram = InitShader( "vshader.glsl", "fshader.glsl" );
		// Get the location of a uniform shader variable named 'ortho'.
		GLint orthoLoc = glGetUniformLocation(shaderProgram, "ortho");
		// Now set it to the orthographic projection.
		glProgramUniformMatrix4fv(shaderProgram, orthoLoc, 1, true, Ortho2D( 0, WINDOW_WIDTH, 0, WINDOW_HEIGHT ) );

	};

	Shader(Shader const&);	// DO NOT IMPLEMENT
	void operator=(Shader const&); // DO NOT IMPLEMENT

	static char* readShaderSource( const char* shaderFile )
	{// Create a NULL-terminated string by reading the provided file
		FILE* fp = fopen(shaderFile, "r"); // VS gives warning about being insecure :-)

		if ( fp == NULL ) { return NULL; }

		fseek(fp, 0L, SEEK_END);
		long size = ftell(fp);

		fseek(fp, 0L, SEEK_SET);
		char* buf = new char[size + 1];
		fread(buf, 1, size, fp);

		buf[size] = '\0';
		fclose(fp);

		return buf;
	};
	static GLuint InitShader( const char* vShaderFile, const char* fShaderFile )
	{
		 struct Shader
		{
			const char*  filename;
			GLenum       type;
			GLchar*      source;
		}  shaders[2] = {
			{ vShaderFile, GL_VERTEX_SHADER, NULL },
			{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
		};

		GLuint program = glCreateProgram();
    
		for ( int i = 0; i < 2; ++i )
		{
			Shader& s = shaders[i];
			s.source = readShaderSource( s.filename );
			if ( shaders[i].source == NULL ) 
			{
				std::cerr << "Failed to read " << s.filename << std::endl;
				exit( EXIT_FAILURE );
			}

			GLuint shader = glCreateShader( s.type );
			glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
			glCompileShader( shader );

			GLint  compiled;
			glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
			if ( !compiled ) 
			{
				std::cerr << s.filename << " failed to compile:" << std::endl;
				GLint  logSize;
				glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
				char* logMsg = new char[logSize];
				glGetShaderInfoLog( shader, logSize, NULL, logMsg );
				std::cerr << logMsg << std::endl;
				delete [] logMsg;

				exit( EXIT_FAILURE );
			}

			delete [] s.source;

			glAttachShader( program, shader );
		}

		glBindAttribLocation(program, 0, "vPosition" );
		glBindAttribLocation(program, 1, "vColor" );

		/* link  and error check */
		glLinkProgram(program);

		GLint  linked;
		glGetProgramiv( program, GL_LINK_STATUS, &linked );
		if ( !linked ) 
		{
			std::cerr << "Shader program failed to link" << std::endl;
			GLint  logSize;
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetProgramInfoLog( program, logSize, NULL, logMsg );
			std::cerr << logMsg << std::endl;
			delete [] logMsg;

			exit( EXIT_FAILURE );
		}

		/* use program object */
	//	glUseProgram(program);

		return program;

	};
	
public:
	static GLuint getShaderProgram()
	{
		static Shader instance;
		return instance.shaderProgram;
	}

	
};

#endif
