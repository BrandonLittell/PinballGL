
#include "DrawablePolygon.h"

DrawablePolygon::DrawablePolygon( GLfloat initX, GLfloat initY, int numVerts, vec2* verts, vec3 color )
{
	mesh.numVertices = numVerts;
	mesh.vertices = new vec2[numVerts];
	mesh.color = new vec3[numVerts];
	
	for( int i = 0; i < numVerts; i++ )
	{
		mesh.vertices[i] = verts[i];
		mesh.color[i] = color;
	}
	// defaults to no change in color
	deltaColor = vec3( 0.0f, 0.0f, 0.0f );
	init();
	transforms.translate( vec2( initX, initY ) );
};

DrawablePolygon::~DrawablePolygon()
{
	delete [] mesh.color;
	delete [] mesh.vertices;
}
	
void DrawablePolygon::init( void )
{

	/*
	*	A lifesaver!
	*    http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
	*/
	
	// Create an array to hold x,y components of every vertex
	GLfloat* vertexData = new GLfloat[2*mesh.numVertices];

	// 
	for(int i = 0; i < mesh.numVertices; i++)
	{
		vertexData[i*2] = mesh.vertices[i].x;
		vertexData[i*2 + 1] = mesh.vertices[i].y;
	}

	GLfloat* colorData = new GLfloat[3*mesh.numVertices];
	for(int j = 0; j < mesh.numVertices; j++)
	{
		colorData[j*3] = mesh.color[j].x;
		colorData[j*3 + 1] = mesh.color[j].y;
		colorData[j*3 + 2] = mesh.color[j].z;
	}

	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	// initialize buffer objects
	glGenBuffers( 1, &mesh.vertexBuffer);
	glBindBuffer( GL_ARRAY_BUFFER, mesh.vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat)*2*mesh.numVertices, vertexData, GL_STATIC_DRAW );

	glGenBuffers( 1, &mesh.colorBuffer);
	glBindBuffer( GL_ARRAY_BUFFER, mesh.colorBuffer);
	glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat)*3*mesh.numVertices, colorData, GL_STATIC_DRAW );

	glUseProgram( shader.getShaderProgram() );

	
	delete [] vertexData;
	delete [] colorData;

};

void DrawablePolygon::draw( void )
{
	glUseProgram( shader.getShaderProgram() );

	// set world transformation
	GLint worldLoc = glGetUniformLocation( shader.getShaderProgram(), "world" );
	glProgramUniformMatrix4fv( shader.getShaderProgram(), worldLoc, 1, true, transforms.getMatrix() );

	// set change in color
	GLint colorLoc = glGetUniformLocation( shader.getShaderProgram(), "dColor" );
	GLfloat colorChange[] = { deltaColor.x, deltaColor.y, deltaColor.z };
	glUniform3fvARB( colorLoc, 1, colorChange );

	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, mesh.vertexBuffer );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glEnableVertexAttribArray( 1 );
	glBindBuffer( GL_ARRAY_BUFFER, mesh.colorBuffer );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glDrawArrays( GL_POLYGON, 0, mesh.numVertices );

	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
		
};

void DrawablePolygon::changeColor( vec3 dColor)
{
	deltaColor = dColor;
}