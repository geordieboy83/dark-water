package android.opengl.tutorial;

public class CBO extends BufferObject {

	public CBO(float[] data) {
		super(data, Shaders.ATTR_COL, Model.COLOUR_COMPONENTS_PER_VERTEX);
	}
	
	public CBO(int vertices, float r, float g, float b, float a){
		this(fromRGBA(vertices, r,g,b,a));
	}
	
	
	public CBO(int vertices, float rgba[]){
		this(fromRGBA(vertices, rgba));
	}
	
	
	protected static float[] fromRGBA(int vertices, float rgba[]){
		if(rgba==null||rgba.length<4) return null;
		return fromRGBA(vertices, rgba[0],rgba[1],rgba[2],rgba[3]);
	}
	
	
	protected static float[] fromRGBA(int vertices, float r, float g, float b, float a){
		if(vertices <=0) return null;
		float result[]=new float[4*vertices];
		for(int i=0; i<vertices; i++) {			
			result[4*i]=r;
			result[4*i+1]=g;
			result[4*i+2]=b;
			result[4*i+3]=a;
		}
		return result;
	}

}
