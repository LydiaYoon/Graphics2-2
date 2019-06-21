#include <vgl.h>
#include <InitShader.h>
#include <mat.h>
#include <deque>
#include "MyCube.h"
#include "MyPyramid.h"

MyCube cube;
MyPyramid pyramid;

GLuint program;
GLuint uMat;

mat4 g_Mat = mat4(1.0);

bool bRotate = false;
int type = 1;
float time = 0;
float rotate = 0;
float ang1 = 0;
float ang2 = 0;
float ang3 = 0;

void myInit()
{
	cube.Init();
	pyramid.Init();

	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);
}

void draw1(GLuint uMat);
void draw2(GLuint uMat);
void draw3(GLuint uMat);

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	GLuint uMat = glGetUniformLocation(program, "uMat");
	
	if (type == 1 ) draw1(uMat);
	else if (type == 2) draw2(uMat);
	else if (type == 3) draw3(uMat);

	glutSwapBuffers();
}

void draw1(GLuint uMat)
{	
	std::deque<mat4> MS;

	mat4 M(1.0); // 하나만 쓰면 단위행렬
	mat4 CTM(1.0); // current transform matrix

	MS.push_back(CTM);

	//BASE_left
	CTM *= Translate(0, -0.5, 0) * RotateY(-time*5);
	M = Translate(0, 0, 0.07) * Scale(0.3, 0.3, 0.07);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	pyramid.Draw(program);
	MS.push_back(CTM); // 뒤로 쌓임

	//BASE_right
	M = Translate(0, 0, -0.07) * Scale(0.3, 0.3, 0.07);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	pyramid.Draw(program);

	//joint
	M = Translate(0, 0.1, 0) * Scale(0.03, 0.03, 0.25);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//////////

	//UpperArm
	CTM *= Translate(0, 0.1, 0) * RotateZ(ang1); // 실제로 움직이는 것
	M = Translate(0, 0.2, 0) * Scale(0.1, 0.5, 0.07); // 물체의 모양을 잡아주는것
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	MS.push_back(CTM);

	//joint
	M = Translate(0, 0.4, 0) * Scale(0.03, 0.03, 0.2);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//////////

	//LowerArm_left
	CTM *= Translate(0, 0.4, 0) * RotateZ(ang2);
	M = Translate(0, 0.2, 0.06) * Scale(0.1, 0.5, 0.05);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	MS.push_back(CTM);

	//LowerArm_right
	M = Translate(0, 0.2, -0.06) * Scale(0.1, 0.5, 0.05);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//joint
	M = Translate(0, 0.4, 0) * Scale(0.03, 0.03, 0.2);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//////////

	//hand
	CTM *= Translate(0, 0.4, 0) * RotateZ(ang3);
	M = Translate(0, 0, 0) * Scale(0.4, 0.1, 0.07);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	MS.push_back(CTM);
}

void draw2(GLuint uMat)
{	
	std::deque<mat4> MS;

	mat4 M(1.0); // 하나만 쓰면 단위행렬
	mat4 CTM(1.0); // current transform matrix

	MS.push_back(CTM);

	//BASE_left
	CTM *= Translate(0, -0.5, 0) * RotateY(-time*5); // 실제로 움직이는 것
	M = Translate(0, 0, 0.07) * Scale(0.3, 0.3, 0.07); // 물체의 모양을 잡아주는것
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	pyramid.Draw(program);
	MS.push_back(CTM); // 뒤로 쌓임

	//BASE_right
	M = Translate(0, 0, -0.07) * Scale(0.3, 0.3, 0.07);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	pyramid.Draw(program);

	//joint
	M = Translate(0, 0.1, 0) * Scale(0.03, 0.03, 0.25);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//////////

	//UpperArm
	CTM *= Translate(0, 0.1, 0) * RotateZ(ang1);
	M = Translate(0, 0.2, 0) * Scale(0.1, 0.5, 0.07);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	MS.push_back(CTM);

	//joint
	M = Translate(0, 0.4, 0) * Scale(0.03, 0.03, 0.2);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//////////

	//LowerArm_left
	CTM *= Translate(0, 0.4, 0) * RotateZ(ang2);
	M = Translate(0, 0, 0.06) * Scale(0.5, 0.1, 0.05);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	MS.push_back(CTM);

	//LowerArm_right
	M = Translate(0, 0, -0.06) * Scale(0.5, 0.1, 0.05);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//joint_left
	M = Translate(-0.2, 0, 0) * Scale(0.03, 0.03, 0.2);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//joint_left
	M = Translate(-0.2, 0, 0) * Scale(0.03, 0.03, 0.2);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//joint_right
	M = Translate(0.2, 0, 0) * Scale(0.03, 0.03, 0.2);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//////////

	//hand_left
	CTM *= Translate(-0.2, 0, 0) * RotateZ(ang3);
	M = Translate(0, 0.2, 0) * Scale(0.1, 0.5, 0.07);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	MS.push_back(CTM);

	//hand_right
	MS.pop_back();
	CTM = MS.back();
	CTM *= Translate(0.2, 0, 0) * RotateZ(-ang3);
	M = Translate(0, 0.2, 0) * Scale(0.1, 0.5, 0.07);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	MS.push_back(CTM);
}

