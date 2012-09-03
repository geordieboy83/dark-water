package android.opengl.tutorial;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

import android.content.Context;

public class PHIL {

	protected float[] myVertices, myNormals;
	protected short[] myIndices;

	protected Vector min=new Vector(Float.MAX_VALUE, Float.MAX_VALUE, Float.MAX_VALUE),
			max=new Vector(Float.MIN_VALUE, Float.MIN_VALUE, Float.MIN_VALUE);
	
	
	protected long load2(int obj, Context context){
			long now=System.currentTimeMillis();
			
			ArrayList<Vector> v=new ArrayList<Vector>();
			ArrayList<Vector> vn=new ArrayList<Vector>();
			ArrayList<Face> f= new ArrayList<Face>();
			
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
							Vector vtx=new Vector(nextLine);
							v.add(vtx);							
						}
							
					}
					
					if(nextLine.contains("faces")){
						while ((nextLine = bufferedReader.readLine()) != null){
							if(nextLine.isEmpty()) continue;
							Face face = new Face(nextLine,v,null,null);
							f.add(face);						
						}
					}
				}
				bufferedReader.close();
			}
			catch (Throwable t){}
			
			myVertices=new float[f.size()*3*3];
			myNormals=new float[f.size()*3*3];
			for(int i=0; i<f.size(); i++){
				Face ff=f.get(i);
				myVertices[9*i] = ff.myVertices[0].x; myVertices[9*i+1] = ff.myVertices[0].y; myVertices[9*i+2] = ff.myVertices[0].z;
				myVertices[9*i+3] = ff.myVertices[1].x; myVertices[9*i+4] = ff.myVertices[1].y; myVertices[9*i+5] = ff.myVertices[1].z;
				myVertices[9*i+6] = ff.myVertices[2].x; myVertices[9*i+7] = ff.myVertices[2].y; myVertices[9*i+8] = ff.myVertices[2].z;
				
				myNormals[9*i] = ff.myNormals[0].x; myNormals[9*i+1] = ff.myNormals[0].y; myNormals[9*i+2] = ff.myNormals[0].z;
				myNormals[9*i+3] = ff.myNormals[1].x; myNormals[9*i+4] = ff.myNormals[1].y; myNormals[9*i+5] = ff.myNormals[1].z;
				myNormals[9*i+6] = ff.myNormals[2].x; myNormals[9*i+7] = ff.myNormals[2].y; myNormals[9*i+8] = ff.myNormals[2].z;
				
			}
			
			for(int i=0; i<myVertices.length; i+=3){
				Vector vv=new Vector(myVertices[i], myVertices[i+1], myVertices[i+2]);
				min.set_coords(
						(vv.x<min.x?vv.x:min.x),
						(vv.y<min.y?vv.y:min.y),
						(vv.z<min.z?vv.z:min.z));
				max.set_coords(
						(vv.x>max.x?vv.x:max.x),
						(vv.y>max.y?vv.y:max.y),
						(vv.z>max.z?vv.z:max.z));
			}
			
			myIndices=new short[f.size()*3];
			for(int i=0; i<myIndices.length; i++) myIndices[i]=(short)i;
			
			v.clear(); vn.clear(); f.clear();
			Runtime.getRuntime().gc();
			
			return System.currentTimeMillis()-now;
		}	
	
	
//	protected long load(int obj, Context context, ArrayList<Vector> v, ArrayList<Vector> f){
	protected long load(int obj, Context context){
			long now=System.currentTimeMillis();
			
			ArrayList<Vector> v=new ArrayList<Vector>();
			ArrayList<Vector> vn=new ArrayList<Vector>();
//			ArrayList<Vector> f=new ArrayList<Vector>();
			ArrayList<Face> f= new ArrayList<Face>();
			
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
//							Vector face=new Vector(nextLine);
							Face face = new Face(nextLine);
							f.add(face);
//							Vector normal= Vector.normal(v.get((int)face.x), v.get((int)face.y), v.get((int)face.z));
							Vector normal= Vector.normal(v.get(face.myVertexI[0]), v.get(face.myVertexI[1]), v.get(face.myVertexI[2]));
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
//				Vector ff=f.get(i);
//				myIndices[3*i]=(short) ff.x;
//				myIndices[3*i+1]=(short) ff.y;
//				myIndices[3*i+2]=(short) ff.z;
				Face ff=f.get(i);
				myIndices[3*i]=(short) ff.myVertexI[0];
				myIndices[3*i+1]=(short) ff.myVertexI[1];
				myIndices[3*i+2]=(short) ff.myVertexI[2];
			}
			
			for(int i=0; i<myVertices.length; i+=3){
				Vector vv=new Vector(myVertices[i], myVertices[i+1], myVertices[i+2]);
				min.set_coords(
						(vv.x<min.x?vv.x:min.x),
						(vv.y<min.y?vv.y:min.y),
						(vv.z<min.z?vv.z:min.z));
				max.set_coords(
						(vv.x>max.x?vv.x:max.x),
						(vv.y>max.y?vv.y:max.y),
						(vv.z>max.z?vv.z:max.z));
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
			long loadtime=load2(plyresource, context);
//			make(vertices, faces);		
			
//			System.out.println("Model: "+vertices.size()+" v, "+ faces.size()+" f, "+loadtime+" ms.");
			System.out.println("Model: "+myVertices.length+" v*3, "+myNormals.length+" vn*3, "+
					myVertices.length/9+" = "+myNormals.length/9+" = "+(myIndices!=null?myIndices.length/3:0)+" f "+loadtime+" ms.");
			System.out.println("Model: "+
					String.format("%.2f",min.x)+" to "+
					String.format("%.2f",max.x)+"x, "+
					String.format("%.2f",min.y)+" to "+
					String.format("%.2f",max.y)+"y, "+
					String.format("%.2f",min.z)+" to "+
					String.format("%.2f",max.z)+"z.");
			
//			vertices.clear(); faces.clear();
			Runtime.getRuntime().gc();

		}



}
