// LookAt.cpp: A program using the TL-Engine

#include "Vector.h"
#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );

	/**** Set up your scene here ****/
	IFont* font = myEngine->LoadFont("calibri", 50);

	ICamera* myCamera = myEngine->CreateCamera(kManual, -50.0f, 75.f, -125.0f);
	myCamera->RotateLocalX(25.f);

	IMesh* square = myEngine->LoadMesh("cube.x");

	IModel* T = square->CreateModel(-100, 0, 0);
	IModel* S = square->CreateModel(-50, 0, 0);
	IModel* G = square->CreateModel(10, 0, 0);

	const double cameraSpeed = 0.1f;

	std::unique_ptr<Vector<float>> vect = std::make_unique<Vector<float>>();

	const Vector<float>::Vect3D U = Vector<float>::Vect3D(0, 1, 0);

	float sMove = 0.01f;


	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		// Control target movement
		T->MoveLocalZ(sMove);
		if (T->GetLocalZ() > 100.f || T->GetLocalZ() < -100.f)
			sMove *= -1;

		Vector<float>::Vect3D vG = Vector<float>::Vect3D(G->GetLocalX(), G->GetLocalY(), G->GetLocalZ());
		Vector<float>::Vect3D vT = Vector<float>::Vect3D(T->GetLocalX(), T->GetLocalY(), T->GetLocalZ());

		// LookAt
		// This is our facing vector
		const Vector<float>::Vect3D test = vT - vG;
		const Vector<float>::Vect3D Z = vect->normalise(vT - vG);

		// Now we can determine our other axis
		const Vector<float>::Vect3D X = vect->normalise(vect->crossproduct(U, Z));
		const Vector<float>::Vect3D Y = vect->normalise(vect->crossproduct(Z, X));

		// Let's update the matrix of G
		float matrix[4][4] = { 
				{X.x, X.y, X.z, 0.f},
				{Y.x, Y.y, Y.z, 0.f},
				{Z.x, Z.y, Z.z, 0.f},
				{G->GetLocalX(), G->GetLocalY(), G->GetLocalZ(), 1.f}
			};
		G->SetMatrix(*matrix);

		// Check infront/behind stationary cube
		Vector<float>::Vect3D vS = Vector<float>::Vect3D(S->GetLocalX(), S->GetLocalY(), S->GetLocalZ());
		// Take the dot product of facing vector (Z) the vector between G and S
		const float facingAngle = vect->dotproduct(Z, vS - vG);
		const string face = facingAngle == 0 ? "Orthagonal" : facingAngle < 0 ? "Behind" : "Infront";
		font->Draw(face + " (" + std::to_string(facingAngle) + ")", 0, 0, tle::kBlack);

		// Check direction of stationary cube (left/right)
		// Take the dot product of X axis the vector between G and S
		const float directionAngle = vect->dotproduct(X, vS - vG);
		const string dir = directionAngle == 0 ? "Facing" : directionAngle < 0 ? "Left" : "Right";
		font->Draw(dir + " (" + std::to_string(directionAngle) + ")", 0, 55, tle::kBlack);

		/**** Update your scene each frame here ****/
		if (myEngine->KeyHeld(Key_W))
		{
			myCamera->MoveLocalZ(cameraSpeed);
		}
		if (myEngine->KeyHeld(Key_S))
		{
			myCamera->MoveLocalZ(-cameraSpeed);
		}
		if (myEngine->KeyHeld(Key_A))
		{
			myCamera->MoveLocalX(-cameraSpeed);
		}
		if (myEngine->KeyHeld(Key_D))
		{
			myCamera->MoveLocalX(cameraSpeed);
		}

		// Rotation keys
		if (myEngine->KeyHeld(Key_E))
		{
			myCamera->RotateY(cameraSpeed);
		}
		if (myEngine->KeyHeld(Key_Q))
		{
			myCamera->RotateY(-cameraSpeed);
		}

		// Cube move
		if (myEngine->KeyHeld(Key_Up))
		{
			G->MoveLocalZ(cameraSpeed);
		}
		if (myEngine->KeyHeld(Key_Down))
		{
			G->MoveLocalZ(-cameraSpeed);
		}
		if (myEngine->KeyHeld(Key_Left))
		{
			G->MoveLocalX(-cameraSpeed);
		}
		if (myEngine->KeyHeld(Key_Right))
		{
			G->MoveLocalX(cameraSpeed);
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
