#include "Polygon.h"

// Default. Null polygon.
Polygon::Polygon():
	num_vertices(0),
	num_faces(0),
	max_cells_per_face(0),
	loaded(false),
	outdated(true),
	silent(false)
	{geometry_vertices=NULL; geometry_faces=NULL; geometry_normals=NULL;}

// Unload before destroying.
Polygon::~Polygon() { if (is_loaded()) unload(); }

// Impose silence.
void Polygon::silence(bool on) { silent=on; return; }

// Parse geometry file. Under normal circumstances an open file with its pointer at the beginning will be passed to this function.
bool Polygon::parse(fstream& file)
{
	int vertices=0, faces=0, max=0;
	string s;

	// Check header.
	file >> s;
	if (s=="vertices")
	{
		// Count and skim through vertex data.
		do vertices++; while ((file >> s)&&(s!="faces"));

		// If unknown identifier or uneaven vertex data (more or less identifiers than needed for all the vertices to be 3D)
		if ((s!="faces")||(--vertices % 3!=0)) {cout << endl << "Invalid file!" << endl;  file.close(); return false;}

		// Multitude of vertices.
		vertices=vertices/3;

		// Skim through face data, count faces and find the maximum number of cells needed to describe a face.
		// The face header which signifies the number of vertices per face must be an integer greater than or equal to 3.
		int i, j;
		while ((file>>j)&&(j>=3)){
			if (max < j) max=j;

			// If not as many vertices as face header signifies, fail.
			for (i=1;i<=j;i++) if(!(file >> s)) {cout << endl << "Invalid file!" << endl; file.close(); return false;}
			faces++;
		}

		// If no face data or less than 3 vertices per face, fail.
		// If at this point an invalid face header (a string) has been encountered,
		// as j is an integer, (file >> j) above will fail and that face together with those that follow it
		// will be ignored. However we must be sure that we have read at least one face.
		if ((faces==0)||(j<3)) {cout << endl << "Invalid file!" << endl; file.close(); return false;}
	}
	
	// Invalid header.
	else {cout << endl << "Invalid file!" << endl; file.close(); return false;}
	// Maximum number of cells needed per face is the number of vertices of the face with the most vertices
	// plus one for that number itself.
	max++;
	set_vertices(vertices);
	set_faces(faces);
	set_max(max);
	return true;
}

// Load geometry file. Under normal circumstances, an open file with its pointer to the beginning should be passed to this function.
void Polygon::load(fstream& file)
{
	string s;
	float x, y, z;
	int i, j, f;
	
	// This should be the header of the file.
	file >> s;

	// Read vertices. Note that, to make sure numbers are read as expected, atof is used.
	// This means that, should there be invalid data - which parsing overlooked,
	// as it was more interested in finding the proper multitude of identifiers -
	// the value stored will be zero.
	for(i=0;i<num_vertices;i++){
		file >> s; x=(float)atof(s.c_str()); file >> s; y=(float)atof(s.c_str()); file >> s; z=(float)atof(s.c_str());
		geometry_vertices[i].set_coords(x,y,z);
	}

	// Skip faces section header.
	file >> s;
	i=0;
	
	// Read faces. As above, strings are converted to numbers, integers this time.
	// If there is invalid input in the file, it will be perceived as zero.
	// The face array <geometry_faces> is a one-dimensional array of length max_cells_per_face*num_faces.
	while(i<num_faces){
		file >> s;
		f=atoi(s.c_str());
		geometry_faces[i*max_cells_per_face]=f;
		for(j=1; j<=f; j++) {file >> s; geometry_faces[i*max_cells_per_face+j]=atoi(s.c_str());}
		i++;
	}

	// There is a polygon in memory now.
	loaded=true;

	// The unit normals are obsolete.
	outdated=true;
	return;
}

// The overall process of loading geometry file <name> into memory.
bool Polygon::load(string name)
{
	// Test if file can be opened.
	fstream in(name,ios::in);		
	if (in.fail()) {cout <<"Unable to open " << name << "!" << endl; return false;}

	// If there is previous geometry data in memory, reset the polygon.
	if (loaded) unload();

	// Parse the geometry file. If this fails, the process cannot continue.
	if (!parse(in)) return false;

	// Allocate space for polygon data.
	geometry_vertices=new Vertex[num_vertices];
	geometry_faces=new int[num_faces*max_cells_per_face];
	geometry_normals=new Vector[num_faces];

	// Reset the input file.
	in.clear();
	in.seekg(0, ios::beg);

	// Read data into memory.
	load(in);	
	in.close();
	return true;
}

