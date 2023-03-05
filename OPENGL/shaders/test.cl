
float4 VelFun(float4 pos)
{
	return (float4)(pos.x+cos(pos.x-pos.y)*0.001, pos.y+sin(pos.y+pos.x)*0.1*pos.y, 1.0, 1.0);
} 

__kernel void add(__global float4* position, __global float4* velocity, int num_particles,  float time)
{
	int gid = get_global_id(0);
	float4 Mine = (float4)(-1.0, -1.0, -1.0, -1.0);
	float4 Maxe = (float4)(1.0, 1.0, 1.0, 1.0);
	position[gid] = position[gid] + 0.001;
	
	
}