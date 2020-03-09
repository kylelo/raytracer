const unsigned window_width  = 256;
const unsigned window_height = 256;

#include <GL/glut.h>
#include "geom.hpp"
#include "math.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "intersect.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "renderer.hpp"
#include <iostream>


void display()
{
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

    // Set up the scene HERE
    Scene t_Scene;
    t_Scene.addCamera( Camera(Point(-400, 0, -20),1, 0, 75, 0) );
    t_Scene.addSphere( Sphere(Point(130, 200, -30), 40, Color( 80,  80, 255)) );

    t_Scene.addSphere( Sphere(Point(100,  70, -40), 25, Color(100, 255, 100)) );
    t_Scene.addTetrahedron( Tetrahedron(Point(100, 130, -40), 60, Color(255, 200, 0)) );
    t_Scene.addPlane( Plane(Point(0, 0, -75), Point(1, 0, -75), Point(0, 1, -75)) );

    t_Scene.addAmbientLight(0.4);
    t_Scene.addLambertLight( LambertLight(0.5, 2, -1) );
    t_Scene.addSpecularShading( SpecularShading(0.5, 2, -1, 32, 1) );

    unsigned int data[window_height][window_width];
    for( int y = 0; y < window_height; ++y )
    {
        for( int x = 0; x < window_width; ++x )
        {
          Color c = Renderer::render_color_for_pixel(t_Scene, x, y);

          int r = c.getRed();
          int g = c.getGreen();
          int b = c.getBlue();

          data[y][x] = r +  g * 256 + b * 256 * 256;
        }
    }
    glDrawPixels( window_width, window_height, GL_RGBA, GL_UNSIGNED_BYTE, data ); // size of the display content
    glutSwapBuffers();
}


int main(int argc,char**argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize( window_width, window_height );
    glutCreateWindow( "GLUT" );
    glutDisplayFunc( display );
    glutMainLoop();
    return 0; // never reached

}
