package android.opengl.tutorial;

import java.util.ArrayList;

public class Face {

//	public float myData[];
//	
//	public Face(float xyz[], float rgba[], float st[], float vn[], short ixyz[], short irgba[], short ist[], short ivn[]){
//		Vertex vertices[]=new Vertex[Model.VERTICES_PER_FACE];
//		for(int i=0; i<vertices.length; i++) vertices[i]=
//				new Vertex(xyz,rgba,st,vn,ixyz[i],(irgba!=null?irgba[i]:0),(ist!=null?ist[i]:0),(ivn!=null?ivn[i]:0));
//		
//		
//	}
	
	public int[] myTextureI={-1,-1,-1}, myVertexI={-1,-1,-1}, myNormalI={-1,-1,-1};
	
	
	
	public Face(){}
	
	public Face(String line){		
		String substrings[]=line.split(" ");
		for(int i=substrings.length-3; i<substrings.length; i++){
		String vertexindices[]=substrings[i].split("/");
			myVertexI[i-(substrings.length-3)]=
					!vertexindices[vertexindices.length-3].isEmpty()?Integer.valueOf(vertexindices[vertexindices.length-3]):-1;
			myTextureI[i-(substrings.length-3)]=		
					!vertexindices[vertexindices.length-2].isEmpty()?Integer.valueOf(vertexindices[vertexindices.length-2]):-1;
			myNormalI[i-(substrings.length-3)]=
					!vertexindices[vertexindices.length-1].isEmpty()?Integer.valueOf(vertexindices[vertexindices.length-1]):-1;
		}
		
	}
	
	
	
}
