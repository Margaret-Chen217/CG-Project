#include <cstdlib>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include <math.h>

#define INACTIVE 0
#define POINT 1
#define LINE 2
#define RECTANGLE 3
#define HEXAGON 4
#define POLYLINE 5
#define CIRCLE 6
#define NUMBERPRIMITIVES 6
#define PI 3.1415926

#define REDX 0
#define BLUEX 1
#define GREENX 2
#define BLACKX 3

static int Color;

// Globals.
static int width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
static int primitive = INACTIVE; // Current drawing primitive.
static int pointCount = 0; // Number of  specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int isGrid = 0; // Is there grid?
static int isFilled = 0;

static float* px = NULL;
static float* py = NULL;

static float** ppx = NULL;
static float** ppy = NULL;

void colorChange(int i) {
	//std::cout << "Color: " << i << std::endl;
	if (i == BLACKX) {
		glColor3f(0.0, 0.0, 0.0);
	}
	else if (i == REDX) {
		glColor3f(1.0, 0.0, 0.0);
	}
	else if (i == BLUEX) {
		glColor3f(0.0, 0.0, 1.0);
	}
	else if (i == GREENX) {
		glColor3f(0.0, 1.0, 0.0);
	}

}

// Point class.
class Point
{
public:
	Point(float xVal, float yVal, float sizeVal, int c)
	{
		x = xVal; y = yVal; size = sizeVal;
		color = c;
	}
	Point() {};
	void drawPoint(void); // Function to draw a point.
private:
	float x, y; // x and y co-ordinates of point.
	float size; // Size of point.
	int color;
};

//float Point::size = pointSize; // Set point size.

// Function to draw a point.
void Point::drawPoint()
{
	glPointSize(size);
	colorChange(color);
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0.0);
	glEnd();
}

// Vector of points.
std::vector<Point> points;

// Iterator to traverse a Point array.
std::vector<Point>::iterator pointsIterator;

// Function to draw all points in the points array.
void drawPoints(void)
{
	// Loop through the points array drawing each point.
	for (auto point : points) { point.drawPoint(); }
}

// Line class.
class Line
{
public:
	Line(float x1Val, float y1Val, float x2Val, float y2Val, int c)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
		color = c;
	}
	Line() {};
	void drawLine();
private:
	float x1, y1, x2, y2; // x and y co-ordinates of endpoints.
	int color;
};


// Function to draw a line.
void Line::drawLine()
{
	colorChange(color);
	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glEnd();
}

// Vector of lines.
std::vector<Line> lines;

// Function to draw all lines in the lines array.
void drawLines(void)
{
	// Loop through the lines array drawing each line.
	for (auto line : lines) { line.drawLine(); }
}

// Rectangle class.
class Rect
{
public:
	Rect(float x1Val, float y1Val, float x2Val, float y2Val, bool f, int c)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
		filled = f;
		color = c;
	}
	Rect() {};
	void drawRectangle();
private:
	float x1, y1, x2, y2; // x and y co-ordinates of diagonally opposite vertices.
	bool filled;
	int color;
};

// Function to draw a rectangle.
void Rect::drawRectangle()
{
	colorChange(color);
	if (filled) {
		/*std::cout << "Filled" << std::endl;*/
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glRectf(x1, y1, x2, y2);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glRectf(x1, y1, x2, y2);
	}
}

// Vector of rectangles.
std::vector<Rect> rectangles;

// Function to draw all rectangles in the rectangles array.
void drawRectangles(void)
{
	// Loop through the rectangles array drawing each rectangle.
	for (auto rectangle : rectangles) { rectangle.drawRectangle(); }
}

class Circle
{
public:
	Circle(float posx, float posy, float radius, bool f, int c)
	{
		x = posx; y = posy; r = radius;
		filled = f;
		color = c;
	}
	Circle() {};
	void drawCircle();
private:
	float x, y, r;
	bool filled;
	int color;
};