void draw3(GLuint uMat)
{	
	std::deque<mat4> MS;

	mat4 M(1.0); // 하나만 쓰면 단위행렬
	mat4 CTM(1.0); // current transform matrix

	MS.push_back(CTM);

	//BASE
	CTM *= Translate(0, 0, 0) * RotateY(-time*8);
	M = Translate(0, 0, 0) * Scale(0.2, 0.4, 0.1);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	MS.push_back(CTM); // 뒤로 쌓임

	//joint (목)
	M = Translate(0, 0.225, 0) * Scale(0.05, 0.05, 0.05);
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);

	//////////

	//Head
	CTM *= Translate(0, 0.2, -0.05) * RotateX(ang1); // 실제로 움직이는 것
	M = Translate(0, 0.1, 0.05) * Scale(0.1, 0.1, 0.07); // 물체의 모양을 잡아주는것
	glUniformMatrix4fv(uMat, 1, true, CTM*M);
	cube.Draw(program);
	MS.push_back(CTM);

	////////////

	////LowerArm_left
	//CTM *= Translate(0, 0.4, 0) * RotateZ(ang2);
	//M = Translate(0, 0, 0.06) * Scale(0.5, 0.1, 0.05);
	//glUniformMatrix4fv(uMat, 1, true, CTM*M);
	//cube.Draw(program);
	//MS.push_back(CTM);

	////LowerArm_right
	//M = Translate(0, 0, -0.06) * Scale(0.5, 0.1, 0.05);
	//glUniformMatrix4fv(uMat, 1, true, CTM*M);
	//cube.Draw(program);

	////joint_left
	//M = Translate(-0.2, 0, 0) * Scale(0.03, 0.03, 0.2);
	//glUniformMatrix4fv(uMat, 1, true, CTM*M);
	//cube.Draw(program);

	////joint_left
	//M = Translate(-0.2, 0, 0) * Scale(0.03, 0.03, 0.2);
	//glUniformMatrix4fv(uMat, 1, true, CTM*M);
	//cube.Draw(program);

	////joint_right
	//M = Translate(0.2, 0, 0) * Scale(0.03, 0.03, 0.2);
	//glUniformMatrix4fv(uMat, 1, true, CTM*M);
	//cube.Draw(program);

	////////////

	////hand_left
	//CTM *= Translate(-0.2, 0, 0) * RotateZ(ang3);
	//M = Translate(0, 0.2, 0) * Scale(0.1, 0.5, 0.07);
	//glUniformMatrix4fv(uMat, 1, true, CTM*M);
	//cube.Draw(program);
	//MS.push_back(CTM);

	////hand_right
	//MS.pop_back();
	//CTM = MS.back();
	//CTM *= Translate(0.2, 0, 0) * RotateZ(-ang3);
	//M = Translate(0, 0.2, 0) * Scale(0.1, 0.5, 0.07);
	//glUniformMatrix4fv(uMat, 1, true, CTM*M);
	//cube.Draw(program);
	//MS.push_back(CTM);
}


void myIdle()
{	
	time += 0.1f;
	if (bRotate == true)
	{
		rotate += 0.1f;

		if (type == 1)
		{
			ang1 = 60*sin(rotate*0.5);
			ang2 = 60*sin(rotate);
			ang3 = 20*sin(rotate*2);
		}

		else if (type == 2)
		{
			ang1 = 60*sin(rotate*0.5);
			ang2 = 20*sin(rotate);
			ang3 = 20*sin(rotate);
		}

		else if (type == 3)
		{
			ang1 = 10*sin(rotate*3);
			ang2 = 20*sin(rotate);
			ang3 = 20*sin(rotate);
		}
	}

	Sleep(16);
	glutPostRedisplay();

}

void myKey(unsigned char key, int x, int y)
{
	if (key == VK_SPACE) // 스페이스바
	{
		if (bRotate == false)
		{
			bRotate = true;
			printf("Start Motion!\n");
		}
		else
		{
			bRotate = false;
			printf("Stop Motion!\n");
		}
	}
	else if (key == '1')
	{
		type = 1;
		printf("Set Robot Type 1\n");
	}
	else if (key == '2')
	{
		type = 2;
		printf("Set Robot Type 2\n");
	}
	else if (key == '3')
	{
		type = 3;
		printf("Set Robot Type 3\n");
	}
	else if (key == 'q' || key == 'Q')
		exit(0); // 종료
	else return;

	myInit();
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("Cube and Pyramid");

	glewExperimental = true;
	glewInit();
	myInit();

	printf("======================================\n");
	printf("== Homework #2: Simple Robot Arm    ==\n");
	printf("======================================\n");
	printf("== [1] key: Robot Arm Type 1        ==\n");
	printf("== [2] key: Robot Arm Type 2        ==\n");
	printf("== [SPACE] key: Start Motion!       ==\n");
	printf("======================================\n");
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKey);

	glutMainLoop();

	return 0;
}
