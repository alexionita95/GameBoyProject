class Object{
	
	protected:
	int x, y, width, height, backColor, foreColor;
	
	public:
	
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	int getWidth()
	{
		return width;
	}
	int getHeight()
	{
		return height;
	}
	int getBackColor()
	{
		return backColor;
	}
	int getForeColor()
	{
		return foreColor;
	}
	
	void setX(int val)
	{
		x=val;
	}
	void setY(int val)
	{
		y=val;
	}
	void setWidth(int val)
	{
		width=val;
	}
	void setHeight(int val)
	{
		height=val;
	}
	void setBackColor(int val)
	{
		backColor=val;
	}
	void setForeColor(int val)
	{
		foreColor=val;
	}
	
	virtual void render()=0;
	virtual void update()=0;
};