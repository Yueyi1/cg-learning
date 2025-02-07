#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

Model *model = NULL;
const int width = 200;
const int height = 200;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror = std::abs(dy) * 2;
	int error = 0;
	int yincr = y1 > y0 ? 1 : -1;
	int eincr = 2 * dx;
	int y = y0;
	if (steep)
	{
		for (int x = x0; x <= x1; x++)
		{
			image.set(y, x, color);
			error += derror;
			if (error > dx)
			{
				y += yincr;
				error -= eincr;
			}
		}
	}
	else
	{
		for (int x = x0; x <= x1; x++)
		{
			image.set(x, y, color);
			error += derror;
			if (error > dx)
			{
				y += yincr;
				error -= eincr;
			}
		}
	}
}

Vec3f barycentric(Vec2i *pts, Vec2i P)
{
	Vec3f u = Vec3f(pts[2].x - pts[0].x, pts[1].x - pts[0].x, pts[0].x - P.x) ^ Vec3f(pts[2].y - pts[0].y, pts[1].y - pts[0].y, pts[0].y - P.y);
	/* `pts` and `P` has integer value as coordinates
	   so `abs(u[2])` < 1 means `u[2]` is 0, that means
	   triangle is degenerate, in this case return something with negative coordinates */
	if (std::abs(u.z) < 1)
		return Vec3f(-1, 1, 1);
	return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color)
{
	// line sweeping
	if (t0.y == t1.y && t0.y == t2.y)
		return; // i dont care about degenerate triangles
	if (t0.y > t1.y)
		std::swap(t0, t1);
	if (t0.y > t2.y)
		std::swap(t0, t2);
	if (t1.y > t2.y)
		std::swap(t1, t2);
	int total_height = t2.y - t0.y;
	for (int i = 0; i < total_height; i++)
	{
		bool second_half = i > t1.y - t0.y || t1.y == t0.y;
		int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
		float alpha = (float)i / total_height;
		float beta = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height; // be careful: with above conditions no division by zero here
		Vec2i A = t0 + (t2 - t0) * alpha;
		Vec2i B = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
		if (A.x > B.x)
			std::swap(A, B);
		for (int j = A.x; j <= B.x; j++)
		{
			image.set(j, t0.y + i, color); // attention, due to int casts t0.y+i != A.y
		}
	}
}

void triangle(Vec2i *pts, TGAImage &image, TGAColor color)
{
	// barycentric
	Vec2i bboxmin(image.get_width() - 1, image.get_height() - 1);
	Vec2i bboxmax(0, 0);
	Vec2i clamp(image.get_width() - 1, image.get_height() - 1);
	for (int i = 0; i < 3; i++)
	{
		bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
		bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));

		bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
		bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
	}
	Vec2i P;
	for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++)
	{
		for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++)
		{
			Vec3f bc_screen = barycentric(pts, P);
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
				continue;
			image.set(P.x, P.y, color);
		}
	}
}

int main(int argc, char **argv)
{
	// if (2==argc) {
	//     model = new Model(argv[1]);
	// } else {
	//     model = new Model("obj/african_head.obj");
	// }

	TGAImage image(width, height, TGAImage::RGB);
	// for (int i=0; i<model->nfaces(); i++) {
	//     std::vector<int> face = model->face(i);
	//     for (int j=0; j<3; j++) {
	//         Vec3f v0 = model->vert(face[j]);
	//         Vec3f v1 = model->vert(face[(j+1)%3]);
	//         int x0 = (v0.x+1.)*width/2.;
	//         int y0 = (v0.y+1.)*height/2.;
	//         int x1 = (v1.x+1.)*width/2.;
	//         int y1 = (v1.y+1.)*height/2.;
	//         line(x0, y0, x1, y1, image, white);
	//     }
	// }

	// image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	// image.write_tga_file("output.tga");
	// delete model;

	// triangle
	Vec2i t0[3] = {Vec2i(10, 70), Vec2i(50, 160), Vec2i(70, 80)};
	Vec2i t1[3] = {Vec2i(180, 50), Vec2i(150, 1), Vec2i(70, 180)};
	Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};
	triangle(t0[0], t0[1], t0[2], image, red);
	triangle(t1[0], t1[1], t1[2], image, white);
	triangle(t2[0], t2[1], t2[2], image, green);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

	TGAImage frame(200, 200, TGAImage::RGB);
	Vec2i pts[3] = {Vec2i(10, 10), Vec2i(100, 30), Vec2i(190, 160)};
	triangle(pts, frame, TGAColor(255, 0, 0, 255));
	frame.flip_vertically(); // to place the origin in the bottom left corner of the image
	frame.write_tga_file("framebuffer.tga");

	return 0;
}