// Reset polygon data.
bool Polygon::unload()
{
	// No polygon in memory.
	if (!loaded) return false;

	// Free allocated memory for geometry data.
	if (geometry_vertices!=NULL) {delete[] geometry_vertices; geometry_vertices=NULL;}
	if (geometry_faces!=NULL) {delete[] geometry_faces; geometry_vertices=NULL;}
	if (geometry_normals!=NULL) {delete[] geometry_normals; geometry_vertices=NULL;}
	
	// Set status
	loaded=false;
	outdated=true;

	// Set sizes
	num_vertices=0;
	num_faces=0;
	max_cells_per_face=0;
	return true;
}

// Save geometry data.
bool Polygon::save_geometry(string name)
{
	bool flag=false;
	char c;
	fstream out;

	// There must be data in memory to save.
	if (!loaded) {cout << "No data in memory! Nothing to save!"; return false;}

	// If the designated output file exists and we are not in silent mode, ask to overwrite.
	if (!silent){
		
		// Open file for reading to check if it exists.
		out.open(name, ios::in);
		flag=!(!out);
		if (flag){
			out.close();
			
			// The user must give either their assent by a y or their refusal by a n.
			do cout << endl << "File exists. Overwrite (y/n)? "; while ((c=_getch()) && (c!='y') && (c!='n'));
			cout << endl;
			if (c=='n') return false;
		}
	}
	flag=false;

	// Open for writing.
	out.open(name, ios::out | ios:: trunc);
	flag=!(!out);

	// Cannot write.
	if (!flag) {cout << "Cannot write to file!"; return false;}

	// Suppress output to user, if in silent mode.
	if (!silent) cout << "Saving " << name << ". Please be patient; this may take some time... " << endl;
	
	// Save vertex data.
	save_vertices(out);

	// Save face data.
	save_faces(out);
	out.close();
	return true;
}

// Save the unit normals to file <name>.
bool Polygon::save_normals(string name)
{
	bool flag=false;
	char c;
	fstream out;

	// There must be a polygon in memory.
	if (!loaded) {cout << "No data in memory! Nothing to save!"; return false;}

	// The polygon's unit normals must not be obsolete.
	if (outdated) {cout << "Unit normals in memory are outdated! Aborting."; return false;}

	// Suppress interaction with the user if in silent mode. Same as the saving of the geometry file.
	if (!silent){
		out.open(name, ios::in);
		flag=!(!out);
		if (flag){
			out.close();
			do cout << endl << "File exists. Overwrite (y/n)? "; while ((c=_getch()) && (c!='y') && (c!='n'));
			cout << endl;
			if (c=='n') return false;
		}
	} 
	flag=false;
	out.open(name, ios::out | ios:: trunc);
	flag=!(!out);
	
	// Unable to write to file.
	if (!flag) {cout << "Cannot write to file!"; return false;}
	if (!silent) cout << "Saving " << name << ". Please be patient; this may take some time... " << endl;
	out << "normals" << endl;
	for (int i=0; i<get_faces(); i++)
		
		// If an invalid face has been read, the unit normal magnitude will not be 1, but most likely 0.
		if(geometry_normals[i].get_magn()!=1) out << "INVALID FACE" << endl;

		else out << geometry_normals[i].getx() << ' ' << geometry_normals[i].gety() << ' ' << geometry_normals[i].getz() << endl;
	out.close();
	return true;
}

