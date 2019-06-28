#include "rt.h"
#include <unistd.h>
#include <math.h>

t_vector			rt_tperlin(t_vector normal, t_vector intercolor, t_env *env,
						t_inter *inter)
{
	// static int		tftype[NBR_FORM] = {SPHERE, PLAN, CYLINDRE, CONE};
	// static t_vector	(*func[NBR_FORM])(t_vector, t_vector, t_inter*,
	// 	t_form*) = {rt_perlin_sphere, rt_perlin_plan,
	// 	rt_perlin_cylindre, rt_perlin_cone};

	(void)normal;
	(void)env;
	(void)intercolor;
	(void)inter;
	
	// printf("%f\n", );

	return (intercolor);
}


