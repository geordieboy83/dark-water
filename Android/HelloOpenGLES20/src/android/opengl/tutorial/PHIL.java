package android.opengl.tutorial;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

import android.content.Context;

public class PHIL {

	protected float[] myVertices, myNormals;
	protected short[] myIndices;

			
//	protected long load(int obj, Context context, ArrayList<Vector> v, ArrayList<Vector> f){
	protected long load(int obj, Context context){
			long now=System.currentTimeMillis();
			
			ArrayList<Vector> v=new ArrayList<Vector>();
			ArrayList<Vector> vn=new ArrayList<Vector>();
			ArrayList<Vector> f=new ArrayList<Vector>();
			
			final InputStream inputStream = context.getResources().openRawResource(obj);
			final InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
			final BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
			
			String nextLine;
			char c;
			
			try
			{
				while ((nextLine = bufferedReader.readLine()) != null)
				{
					if(nextLine.isEmpty()) continue;
					
					if(nextLine.contains("vertices")){
						while ((nextLine = bufferedReader.readLine()) != null){
							if(nextLine.isEmpty()) continue;
							if(!Character.isDigit(c=nextLine.charAt(0))&&c!='-'&&c!='+') break;
//							if(nextLine.equalsIgnoreCase("faces")) 
//								break;
							Vector vtx=new Vector(nextLine);
							v.add(vtx);							
						}
							
					}
					
					if(nextLine.contains("faces")){
						while ((nextLine = bufferedReader.readLine()) != null){
							if(nextLine.isEmpty()) continue;
							Vector face=new Vector(nextLine);
							f.add(face);
							Vector normal= Vector.normal(v.get((int)face.x), v.get((int)face.y), v.get((int)face.z));
							for(int i=1; i<=3; i++) vn.add(Vector.clone(normal));						
						}
					}
				}
				bufferedReader.close();
			}
			catch (Throwable t){}
			
			myVertices=new float[3*v.size()];
			for(int i=0; i<v.size(); i++) {
				Vector vv=v.get(i);
				myVertices[3*i]=vv.x;
				myVertices[3*i+1]=vv.y;
				myVertices[3*i+2]=vv.z;
			}
			
			myNormals=new float[3*vn.size()];
			for(int i=0; i<vn.size(); i++) {
				Vector vvnn=vn.get(i);
				myNormals[3*i]=vvnn.x;
				myNormals[3*i+1]=vvnn.y;
				myNormals[3*i+2]=vvnn.z;
			}
			
			myIndices=new short[3*f.size()];
			for(int i=0; i<f.size(); i++){
				Vector ff=f.get(i);
				myIndices[3*i]=(short) ff.x;
				myIndices[3*i+1]=(short) ff.y;
				myIndices[3*i+2]=(short) ff.z;
			}
			
			v.clear(); vn.clear(); f.clear();
			Runtime.getRuntime().gc();
			
			return System.currentTimeMillis()-now;
		}	
		
//		protected void make(ArrayList<Vector> v, ArrayList<Vector> f){
//			myVertices=new float[3*3*f.size()];
//			myNormals=new float[3*3*f.size()];
//			
//			for(int i=0; i<f.size(); i++){
//				Face face= f.get(i);
//				
//				Vector v1=v.get(face.myVertices[0]-1), v2=v.get(face.myVertices[1]-1), v3=v.get(face.myVertices[2]-1);
//				
//				myVertices[9*i]=v1.x; myVertices[9*i+1]=v1.y; myVertices[9*i+2]=v1.z;
//				myVertices[9*i+3]=v2.x; myVertices[9*i+4]=v2.y; myVertices[9*i+5]=v2.z;
//				myVertices[9*i+6]=v3.x; myVertices[9*i+7]=v3.y; myVertices[9*i+8]=v3.z;
//				
//				if(face.myNormals[0]<=0||face.myNormals[1]<=0||face.myNormals[2]<=0){
//					// Calculate face normal; the OBJ does not provide
//					Vector n=Vector.normal(v1, v2, v3);
//					myNormals[9*i]=n.x; myNormals[9*i+1]=n.y; myNormals[9*i+2]=n.z;
//					myNormals[9*i+3]=n.x; myNormals[9*i+4]=n.y; myNormals[9*i+5]=n.z;
//					myNormals[9*i+6]=n.x; myNormals[9*i+7]=n.y; myNormals[9*i+8]=n.z;						
//				}				
//			}
//
//		}
		
		public PHIL(int plyresource, Context context){
//			ArrayList<Vector> vertices=new ArrayList<Vector>();
//			ArrayList<Vector> faces=new ArrayList<Vector>();
		
//			long loadtime=load(plyresource, context, vertices, faces);
			long loadtime=load(plyresource, context);
//			make(vertices, faces);		
			
//			System.out.println("Model: "+vertices.size()+" v, "+ faces.size()+" f, "+loadtime+" ms.");
			System.out.println("Model: "+myVertices.length+" v*3, "+myNormals.length+" vn*3, "+
					myVertices.length/9+" = "+myNormals.length/9+" = "+myIndices.length/3+" f.");
			
//			vertices.clear(); faces.clear();
			Runtime.getRuntime().gc();

		}



}
