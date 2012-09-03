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
	public Vector[] myTextures=new Vector[3], myVertices=new Vector[3], myNormals=new Vector[3];
	
	
	public Face(String line, ArrayList<Vector> vertices, ArrayList<Vector> textures, ArrayList<Vector> normals){
		this(line);
		if(Character.isDigit(line.charAt(0))){
			// Phil's model
			for(int i=0; i<3; i++) myVertices[i]=Vector.clone(vertices.get(myVertexI[i]));
			Vector normal= Vector.normal(myVertices[0], myVertices[1], myVertices[2]);
			for(int i=0; i<3; i++) myNormals[i]=Vector.clone(normal);			
		}
		else{
			// OBJ
			for(int i=0; i<3; i++){
				myVertices[i]=Vector.clone(vertices.get(myVertexI[i]-1));
				if(textures!=null&&!textures.isEmpty()&&myTextureI[i]!=-1) myTextures[i]=Vector.clone(vertices.get(myTextureI[i]-1));
				if(normals!=null&&!normals.isEmpty()&&myNormalI[i]!=-1) myNormals[i]=Vector.clone(vertices.get(myNormalI[i]-1));
			}
			if(myNormalI[0]==-1){
				Vector normal= Vector.normal(myVertices[0], myVertices[1], myVertices[2]);
				for(int i=0; i<3; i++) myNormals[i]=Vector.clone(normal);
			}
			
		}
	}
	
	public Face(){}
	
	public Face(String line){		
		String substrings[]=line.split(" ");
		for(int i=substrings.length-3; i<substrings.length; i++){
			String vertexindices[]=substrings[i].split("/");
			try{
				myVertexI[i-(substrings.length-3)]=
						!vertexindices[0].isEmpty()?Integer.valueOf(vertexindices[0]):-1;
				myTextureI[i-(substrings.length-3)]=		
						!vertexindices[1].isEmpty()?Integer.valueOf(vertexindices[1]):-1;
				myNormalI[i-(substrings.length-3)]=
						!vertexindices[2].isEmpty()?Integer.valueOf(vertexindices[2]):-1;

			}
			catch(Throwable t){}
//			myVertexI[i-(substrings.length-3)]=
//					!vertexindices[vertexindices.length-3].isEmpty()?Integer.valueOf(vertexindices[vertexindices.length-3]):-1;
//			myTextureI[i-(substrings.length-3)]=		
//					!vertexindices[vertexindices.length-2].isEmpty()?Integer.valueOf(vertexindices[vertexindices.length-2]):-1;
//			myNormalI[i-(substrings.length-3)]=
//					!vertexindices[vertexindices.length-1].isEmpty()?Integer.valueOf(vertexindices[vertexindices.length-1]):-1;
		}
		
	}
	
	
	
}
