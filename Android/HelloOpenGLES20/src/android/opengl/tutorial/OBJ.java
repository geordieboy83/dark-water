package android.opengl.tutorial;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.apache.commons.io.IOUtils;

import android.content.Context;

public class OBJ {
	
	protected float[] myVertices, myNormals, myTextures, myMaterial;

		
	protected long load(int obj, Context context, ArrayList<Vector> v, ArrayList<Vector> vn, ArrayList<Vector> vt, ArrayList<Face> f){
		long now=System.currentTimeMillis();
		
		if(v==null||vn==null||vt==null||f==null) return 0;
		
		v.clear(); vn.clear(); vt.clear(); f.clear();
		
		final InputStream inputStream = context.getResources().openRawResource(obj);
		final InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
		final BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
		
		String nextLine;
		
		try
		{
			while ((nextLine = bufferedReader.readLine()) != null)
			{
				if(nextLine.isEmpty()||nextLine.startsWith("#")) continue;
				
				if(nextLine.startsWith("vn")){
//					vn.add(readFloatData(nextLine));
					vn.add(new Vector(nextLine));
				}
				else if(nextLine.startsWith("vt")){
//					vt.add(readFloatData(nextLine));
					vt.add(new Vector(nextLine));
				}
				else if(nextLine.startsWith("v")){
//					v.add(readFloatData(nextLine));
					v.add(new Vector(nextLine));
				}
				else if(nextLine.startsWith("f")){					
//					f.add(readIntegerData(nextLine));
					f.add(new Face(nextLine));
				}
			}
			bufferedReader.close();
		}
		catch (Throwable t){}
		
		return System.currentTimeMillis()-now;
	}	
	
//	protected Vector readFloatData(String line){
//		String substrings[]=line.split(" ");		
//		Vector result=new Vector();
//		try{
//			result.set_coords(
//					Float.valueOf(substrings[substrings.length-3]),
//					Float.valueOf(substrings[substrings.length-2]),
//					Float.valueOf(substrings[substrings.length-1]));
//		}catch(Throwable t){}
//		return result;
//	}
	
//	protected Face readIntegerData(String line){
//		String substrings[]=line.split(" ");
//		Face result=new Face();
//		for(int i=substrings.length-3; i<substrings.length; i++){
//			String vertexindices[]=substrings[i].split("/");
//			result.myVertices[i-(substrings.length-3)]=
//					!vertexindices[vertexindices.length-3].isEmpty()?Integer.valueOf(vertexindices[vertexindices.length-3]):-1;
//			result.myTextures[i-(substrings.length-3)]=		
//					!vertexindices[vertexindices.length-2].isEmpty()?Integer.valueOf(vertexindices[vertexindices.length-2]):-1;
//			result.myNormals[i-(substrings.length-3)]=
//					!vertexindices[vertexindices.length-1].isEmpty()?Integer.valueOf(vertexindices[vertexindices.length-1]):-1;
//		}
//		return result;
//	}
	
	
	protected void make(ArrayList<Vector> v, ArrayList<Vector> vn, ArrayList<Vector> vt, ArrayList<Face> f){
		myVertices=new float[3*3*f.size()];
		if(!vt.isEmpty()) myTextures=new float[3*2*f.size()];
		myNormals=new float[3*3*f.size()];
		
		for(int i=0; i<f.size(); i++){
			Face face= f.get(i);
			
			Vector v1=v.get(face.myVertexI[0]-1), v2=v.get(face.myVertexI[1]-1), v3=v.get(face.myVertexI[2]-1);
			
			myVertices[9*i]=v1.x; myVertices[9*i+1]=v1.y; myVertices[9*i+2]=v1.z;
			myVertices[9*i+3]=v2.x; myVertices[9*i+4]=v2.y; myVertices[9*i+5]=v2.z;
			myVertices[9*i+6]=v3.x; myVertices[9*i+7]=v3.y; myVertices[9*i+8]=v3.z;
			
			if(face.myNormalI[0]<=0||face.myNormalI[1]<=0||face.myNormalI[2]<=0){
				// Calculate face normal; the OBJ does not provide
				Vector n=Vector.normal(v1, v2, v3);
				myNormals[9*i]=n.x; myNormals[9*i+1]=n.y; myNormals[9*i+2]=n.z;
				myNormals[9*i+3]=n.x; myNormals[9*i+4]=n.y; myNormals[9*i+5]=n.z;
				myNormals[9*i+6]=n.x; myNormals[9*i+7]=n.y; myNormals[9*i+8]=n.z;						
			}
			else{
				
				v1=vn.get(face.myNormalI[0]-1); v2=vn.get(face.myNormalI[1]-1); v3=vn.get(face.myNormalI[2]-1);
				myNormals[9*i]=v1.x; myNormals[9*i+1]=v1.y; myNormals[9*i+2]=v1.z;
				myNormals[9*i+3]=v2.x; myNormals[9*i+4]=v2.y; myNormals[9*i+5]=v2.z;
				myNormals[9*i+6]=v3.x; myNormals[9*i+7]=v3.y; myNormals[9*i+8]=v3.z;
			}
			
			if(myTextures!=null){
				v1=vt.get(face.myTextureI[0]-1); v2=vt.get(face.myTextureI[1]-1); v3=vt.get(face.myTextureI[2]-1);
				myTextures[6*i]=v1.x; myTextures[6*i+1]=v1.y;
				myTextures[6*i+2]=v2.x; myTextures[6*i+3]=v2.y;
				myTextures[6*i+4]=v3.x; myTextures[6*i+5]=v3.y;
			}
			
			
			
		}

	}
	
	public OBJ(int objresource, Context context){
		ArrayList<Vector> vertices=new ArrayList<Vector>(), normals=new ArrayList<Vector>(), textures=new ArrayList<Vector>();
		ArrayList<Face> faces=new ArrayList<Face>();
	
		long loadtime=load(objresource, context, vertices, normals, textures, faces);
		make(vertices, normals, textures, faces);		
		
		System.out.println("Model: "+vertices.size()+" v, "+normals.size()+" vn, "+ textures.size()+" vt, "+ faces.size()+" f, "+loadtime+" ms.");
		System.out.println("Model: "+myVertices.length+" v*3, "+myNormals.length+" vn*3, "+ (myTextures==null?0:myTextures.length)+" vt*2, "+
				myVertices.length/9+" = "+myNormals.length/9+" = "+(myTextures==null?0:myTextures.length/6)+" f.");
		
		vertices.clear(); normals.clear(); textures.clear(); faces.clear();
		Runtime.getRuntime().gc();

	}

}