// Output geometry data to the screen.
bool Polygon::print()
{
	char c='1';

	// Must have data to display.
	if (!loaded) {cout << "No data in memory! Nothing to display!" << endl; return false;}
	system("cls");
	
	// Vertex output.
	cout << "=== " << get_vertices() << " VERTICES ===" << endl << endl;

	// Vertices are displayed in sets of 20.
	for(int i=0; i<get_vertices(); i++){
		cout << i+1 << " / " << get_vertices() << ": ("
			<< geometry_vertices[i].getx() << ", "
			<< geometry_vertices[i].gety() << ", "
			<< geometry_vertices[i].getz() << ")" << endl;
		
		// If ESC has not been pressed (therefore paged output) and 20 vertices have been displayed,
		// end page and wait for the user to press a key.
		if((c!=27)&&((i+1) % 20 == 0)){
			cout << endl << "=== Page " << (i+1)/20 << " of " << ceil((float) get_vertices() / (float) 20) << " ===";
			cout << endl << "Press a key to continue; ESC to skip verbose mode (irreversible action)... ";
			c=_getch();
			system("cls");
		}
	}

	// If in paged mode, end last page.
	if(c!=27) cout << endl << "=== Page " <<  ceil((float) get_vertices() / (float) 20) << " of " << ceil((float) get_vertices() / (float) 20) << " ===" << endl;
	
	cout << endl << "Press a key to continue; ESC to skip verbose mode (irreversible action)... ";
	c=_getch();
	system("cls");
	
	// Face output.
	cout << "=== " << get_faces() << " FACES ===" << endl << endl;

	// Faces are displayed in sets of 15. As above.
	for(int i=0; i<get_faces(); i++){
		cout << i+1 << " / " << get_faces() << ": [";
		for(int j=1;j<=geometry_faces[i*get_max()];j++) cout << geometry_faces[i*get_max()+j] << ", ";
		cout << "\b\b] (" << geometry_faces[i*get_max()] << " vertices)" << endl;
		if((c!=27)&&((i+1) % 15 == 0)){
			cout << endl << "=== Page " << (i+1)/15 << " of " << ceil((float) get_faces() / (float) 15) << " ===" << endl
				<< "Press a key to continue; ESC to skip verbose mode (irreversible action)... ";
			c=_getch();
			system("cls");
		
		}
	}
	if(c!=27) cout << endl << "=== Page " <<  ceil((float) get_faces() / (float) 15) << " of " << ceil((float) get_faces() / (float) 15) << " ===" << endl;
	
	// End print.
	cout << "Press a key to continue ...";
	_getch();
	system("cls");
	return true;
}

// Translate all vertices by a position vector.
bool Polygon::translate(Vector v)
{
	// There must be a polygon in memory.
	if (!is_loaded()) return false;

	// Translating by (0,0,0) has no effect on the polygon.
	if(v.get_magn()==0) return true;

	// Translate each vertex by vector <v>.
	for(int i=0;i<get_vertices(); i++) geometry_vertices[i].translate((Vertex) v);
	return true;
}

// Uniform scaling.
bool Polygon::scale(float scalar)
{
	// There must be a polygon in memory.
	if (!is_loaded()) return false;

	// It will ruin the polygon to scale it by 0.
	if(scalar==0) return false;

	// Scaling by 1 has no effect on the polygon.
	if(scalar==1) return true;

	// Scale all vertices by <scalar>.
	for(int i=0;i<get_vertices(); i++) geometry_vertices[i].scale(scalar);
	return true;
}


// Rotate the polygon around axis of vector <v> by angle <angle> in degrees.
bool Polygon::rotate(Vector v, float angle)
{
	// There must be a polygon in memory.
	if (!is_loaded()) return false;

	// Cannot rotate around (0,0,0).
	if(v.get_magn()==0) return false;

	// Rotating by zero angle has no effect on the shape.
	if(angle==0) return true;

	// The axis of the vector supplied is what we need. Therefore the vector must be normalised.
	v.unit();

	// Convert angle to radians.
	angle=(float)(angle*3.1415926535897932384626433832795)/(float)180;

	// The rotation of a vertex is implemented as three dot products
	// of the vertex' position vector and three rotation vectors,
	// the rows of a rotation matrix. They must be computed at this point.
	compute_rotation_vectors(v,angle);

	// Rotate each vertex.
	for(int i=0; i<get_vertices(); i++) geometry_vertices[i]=rotate(geometry_vertices[i]);
	outdated=true;
	return true;
}