// Function to draw a circles
void Circle::drawCircle()
{
	//����Բ��
	/*std::cout << "COLOR: " << Color << std::endl;*/
	colorChange(color);
	if (filled) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES);
		int n = 100;
		for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
		{
			//std::cout << x << " " << y <<  " " << r << std::endl;
			//glVertex2f(125 + 12.5 * cos(2 * PI * i / n), 235 + 12.5 * sin(2 * PI * i / n));
			glVertex2f(x, y);
			glVertex2f(x + r * cos(2 * PI * i / n), y + r * sin(2 * PI * i / n));
			glVertex2f(x + r * cos(2 * PI * (i + 1) / n), y + r * sin(2 * PI * (1 + i) / n));
		}
		glEnd();
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_LINE_LOOP);
		int n = 50;
		for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
		{
			//std::cout << x << " " << y <<  " " << r << std::endl;
			//glVertex2f(125 + 12.5 * cos(2 * PI * i / n), 235 + 12.5 * sin(2 * PI * i / n));
			glVertex2f(x + r * cos(2 * PI * i / n), y + r * sin(2 * PI * i / n));
		}
		glEnd();
	}


}

// Vector of circles
std::vector<Circle> circles;

// Function to draw all circles in the circles array.
void drawCircles(void)
{
	// Loop through the circles array drawing each circle.
	for (auto circle : circles) { circle.drawCircle(); }
}

class Hexagon
{
public:
	Hexagon(float posx, float posy, float distance, bool f, int c)
	{
		x = posx, y = posy, r = distance;
		filled = f;
		color = c;
	}
	Hexagon() {};
	void drawHexagon();
private:
	float x, y, r;
	bool filled;
	int color;
};

// Function to draw a Hexagon.
void Hexagon::drawHexagon()
{
	colorChange(color);
	std::cout << "CColor = " << color << std::endl;
	std::cout << "GColor = " << Color << std::endl;
	if (filled)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES);
		int n = 6;
		for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
		{
			glVertex2f(x, y);
			glVertex2f(x + r * cos(2 * PI * (i + 1) / n), y + r * sin(2 * PI * (i + 1) / n));
			glVertex2f(x + r * cos(2 * PI * i / n), y + r * sin(2 * PI * i / n));
		}
		glEnd();
	}
	else {
		//std::cout << "!" << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
		glBegin(GL_LINE_LOOP);
		int n = 6;
		for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
		{
			glVertex2f(x + r * cos(2 * PI * i / n), y + r * sin(2 * PI * i / n));
		}
		glEnd();
	}

}

// Vector of circles
std::vector<Hexagon> hexagons;

// Function to draw all circles in the circles array.
void drawHexagons(void)
{
	// Loop through the circles array drawing each circle.
	for (auto hexagon : hexagons) { hexagon.drawHexagon(); }
}

class Polylinex
{
public:
	Polylinex(float posx[], float posy[], int c, int co)
	{
		count = c;
		for (int i = 0; i < c; i++) {
			x[i] = posx[i];
			y[i] = posy[i];
			i++;
		};
	}
	Polylinex() {};
	void drawPolyline();
private:
	float x[20];
	float y[20];
	int count;
	int color;
};

// Function to draw a polyline
void Polylinex::drawPolyline()

{
	colorChange(color);
	//��������
	glBegin(GL_LINE_STRIP);
	std::cout << "drawPoly" << std::endl;
	for (int i = 0; i < count; i++) {
		std::cout << "px[" << i << "] = " << px[i] << "py[" << i << "] = " << py[i] << std::endl;
		glVertex2f(px[i], py[i]);
		std::cout << "i = " << i << std::endl;
	}
	glEnd();
}

// Vector of Polyline
std::vector<Polylinex> polylines;

// Function to draw all circles in the circles array.
void drawPolylines(void)
{
	// Loop through the circles array drawing each circle.
	for (auto polyline : polylines) { polyline.drawPolyline(); }
}

