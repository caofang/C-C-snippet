class Circle
{
private:
	float radius;
	float area;
	float circumference;

	void setArea();
	void setCircumference();

public:
	Circle();
	void setRadius(float r);	// will automatically compute area and circumferenc
	float getRadius();
	float getArea();
	float getCircumference();
};