// Calculate unit normals.
bool Polygon::normals()
{
	// There must be a polygon in memory.
	if (!is_loaded()) return false;

	// If the normals are up-to-date, there is no need to calculate them again.
	if (!outdated) return true;

	// For all faces, calculate the unit normal from the position vectors
	// of their first three vertices.
	for (int i=0; i<get_faces();i++){
		Vector v1=geometry_vertices[geometry_faces[get_max()*i+1]];
		Vector v2=geometry_vertices[geometry_faces[get_max()*i+2]];
		Vector v3=geometry_vertices[geometry_faces[get_max()*i+3]];
		geometry_normals[i]=normal(v1, v2, v3);
	}

	// The normals are up to date now.
	outdated=false;
	return true;
}

// Get methods

int Polygon::get_vertices() {return num_vertices;}

int Polygon::get_faces() {return num_faces;}

int Polygon::get_max() {return max_cells_per_face;}

// Set methods

void Polygon::set_vertices(int verts) {num_vertices=verts; return;}

void Polygon::set_faces(int faces) {num_faces=faces; return;}

void Polygon::set_max(int max) {max_cells_per_face=max; return;}

// Status query.

bool Polygon::is_loaded() {return loaded;}

bool Polygon::is_outdated() {return outdated;}


// Compute the vectors used to rotate the vertices.
void Polygon::compute_rotation_vectors(Vector u, float theta)
/*
The vectors calculated here are in essence the rows of the following generic rotation matrix:

[ costh + ux^2(1-costh)		ux*uy(1-costh) - uz*costh	ux*uz(1-costh) + uy*sinth ]
[ uy*ux(1-costh) + uz*sinth		costh + uy^2(1-costh)	uy*uz(1-costh) - ux*sinth ]
[ uz*ux(1-costh) - uy*sinth	uz*uy(1-costh) + ux*costh		costh + uz^2(1-costh) ],

for a unit vector u=(ux, uy, uz) and an angle th.

For the purposes of this project, this formula has been supplied by Wikipedia
*/
{
	float costh=cos(theta), oneminuscosth=1-costh, sinth=sin(theta);
	float uxsq=u.getx()*u.getx(), uysq=u.gety()*u.gety(), uzsq=u.getz()*u.getz();
	float uxuy=u.getx()*u.gety(), uxuz=u.getx()*u.getz(), uyuz=u.gety()*u.getz();
	rotation_vectors[0].set_coords(costh+uxsq*oneminuscosth,uxuy*oneminuscosth-u.getz()*sinth,uxuz*oneminuscosth+u.gety()*sinth);
	rotation_vectors[1].set_coords(uxuy*oneminuscosth+u.getz()*sinth,costh+uysq*oneminuscosth,uyuz*oneminuscosth-u.getx()*sinth);
	rotation_vectors[2].set_coords(uxuz*oneminuscosth-u.gety()*sinth,uyuz*oneminuscosth+u.getx()*sinth,costh+uzsq*oneminuscosth);	
	return;
}

// Get method.
Vector Polygon::get_rotation_vector(char axis)
{
	switch(axis){
		case 'x': return rotation_vectors[0];
		case 'y': return rotation_vectors[1];
		case 'z': return rotation_vectors[2];
	}
	return Vector::Vector();
}

// The rotation of a vertex. The new coordinates are the dot products of its position vector and the rotation vectors.
Vertex Polygon::rotate(Vertex v)
{	
	return (Vertex) Vector::Vector(dot(rotation_vectors[0],(Vector)v),dot(rotation_vectors[1],(Vector)v),dot(rotation_vectors[2],(Vector)v));
}

// Write vertex data to a file. Under normal circumstances, an open file with its pointer set appropriately will be passed to this function.
void Polygon::save_vertices(fstream& file)
{
	file << "vertices" << endl;
	for (int i=0; i<get_vertices(); i++) file << geometry_vertices[i].getx() << ' ' << geometry_vertices[i].gety() << ' ' << geometry_vertices[i].getz() << endl;
	return;
}

// Write face data to a file. Under normal circumstances, an open file with its pointer set appropriately will be passed to this function.
void Polygon::save_faces(fstream& file)
{
	file << "faces" << endl;
	for(int i=0; i<get_faces(); i++){
		file << geometry_faces[i*get_max()];
		for(int j=1;j<=geometry_faces[i*get_max()];j++) file << ' ' << geometry_faces[i*get_max()+j];
		file << endl;
	}
	return;
}

