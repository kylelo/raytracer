#ifndef SCENE_HPP
#define SCENE_HPP

class Scene
{
public:
    Scene(){}

    void addCamera(const Camera& a_Cam)                        { m_Camera = a_Cam;                                 };
    void addSphere(const Sphere& a_Sphere)                     { m_Object.m_Spheres.push_back(a_Sphere);           };
    void addTetrahedron(const Tetrahedron& a_Tetrahedron)      { m_Object.m_Tetrahedrons.push_back(a_Tetrahedron); };
    void addPlane(const Plane& a_Plane)                        { m_Object.m_Planes.push_back(a_Plane);             };
    void addAmbientLight(const AmbientLight& a_AmLight)        { m_Light.m_Ambient = a_AmLight;                    };
    void addLambertLight(const LambertLight& a_LbLight)        { m_Light.m_Lamberts.push_back(a_LbLight);          };
    void addSpecularShading(const SpecularShading& a_SShading) { m_Light.m_Speculars.push_back(a_SShading);        };

    Camera getCamera() { return m_Camera; } const;
    Object getObject() { return m_Object; } const;
    Light  getLight()  { return m_Light;  } const;

private:
    Camera m_Camera;
    Object m_Object;
    Light  m_Light;
};

#endif /* SCENE_HPP */