// Function to draw point selection box in left selection area.
void drawPointSelectionBox(void)
{
	if (primitive == POINT) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.98039, 0.50196, 0.44706); // No highlight.
	//pink
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.9 * height, 0.1 * width, height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.9 * height, 0.1 * width, height);

	// Draw point icon.
	glPointSize(pointSize);
	colorChange(Color);
	glBegin(GL_POINTS);
	glVertex3f(0.05 * width, 0.95 * height, 0.0);
	glEnd();
}

// Function to draw line selection box in left selection area.
void drawLineSelectionBox(void)
{
	if (primitive == LINE) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.98039, 0.50196, 0.44706); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.8 * height, 0.1 * width, 0.9 * height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.8 * height, 0.1 * width, 0.9 * height);

	// Draw line icon.
	colorChange(Color);
	glBegin(GL_LINES);
	glVertex3f(0.025 * width, 0.825 * height, 0.0);
	glVertex3f(0.075 * width, 0.875 * height, 0.0);
	glEnd();
}

// Function to draw rectangle selection box in left selection area.
void drawRectangleSelectionBox(void)
{
	if (primitive == RECTANGLE) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.98039, 0.50196, 0.44706); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.7 * height, 0.1 * width, 0.8 * height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.7 * height, 0.1 * width, 0.8 * height);

	// Draw rectangle icon.
	colorChange(Color);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glRectf(0.025 * width, 0.735 * height, 0.075 * width, 0.765 * height);
	if (isFilled) {
		/*std::cout << "Filled" << std::endl;*/
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glRectf(0.025 * width, 0.735 * height, 0.075 * width, 0.765 * height);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glRectf(0.025 * width, 0.735 * height, 0.075 * width, 0.765 * height);
	}
	glEnd();
}

void drawHexagonSelectionBox(void)
{
	if (primitive == HEXAGON) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.98039, 0.50196, 0.44706); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.6 * height, 0.1 * width, 0.7 * height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.6 * height, 0.1 * width, 0.7 * height);

	// Draw rectangle icon.
	colorChange(Color);
	//glBegin(GL_LINE_LOOP);
	////std::cout << "Drawing Hexagon" << std::endl;
	//glVertex2f((0.05 - 0.0125) * width, (0.65 + 0.0125) * height);
	//glVertex2f((0.05 + 0.0125) * width, (0.65 + 0.0125) * height);
	//glVertex2f((0.05 + 0.025) * width, (0.65 + 0.0) * height);
	//glVertex2f((0.05 + 0.0125) * width, (0.65 - 0.0125) * height);
	//glVertex2f((0.05 - 0.0125) * width, (0.65 - 0.0125) * height);
	//glVertex2f((0.05 - 0.025) * width, (0.65 + 0.0) * height);
	//glEnd();
	float x = 0.05 * width;
	float y = 0.65 * height;
	float r = 0.025 * width;
	if (isFilled)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES);
		int n = 6;
		for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
		{
			glVertex2f(x, y);
			glVertex2f(x + r * cos(2 * PI * (i + 1) / n), y + r * sin(2 * PI * (i + 1) / n));
			glVertex2f(x + r * cos(2 * PI * i / n), y + r * sin(2 * PI * i / n));
		}
		glEnd();
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
		glBegin(GL_LINE_LOOP);
		int n = 6;
		for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
		{
			glVertex2f(x + r * cos(2 * PI * i / n), y + r * sin(2 * PI * i / n));
		}
		glEnd();
	}
}

void drawPolylineSelectionBox(void)
{
	if (primitive == POLYLINE) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.98039, 0.50196, 0.44706); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.5 * height, 0.1 * width, 0.6 * height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.5 * height, 0.1 * width, 0.6 * height);

	// Draw rectangle icon.
	colorChange(Color);
	glBegin(GL_LINE_STRIP);
	glVertex2f((0.05 - 0.025) * width, (0.55 - 0.0125) * height);
	glVertex2f((0.05 - 0.0125) * width, (0.55 + 0.0125) * height);
	glVertex2f((0.05 - 0.0) * width, (0.55 - 0.0125) * height);
	glVertex2f((0.05 + 0.0125) * width, (0.55 + 0.0125) * height);
	glVertex2f((0.05 + 0.025) * width, (0.55 - 0.0125) * height);
	glEnd();
}

