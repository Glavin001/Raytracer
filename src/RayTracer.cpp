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
}

bool transmittedDirection( const Vector3f& normal, const Vector3f& incoming,
        float index_n, float index_nt,
        Vector3f& transmitted)
{
}

RayTracer::RayTracer( SceneParser * scene, int max_bounces
  //more arguments if you need...
                      ) :
  m_scene(scene)

{
  // g=scene->getGroup();
  m_maxBounces = max_bounces;
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

        // Diffuse and Specular light
        // Check for lights
        int numLights = m_scene->getNumLights();
        // FIXME: Only single light
        if (numLights > 0) {
            // Get Light
            Light *light = m_scene->getLight(0);

            Vector3f p = ray.pointAtParameter(hit.getT());
            Vector3f dirToLight;
            Vector3f intensity;
            float distanceToLight;
            light->getIllumination( p, dirToLight, intensity, distanceToLight);

            Hit rhit = Hit( FLT_MAX, NULL, Vector3f( 0, 0, 0 ) );
            Ray ray = Ray(p, dirToLight);
            if (!group->intersect(ray, rhit, EPSILON)) {
                Vector3f h = (dirToLight.normalized() + (-1*ray.getDirection()).normalized());

                color = color + material->getDiffuseColor() * intensity * fmax(0, Vector3f::dot(hit.getNormal(), dirToLight));
            }
        }
        return color;
    } else {
        return m_scene->getBackgroundColor();
    }
}
