
int xorshift32(int* state)
{
	/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
	int x = *state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
    *state = x;
	return x;
};

__kernel void ray_gen( 
    __global float* ray_data, 
    int antialiasing, 
    int width, 
    int height, 
    float upx, 
    float upy,
    float upz,
    float sidex, 
    float sidey,
    float sidez,  
    float screen_centerx, 
    float screen_centery,
    float screen_centerz,
    float aspect_ratio, 
    float cameraposx,
    float cameraposy,
    float cameraposz,
    int ray_size
    )
{
    int x = get_global_id( 0 );
    int y = get_global_id( 1 );

	int rand = x * y + 1 ;

	for (int n = 0; n < antialiasing; n++) {
		float px = ((float)x + (float)xorshift32(&rand) / (float)2147483647) / (float)width;
		float py = ((float)y + (float)xorshift32(&rand) / (float)2147483647) / (float)height;
		
        float dirx = screen_centerx + (sidex * ((px - 0.5f) * aspect_ratio)) + (upx * ((py * -1) + 0.5f));
        float diry = screen_centery + (sidey * ((px - 0.5f) * aspect_ratio)) + (upy * ((py * -1) + 0.5f));
        float dirz = screen_centerz + (sidez * ((px - 0.5f) * aspect_ratio)) + (upz * ((py * -1) + 0.5f));
        dirx = dirx - cameraposx;
        diry = diry - cameraposy;
        dirz = dirz - cameraposz;
		float3 dir = (float3)(dirx, diry, dirz);
		dir = normalize(dir);
		ray_data[((x + width * y) * antialiasing + n) * ray_size] = cameraposx;
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 1] = cameraposy;
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 2] = cameraposz;
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 4] = dir.x;
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 5] = dir.y;
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 6] = dir.z;
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 8] = 1.f/dir.x;
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 9] = 1.f/dir.y;
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 10] = 1.f/dir.z;
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 16] = 999999999.f; //distance tointersection
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 17] = 0; // hitptr
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 18] = 3; // 3 equates to nothing primative
        ray_data[((x + width * y) * antialiasing + n) * ray_size + 19] = 0; // complexity
	}
}