void drawCircleSelectionBox(void)
{
	if (primitive == CIRCLE) glColor3f(1.0, 1.0, 1.0); // Highlight.
	else glColor3f(0.98039, 0.50196, 0.44706); // No highlight.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.4 * height, 0.1 * width, 0.5 * height);

	// Draw black boundary.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.4 * height, 0.1 * width, 0.5 * height);

	// Draw rectangle icon.
	//glBegin(GL_LINE_LOOP);
	//colorChange(Color);
	//glBegin(GL_LINE_LOOP);

	//int n = 50;
	//for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
	//{
	//	glVertex2f(0.05 * width + 0.025 * width * cos(2 * PI * i / n), 0.45 * height + 0.025 * width * sin(2 * PI * i / n));
	//}
	//glEnd();
	float x = 0.05 * width;
	float y = 0.45 * height;
	float r = 0.025 * width;
	colorChange(Color);
	if (isFilled) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES);
		int n = 100;
		for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
		{
			//std::cout << x << " " << y <<  " " << r << std::endl;
			//glVertex2f(125 + 12.5 * cos(2 * PI * i / n), 235 + 12.5 * sin(2 * PI * i / n));
			glVertex2f(x, y);
			glVertex2f(x + r * cos(2 * PI * i / n), y + r * sin(2 * PI * i / n));
			glVertex2f(x + r * cos(2 * PI * (i + 1) / n), y + r * sin(2 * PI * (1 + i) / n));
		}
		glEnd();
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_LINE_LOOP);
		int n = 50;
		for (int i = 0; i < n; i++)     //ͨ����ѧ������������εĵ�
		{
			//std::cout << x << " " << y <<  " " << r << std::endl;
			//glVertex2f(125 + 12.5 * cos(2 * PI * i / n), 235 + 12.5 * sin(2 * PI * i / n));
			glVertex2f(x + r * cos(2 * PI * i / n), y + r * sin(2 * PI * i / n));
		}
		glEnd();
	}
}

// Function to draw unused part of left selection area.
void drawInactiveArea(void)
{
	glColor3f(0.98039, 0.50196, 0.44706);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(0.0, 0.0, 0.1 * width, (1 - NUMBERPRIMITIVES * 0.1) * height);

	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(0.0, 0.0, 0.1 * width, (1 - NUMBERPRIMITIVES * 0.1) * height);
}

// Function to draw temporary point.
void drawTempPoint(void)
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glVertex3f(tempX, tempY, 0.0);
	glEnd();
}
void drawPolyTempPoint()
{
	int i = 0;
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	if (px) {
		while (px[i]) {
			glVertex3f(px[i], py[i], 0.0);
			i++;
		}
	}
	glEnd();
}
// Function to draw a grid.
void drawGrid(void)
{
	int i;

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x5555);
	glColor3f(0.75, 0.75, 0.75);

	glBegin(GL_LINES);
	for (i = 2; i <= 9; i++)
	{
		glVertex3f(i * 0.1 * width, 0.0, 0.0);
		glVertex3f(i * 0.1 * width, height, 0.0);
	}
	for (i = 1; i <= 9; i++)
	{
		glVertex3f(0.1 * width, i * 0.1 * height, 0.0);
		glVertex3f(width, i * 0.1 * height, 0.0);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	drawPointSelectionBox();
	drawLineSelectionBox();
	drawRectangleSelectionBox();
	drawHexagonSelectionBox();
	drawPolylineSelectionBox();
	drawCircleSelectionBox();

	drawInactiveArea();
	drawPoints();
	drawLines();
	drawRectangles();
	drawCircles();
	drawHexagons();
	drawPolylines();

	if (((primitive == LINE) ||
		(primitive == RECTANGLE)) && (pointCount == 1) ||
		(primitive == CIRCLE) && (pointCount == 1) ||
		(primitive == HEXAGON) && (pointCount == 1))drawTempPoint();
	else if ((primitive == POLYLINE)) {
		drawPolyTempPoint();

	}

	if (isGrid) drawGrid();
	glutSwapBuffers();
}

