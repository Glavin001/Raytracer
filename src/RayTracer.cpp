#include "RayTracer.h"
#include "Camera.h"
#include "Ray.h"
#include "Hit.h"
#include "Group.h"
#include "Material.h"
#include "Light.h"
#include <cmath>

#define EPSILON 0.001

//IMPLEMENT THESE FUNCTIONS
//These function definitions are mere suggestions. Change them as you like.
Vector3f mirrorDirection( const Vector3f& normal, const Vector3f& incoming)
{
    return (incoming - 2*Vector3f::dot(incoming, normal) * normal).normalized();
}

bool transmittedDirection( const Vector3f& normal, const Vector3f& incoming,
                           float index_n, float index_nt,
                           Vector3f& transmitted)
{
}

RayTracer::RayTracer( SceneParser * scene,
                      int max_bounces,
                      bool shadows,
                      bool shade_back
                      //more arguments if you need...
                      ) :
    m_scene(scene)
{
    // g=scene->getGroup();
    m_maxBounces = max_bounces;
    m_shadows = shadows;
    m_shade_back = shade_back;
}

RayTracer::~RayTracer()
{
}

Vector3f RayTracer::traceRay( Ray& ray, float tmin, int bounces,
                              float refr_index, Hit& hit ) const
{
    hit = Hit( FLT_MAX, NULL, Vector3f( 0, 0, 0 ) );

    // Hit rec, srec = Hit();
    // Hit hit = Hit();
    //
    Group *group = (Group *) m_scene->getGroup();
    //
    if (group->intersect(ray, hit, tmin))
    {
        // Ambient light
        Material* material = hit.getMaterial();
        Vector3f color = material->getDiffuseColor() * m_scene->getAmbientLight();
        Vector3f normal = hit.getNormal().normalized();
        Vector3f p = ray.pointAtParameter(hit.getT());

        bool isBack = Vector3f::dot(normal, ray.getDirection()) > 0;
        if (m_shade_back && isBack)
        {
            // std::cout << "Back face: " << Vector3f::dot(normal, ray.getDirection()) << endl;
            normal *= -1; // Flip normal
        }

        // Diffuse and Specular light
        // Check for lights
        int numLights = m_scene->getNumLights();
        for (int i=0; i<numLights; i++) {
            // Get Light
            Light *light = m_scene->getLight(i);

            Vector3f dirToLight;
            Vector3f lightColor;
            float distanceToLight;
            light->getIllumination( p, dirToLight, lightColor, distanceToLight);

            Hit rhit = Hit( FLT_MAX, NULL, Vector3f( 0, 0, 0 ) );
            Ray rray = Ray(p, dirToLight);

            // Shadows
            if (!(m_shadows && group->intersect(rray, rhit, EPSILON) && rhit.getT() < distanceToLight)) {

                // Diffuse
                Vector3f diffuseColor = material->getDiffuseColor() * lightColor * fmax(0, Vector3f::dot(normal, dirToLight));
                color += diffuseColor;
                // Specular / Phong
                Vector3f h = (dirToLight.normalized() + -1*ray.getDirection().normalized()).normalized();
                Vector3f specularColor = material->getSpecularColor() * lightColor * pow(Vector3f::dot(normal, h), material->getShininess());
                color += specularColor;

                // std::cout << "diffuseColor: (" << diffuseColor.x() << ", " << diffuseColor.y() << ", " << diffuseColor.z() << ")" << endl;
                // std::cout << "specularColor:(" << specularColor.x() << ", " << specularColor.y() << ", " << specularColor.z() << ")" << endl;
                // std::cout << "normal:(" << normal.x() << ", " << normal.y() << ", " << normal.z() << ")" << endl;
                // std::cout << "dirToLight:(" << dirToLight.x() << ", " << dirToLight.y() << ", " << dirToLight.z() << ")" << endl;
                // std::cout << "ray.getDirection():(" << ray.getDirection().x() << ", " << ray.getDirection().y() << ", " << ray.getDirection().z() << ")" << endl;
                // std::cout << "h:(" << h.x() << ", " << h.y() << ", " << h.z() << ")" << endl;
                // std::cout << "normal dot h: " << Vector3f::dot(normal, h) << endl;
                //
                // std::cout << "color1: (" << color.x() << ", " << color.y() << ", " << color.z() << ")" << endl << endl;
            }

            // Specular Reflection
            if (bounces < m_maxBounces) {
                Vector3f dirFromMirror = mirrorDirection(normal, ray.getDirection());
                Ray mray = Ray(p, dirFromMirror);
                Hit mhit = Hit();
                color += material->getReflectiveColor() * traceRay(mray, EPSILON, ++bounces, 0.0f, mhit);
                // std::cout << "color2: (" << color.x() << ", " << color.y() << ", " << color.z() << ")" << endl << endl;
                // if (color.x() <= 0.03125f){
                //     std::cout << "color2: (" << color.x() << ", " << color.y() << ", " << color.z() << ")" << endl << endl;
                //     std::cout << "dirFromMirror: (" << dirFromMirror.x() << ", " << dirFromMirror.y() << ", " << dirFromMirror.z() << ")" << endl << endl;
                //     std::cout << "ray.getDirection():(" << ray.getDirection().x() << ", " << ray.getDirection().y() << ", " << ray.getDirection().z() << ")" << endl;
                // }
            }

        }
        return color;
    } else {
        return m_scene->getBackgroundColor(Vector3f( 0, 0, 0 ));
    }
}