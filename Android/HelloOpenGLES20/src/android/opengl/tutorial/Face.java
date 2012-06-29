package android.opengl.tutorial;

public class Face {

	public float myData[];
	
	public Face(float xyz[], float rgba[], float st[], float vn[], short ixyz[], short irgba[], short ist[], short ivn[]){
		Vertex vertices[]=new Vertex[Model.VERTICES_PER_FACE];
		for(int i=0; i<vertices.length; i++) vertices[i]=
				new Vertex(xyz,rgba,st,vn,ixyz[i],(irgba!=null?irgba[i]:0),(ist!=null?ist[i]:0),(ivn!=null?ivn[i]:0));
		
		
	}
	
}