// Function to pick primitive if click is in left selection area.
void pickPrimitive(int y)
{
	if (y < (1 - NUMBERPRIMITIVES * 0.1) * height) primitive = INACTIVE;
	else if (y < (1 - 5 * 0.1) * height) primitive = CIRCLE;
	else if (y < (1 - 4 * 0.1) * height) primitive = POLYLINE;
	else if (y < (1 - 3 * 0.1) * height) primitive = HEXAGON;
	else if (y < (1 - 2 * 0.1) * height) primitive = RECTANGLE;
	else if (y < (1 - 1 * 0.1) * height) primitive = LINE;
	else primitive = POINT;
}

// The mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		y = height - y; // Correct from mouse to OpenGL co-ordinates.

		if (x < 0 || x > width || y < 0 || y > height); // Click outside canvas - do nothing.

		// Click in left selection area.
		else if (x < 0.1 * width)
		{
			pickPrimitive(y);
			pointCount = 0;
		}

		// Click in canvas.
		else
		{
			if (primitive == POINT) points.push_back(Point(x, y, pointSize, Color));
			else if (primitive == LINE)
			{
				if (pointCount == 0)
				{
					tempX = x; tempY = y;
					pointCount++;
				}
				else
				{
					lines.push_back(Line(tempX, tempY, x, y, Color));
					pointCount = 0;
				}
			}
			else if (primitive == RECTANGLE)
			{
				if (pointCount == 0)
				{
					tempX = x; tempY = y;
					pointCount++;
				}
				else
				{
					rectangles.push_back(Rect(tempX, tempY, x, y, isFilled, Color));
					pointCount = 0;
				}
			}
			else if (primitive == HEXAGON) {
				if (pointCount == 0)
				{
					tempX = x, tempY = y;
					pointCount++;
				}
				else {
					if (pointCount == 0)
					{
						tempX = x; tempY = y;
						pointCount++;
					}
					else
					{
						/*std::cout << "x = " << x << std::endl;
						std::cout << "y = " << y << std::endl;
						std::cout << "tempX = " << tempX << std::endl;
						std::cout << "tempY = " << tempY << std::endl;*/
						float midX = (x + tempX) / 2.0;
						float midY = (y + tempY) / 2.0;
						//std::cout << "midX = " << midX << std::endl;
						//std::cout << "midY = " << midY << std::endl;
						float minusX = (x - tempX);
						float minusY = (y - tempY);
						/*std::cout << "minusX2 = " << minusX*minusX << std::endl;
						std::cout << "minusY2 = " << minusY*minusY << std::endl;*/
						float sum = minusX * minusX + minusY * minusY;
						float d = sqrt(sum);
						float r = d / 2.0;
						//std::cout << "r = " << r << std::endl;
						//circles.push_back(Circle(midX, midY, r));
						hexagons.push_back(Hexagon(midX, midY, r, isFilled, Color));
						pointCount = 0;
					}
				}
			}
			else if (primitive == CIRCLE) {
				if (pointCount == 0)
				{
					tempX = x; tempY = y;
					pointCount++;
				}
				else
				{
					/*std::cout << "x = " << x << std::endl;
					std::cout << "y = " << y << std::endl;
					std::cout << "tempX = " << tempX << std::endl;
					std::cout << "tempY = " << tempY << std::endl;*/
					float midX = (x + tempX) / 2.0;
					float midY = (y + tempY) / 2.0;
					//std::cout << "midX = " << midX << std::endl;
					//std::cout << "midY = " << midY << std::endl;
					float minusX = (x - tempX);
					float minusY = (y - tempY);
					/*std::cout << "minusX2 = " << minusX*minusX << std::endl;
					std::cout << "minusY2 = " << minusY*minusY << std::endl;*/
					float sum = minusX * minusX + minusY * minusY;
					float d = sqrt(sum);
					float r = d / 2.0;
					//std::cout << "r = " << r << std::endl;
					circles.push_back(Circle(midX, midY, r, isFilled, Color));
					pointCount = 0;
				}
			}
			else if (primitive == POLYLINE) {
				if (pointCount == 0) {
					px = new float[20];
					py = new float[20];
					std::cout << "pointCount = " << pointCount << std::endl;
					px[pointCount] = x;
					py[pointCount] = y;
					pointCount++;

				}
				else {
					std::cout << "h2" << pointCount << std::endl;
					px[pointCount] = x;
					py[pointCount] = y;
					pointCount++;
				}
			}
		}


	}
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		px[pointCount] = x;
		py[pointCount] = y;
		pointCount++;
		polylines.push_back(Polylinex(px, py, pointCount, Color));
		pointCount = 0;
	}
	glutPostRedisplay();
}
// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set viewing box dimensions equal to window dimensions.
	glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);

	// Pass the size of the OpenGL window to globals.
	width = w;
	height = h;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Clear the canvas and reset for fresh drawing.
