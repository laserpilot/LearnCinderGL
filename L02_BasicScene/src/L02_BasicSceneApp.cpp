/*
Lesson 02: In Which We Learn to setup shaders and use batches to draw basic shapes.
Topics Covered:
	drawing simple primitives with BatchRefs
	writing shaders and using GlslProgRefs to shade our BatchRefs
	basic object positioning using glm, the GL Math library
*/

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/GlslProg.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class L02_BasicScene : public App
{
public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void update() override;
	void draw() override;

private:
	void setupCamera();

	CameraPersp	mCamera;
	CameraUi	mCameraCtrl;

	gl::BatchRef	mPlaneBatch;
	gl::GlslProgRef	mPlaneShader;

	gl::BatchRef	mSphereBatch;
	gl::GlslProgRef	mSphereShader;
};

void L02_BasicScene::setup()
{
	setupCamera();

	//setup plane
	string planeVertShader = "shaders/plane_vert.glsl";
	string planeFragShader = "shaders/plane_frag.glsl";
	mPlaneShader = gl::GlslProg::create(loadAsset(planeVertShader), loadAsset(planeFragShader));

	vec3 planeNormal(0, 1, 0);
	vec2 planeSize(2.0f);
	mPlaneBatch = gl::Batch::create(geom::Plane().normal(planeNormal).size(planeSize), mPlaneShader);

	//setup sphere
	string sphereVertShader = "shaders/sphere_vert.glsl";
	string sphereFragShader = "shaders/sphere_frag.glsl";
	mSphereShader = gl::GlslProg::create(loadAsset(sphereVertShader), loadAsset(sphereFragShader));

	float sphereRadius = 0.1f;
	int sphereResolution = 16;
	mSphereBatch = gl::Batch::create(geom::Sphere().radius(sphereRadius).subdivisions(sphereResolution),mSphereShader);
}

void L02_BasicScene::setupCamera()
{
	float verticalFOV = 45.0f;
	float aspectRatio = getWindowAspectRatio();
	float nearClip = 0.1f;
	float farClip = 10.0f;
	vec3 cameraPosition = vec3(0, 0, -1);
	vec3 cameraTarget = vec3(0);
	vec3 cameraUpAxis = vec3(0, 1, 0);

	mCamera.setPerspective(verticalFOV, aspectRatio, nearClip, farClip);
	mCamera.lookAt(cameraPosition, cameraTarget, cameraUpAxis);
	mCameraCtrl = CameraUi(&mCamera, getWindow());
}

void L02_BasicScene::mouseDown(MouseEvent event)
{
}

void L02_BasicScene::update()
{
}

void L02_BasicScene::draw()
{
	gl::clear(Color(0, 0, 0));
	gl::setMatrices(mCamera);
	gl::enableDepthRead();

	mPlaneBatch->draw();

	gl::pushMatrices();
	gl::translate(vec3(0, 0.1, 0));
	mSphereBatch->draw();
	gl::popMatrices();
}

CINDER_APP(L02_BasicScene, RendererGl)
