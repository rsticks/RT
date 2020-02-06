#include <stdio.h>
#include <math.h>

float arch(float x)
{
	return log(x + sqrt(powf(x, 2) - 1));
}

float arsh(float x)
{
	return log(x + sqrt(powf(x, 2) + 1));
}

float sgn(float x)
{
	if (x < 0)
		return (-1);
	else if (x > 0)
		return (1);
	else
		return (x);
}

float solution_equation_3(float a, float b, float c)
{
	float q;
	float r;
	float s;
	float fi;
	float root;

	q = (powf(a, 2) - 3 * b) / 9;
	r = (2 * powf(a, 3) - 9 * a * b + 27 * c) / 54;
	s = powf(q, 3) - powf(r, 2);

	if ((int)s > 0.0)
	{
		fi = (1 / 3) * acos(r / sqrt(powf(q, 3)));
		root = -2 * sqrt(q) * cos(fi) - (a / 3);
	}
	else if ((int)s < 0.0 && (int)q > 0.0)
	{
		fi = (1 / 3) * arch(fabsf(r) / sqrt(powf(q, 3)));
		root = -2 * sgn(r) * sqrt(q) * cosh(fi) - (a / 3);
	}
	else if ((int)s < 0.0 && (int)q < 0.0)
	{
		fi = (1 / 3) * arsh(fabsf(r) / sqrt(powf(q, 3)));
		root = -2 * sgn(r) * sqrt(fabsf(q)) * sinh(fi) - (a / 3);
	}
	else if ((int)s < 0.0 && (int)q == 0.0)
		root = (-1) * cbrtf(c - (powf(a, 3) / 27)) - (a / 3);
	else if ((int)s == 0.0)
		root = -2 * cbrtf(r) - (a / 3);
	return root;
}

float solution_cordan(float a, float b, float c, float d)
{
	float p;
	float q;
	float qq;
	float alpha;
	float betta;
	float root;

	p = (3 * a * c - powf(b, 2)) / (3 * powf(a, 2));
	q = (2 * powf(b, 3) - 9 * a * b * c + 27 * powf(a, 2) * d) / (27 * powf(a, 3));
	qq = powf(p / 3, 3) + powf(q / 2, 2);

	printf("cbrtf(qq) = %g\n", cbrtf((-1) * (q / 2) + sqrtf((int)qq)));

	if (qq >= 0) {
		if (sqrtf(qq) == NAN) {
			printf("sqrt(qq) = %g\n", sqrtf((int) qq));
			alpha = cbrtf((-1) * (q / 2) + sqrtf((int) qq));
			betta = cbrtf((-1) * (q / 2) - sqrtf((int) qq));
		} else {
			printf("sqrt(qq) = %g\n", sqrtf(qq));
			alpha = cbrtf((-1) * (q / 2) + sqrtf(qq));
			betta = cbrtf((-1) * (q / 2) - sqrtf(qq));
		}
	}
	root = alpha + betta - (b / (3 * a));
	return root;
}

float ft_grad(float a, float b, float c, float d, float x)
{
	return 4 * a * pow(x, 3) + 3 * b * pow(x, 2) + 2 * c * x + d;
}

float solution_grad(float a, float b, float c, float d)
{
	float x;
	float x_next;
	float leambda;
	int inter_count;


	x = 1;
	leambda = 0.5;
	x_next = x - leambda * ft_grad(a, b , c , d, x);
	printf("x = %g, ft_grad = %g x_next = %g\n", x, ft_grad(a, b , c , d, x), x - leambda * ft_grad(a, b , c , d, x));
	inter_count = 0;
	while(inter_count < 200 && fabsf(x_next - x) > 0.001)
	{
		x = x_next;
		x_next = x - leambda * ft_grad(a, b , c , d, x);
		printf("x = %g, ft_grad = %g x_next = %g\n", x, ft_grad(a, b , c , d, x), x - leambda * ft_grad(a, b , c , d, x));
		inter_count++;
	}
	return (float)x_next;
}

float			get_quadratic_solution(double a, double b, double discriminant)
{
	double		t1;
	double		t2;

	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}

float solution_Viet_Cord(float a, float b, float c)
{
	float q, q3;
	float r, r2;
	float aa;
	float bb;
	float t;

	q = (powf(a, 2) - 3 * b) / 9;
	r = (2 * powf(a, 3) - 9 * a * b + 27 * c) / 54;
	r2 = pow(r, 2);
	q3 = pow(q, 3);
	if (r2 < q3)
	{
		t = acosf(r / sqrtf(q3));
		a /= 3.0;
		q = (-1) * 2 * sqrtf(q);
		return(q * cosf(t / 3) - a);
	}
	else
	{
		if (r <= 0.0)
			r = -r;
		aa = -powf(r + sqrtf(r2 - q3), 1.0 / 3.0);
		if (aa != 0.0)
			bb = q / aa;
		else
			bb = 0.0;
		a /= 3.0;
		q = aa + bb;
		return(q - a);
	}
}

float solution_Ferrary(float a, float b, float c, float d)
{
	float a_3, b_3, c_3;
	float n, m, discriminant;
	float y_root;
	float main_root_1, main_root_2;

	a_3 = -b;
	b_3 = a * c - 4.0 * d;
	c_3 = (-1) * (powf(c, 2) + d * (powf(a, 2) - 4.0 * b));
	y_root = solution_Viet_Cord(a_3, b_3, c_3);

	n = sqrtf(powf(y_root, 2) / 4.0 - d);
	m = sqrtf(powf(a, 2) / 4.0 - b + y_root);

	a_3 = 1;
	b_3 = a / 2.0 - m;
	c_3 = y_root / 2.0 - n;
	discriminant = powf(b_3, 2) - 4 * a_3 * c_3;
	main_root_1 = get_quadratic_solution(a_3, b_3, discriminant);

	a_3 = 1;
	b_3 = a / 2.0 + m;
	c_3 = y_root / 2.0 + n;
	discriminant = powf(b_3, 2) - 4 * a_3 * c_3;
	main_root_2 = get_quadratic_solution(a_3, b_3, discriminant);

	if (main_root_1 != -1.0)
		return (main_root_1);
	else if (main_root_2 != -1.0)
		return (main_root_2);
	return (-1);
}

int main()
{
	float root;
	float a, b, c, d, e;

	a = 0;
	b = -1;
	c = 2;
	d = -1;
	
	//root = solution_Viet_Cord(a, b, c);
	//printf("root = %g\n", root);
	//printf("equation = %g\n", powf(root, 3) + a * powf(root, 2) + b * root + c);

	root = solution_Ferrary(a, b, c, d);
	printf("root = %g\n", root);
	printf("equation = %g\n", powf(root, 4) + a * powf(root, 3) + b * powf(root, 2) + c * root + d);

	return 0;
}