void clearAll(void)
{
	points.clear();
	lines.clear();
	rectangles.clear();
	circles.clear();
	hexagons.clear();
	polylines.clear();


	primitive = INACTIVE;
	pointCount = 0;
}

// The right button menu callback function.

void rightMenu(int id)
{
	if (id == 1)
	{
		clearAll();
		glutPostRedisplay();
	}
	if (id == 2) exit(0);
}

// The sub-menu callback function.
void grid_menu(int id)
{
	if (id == 3) isGrid = 1;
	if (id == 4) isGrid = 0;
	glutPostRedisplay();
}
void color_menu(int id) {
	std::cout << "Colorid = " << id << std::endl;
	if (id == 7) {
		Color = BLACKX;
	}
	else if (id == 8) {
		Color = REDX;
	}
	else if (id == 9) {
		Color = BLUEX;
	}
	else if (id == 10) {
		Color = GREENX;
	}
	glutPostRedisplay();
	//std::cout << "GColor = " << Color << std::endl;
}
void filled_menu(int id) {
	if (id == 5) isFilled = 1;
	if (id == 6) isFilled = 0;
	glutPostRedisplay();
}
// Function to create menu.
void makeMenu(void)
{
	int sub_menu;
	int sub_menu1;
	int sub_menu2;

	sub_menu2 = glutCreateMenu(color_menu);
	glutAddMenuEntry("BLACK", 7);
	glutAddMenuEntry("RED", 8);
	glutAddMenuEntry("BLUE", 9);
	glutAddMenuEntry("GREEN", 10);

	sub_menu = glutCreateMenu(filled_menu);
	glutAddMenuEntry("On", 5);
	glutAddMenuEntry("Off", 6);

	sub_menu1 = glutCreateMenu(grid_menu);
	glutAddMenuEntry("On", 3);
	glutAddMenuEntry("Off", 4);



	glutCreateMenu(rightMenu);
	glutAddSubMenu("Grid", sub_menu1);
	glutAddSubMenu("Filled", sub_menu);
	glutAddSubMenu("Color", sub_menu2);
	glutAddMenuEntry("Clear", 1);
	glutAddMenuEntry("Quit", 2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	makeMenu(); // Create menu.
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Left click on a box on the left to select a primitive." << std::endl
		<< "Then left click on the drawing area: once for point, twice for line or rectangle." << std::endl
		<< "Right click for menu options." << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("canvas.cpp");
	//
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}