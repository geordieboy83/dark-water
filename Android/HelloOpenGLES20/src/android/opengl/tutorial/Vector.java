package android.opengl.tutorial;

public class Vector {

	protected float x=0;
	protected float y=0;
	protected float z=0;
	protected float magnitude=0;
	
	
	public Vector(){}
	
	public Vector(float[] vertices, short index){
		
		try{
			x=vertices[3*index];
			y=vertices[3*index+1];
			z=vertices[3*index+2];
			magn();
			
		}catch(Throwable t){}
		
	}
	
	public Vector(float xcoord, float ycoord, float zcoord){
		x=xcoord;
		y=ycoord;
		z=zcoord;		
		magn();
	}
	
	public Vector(String line){
		String substrings[]=line.split(" ");	
		try{
			set_coords(
				Float.valueOf(substrings[substrings.length-3]),
				Float.valueOf(substrings[substrings.length-2]),
				Float.valueOf(substrings[substrings.length-1]));
		}catch(Throwable t){}
		magn();
	}
	
	

	// Remake vector.
	public void set_coords(float newx, float newy, float newz) { x=newx; y=newy; z=newz; magn(); }

	// Calculate magnitude.
	public void magn() { magnitude=(float) Math.sqrt(x*x+y*y+z*z); return; }

	// Scale.
	public void scale(float a) { set_coords(a*x, a*y, a*z); magn(); return; }

	// Convert into unit vector.
	public void unit() { if (magnitude==0) return; scale(1/magnitude); magnitude=1; return; }

	public final float get_magn() { return magnitude; }

	// Add two vectors.
	public static Vector add (Vector p, Vector q)
	{
		return new Vector(p.getx()+q.getx(),p.gety()+q.gety(),p.getz()+q.getz());
	}

	// Subtract two vectors.
	public static Vector subtract (Vector p, Vector q)
	{
		return new Vector(p.getx()-q.getx(),p.gety()-q.gety(),p.getz()-q.getz());
	}


	// Dot product.
	public static float dot(Vector p, Vector q)
	{
		return p.getx()*q.getx()+p.gety()*q.gety()+p.getz()*q.getz();
	}


	// Angle between two vectors.
	public static float angle(Vector p, Vector q)
	{
		return (float) Math.acos(dot(p,q)/(p.get_magn()*q.get_magn()));
	}


	// Two vector cross product.
	public static Vector cross(Vector p, Vector q)
	{
		return new Vector((p.gety()*q.getz()-p.getz()*q.gety()),(p.getz()*q.getx()-p.getx()*q.getz()),(p.getx()*q.gety()-p.gety()*q.getx()));
	}

	// Unit normal from two vectors.
	public static Vector normal(Vector p, Vector q)
	{
		float scalar=(float) (p.get_magn()*q.get_magn()*Math.sin(angle(p,q)));
		Vector v=cross(p,q);
		v.scale(scalar);
		return v;
	}

	// Unit normal from three position vectors.
	public static Vector normal(Vector p, Vector q, Vector r)
	{
		Vector v=cross(subtract(p,q), subtract(q,r));
		v.unit();
		return v;
	}	

	// Get methods.
	public final float getx() { return x; }
	public final float gety() { return y; }
	public final float getz() { return z; }


	// Vector negation functionality.
	public void negate()  { x=-x; y=-y; z=-z; return; }	

	// Vector translation functionality.
	public void translate(Vector p) {set_coords(x=x+p.getx(), y=y+p.gety(), z=z+p.getz()); return;}



}
