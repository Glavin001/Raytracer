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
    // std::cout << "=== transmittedDirection ===" << endl;
    // std::cout << "index_n: " << index_n << ", index_nt: " << index_nt << endl;
    // std::cout << "normal: ";
    // normal.print();
    // std::cout << "incoming: ";
    // incoming.print();

    float n = (index_n / index_nt);

    float sinT2 = (
        pow(n, 2)
        *
        (1 - pow(Vector3f::dot(incoming, normal), 2))
    );

    // std::cout << "disc: " << disc << endl;

    if (sinT2 > 1.0) {
        // transmitted = mirrorDirection(normal, incoming);
        transmitted = Vector3f(0,0,0);
        return false;
    }

    float cotT = sqrtf(1 - sinT2);

    transmitted = (n
        * (incoming - normal * Vector3f::dot(incoming, normal))
        - (normal * cotT)).normalized();

    // std::cout << "transmitted dir: ";
    // transmitted.print();

    return true;

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
        Vector3f rayDir = ray.getDirection();

        // If normal.dot(rayDir) > 0 then
        // they are facing the same direction
        // and the surface is the back face
        bool isBack = Vector3f::dot(normal, rayDir) > 0;
        Vector3f shadeNormal = normal;
        if (m_shade_back && isBack)
        {
            // std::cout << "Back face: " << Vector3f::dot(normal, rayDir) << endl;
            shadeNormal *= -1; // Flip normal
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
                Vector3f diffuseColor = material->getDiffuseColor() * lightColor * fmax(0, Vector3f::dot(shadeNormal, dirToLight));
                color += diffuseColor;
                // Specular / Phong
                Vector3f h = (dirToLight.normalized() + -1*rayDir.normalized()).normalized();
                Vector3f specularColor = material->getSpecularColor() * lightColor * pow(Vector3f::dot(shadeNormal, h), material->getShininess());
                color += specularColor;

                // std::cout << "diffuseColor: (" << diffuseColor.x() << ", " << diffuseColor.y() << ", " << diffuseColor.z() << ")" << endl;
                // std::cout << "specularColor:(" << specularColor.x() << ", " << specularColor.y() << ", " << specularColor.z() << ")" << endl;
                // std::cout << "normal:(" << normal.x() << ", " << normal.y() << ", " << normal.z() << ")" << endl;
                // std::cout << "dirToLight:(" << dirToLight.x() << ", " << dirToLight.y() << ", " << dirToLight.z() << ")" << endl;
                // std::cout << "rayDir:(" << rayDir.x() << ", " << rayDir.y() << ", " << rayDir.z() << ")" << endl;
                // std::cout << "h:(" << h.x() << ", " << h.y() << ", " << h.z() << ")" << endl;
                // std::cout << "normal dot h: " << Vector3f::dot(normal, h) << endl;
                //
                // std::cout << "color1: (" << color.x() << ", " << color.y() << ", " << color.z() << ")" << endl << endl;
            }
        }

        // Reflection / Refraction
        if (bounces < m_maxBounces) {

            float rn = refr_index;
            float rnt = material->getRefractionIndex();
            Vector3f dirFromMirror = mirrorDirection(normal, rayDir);

            // If point is on a dieletric
            if (rn > 0.0)
            {
                // std::cout << "=== Dielectric ===" <<endl;
                // std::cout << "rn:  " << rn <<endl;
                // std::cout << "rnt: " << rnt <<endl;

                float c;
                Vector3f k;
                Vector3f dirOfRefraction;

                // If entering object
                if (Vector3f::dot(rayDir, normal) < 0)
                {
                    // Entering object

                    // compute t
                    transmittedDirection(normal, rayDir, rn, rnt, dirOfRefraction);

                    // compute theta
                    c = Vector3f::dot(-rayDir, normal);
                    k = Vector3f(1,1,1);

                } else {
                    // Not entering object
                    // std::cout << "Exiting object" << endl;

                    // compute attenuation
                    // apply Beer's law
                    float attenuation = 0.15f;
                    Vector3f absorbance = attenuation * -hit.getT();// * material->getTransparentColor();
                    k = Vector3f( expf( absorbance.x() ), expf( absorbance.y() ), expf( absorbance.z() ) );

                    // compute t
                    bool doesRefract = transmittedDirection(-normal, rayDir, rnt, rn, dirOfRefraction);

                    if (doesRefract)
                    {
                        c = Vector3f::dot(dirOfRefraction, normal);
                    }
                    else
                    {
                        // std::cout << "Specular reflection only" << endl;
                        // Specular Reflection
                        Ray mray = Ray(p, dirFromMirror);
                        Hit mhit = Hit();
                        color += k * material->getReflectiveColor() *
                            traceRay(mray, EPSILON, bounces+1, rn, mhit);
                        return color;
                    }
                }

                // compute R0, R
                float R0 = pow(
                    (
                        (rn - 1)
                        /
                        (rn + 1)
                    ), 2);
                float R = (R0 + (1-R0)*pow((1-c), 5));

                Ray reflectRay = Ray(p, dirFromMirror);
                Ray refractRay = Ray(p, dirOfRefraction);
                Hit mhit1 = Hit();
                Hit mhit2 = Hit();

                // if (R < 0) {
                //     std::cout << "R: "<<R << ", R0: "<<R0 << ", c: "<< c <<endl;
                //     std::cout << "normal: " << normal.abs() << " ";
                //     normal.print();
                //     std::cout << ", dirOfRefraction: " << dirOfRefraction.abs() << " ";
                //     dirOfRefraction.print();
                //     std::cout << ", dirFromMirror" << dirFromMirror.abs() << " ";
                //     dirFromMirror.print();
                // }

                color += 1.0f * (
                    material->getReflectiveColor() *
                    R * traceRay(reflectRay, EPSILON, bounces+1, rn, mhit1)
                    +
                    k * material->getTransparentColor() *
                    (1-R) * traceRay(refractRay, EPSILON, bounces+1, rn, mhit2)
                );

            } else {
                // No refraction
                // Apply only reflection, if any
                // std::cout << "=== Not Dielectric ===" << endl;

                // Specular Reflection
                Ray mray = Ray(p, dirFromMirror);
                Hit mhit = Hit();
                color += material->getReflectiveColor() * traceRay(mray, EPSILON, bounces+1, rn, mhit);

            }

        }


        return color;
    } else {
        return m_scene->getBackgroundColor(Vector3f( 0, 0, 0 ));
    }
}
