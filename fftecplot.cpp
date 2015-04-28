#include <ff++.hpp>
#include "AFunction_ext.hpp"
#include "TECIO.h"
using namespace Fem2D;
double savetec(string* const& file, Mesh* const& pTh,KN<double>* const& uh,string* const& varname)
{
	string shape;
  ofstream pf((*file).c_str());
  size_t n, m;
  Mesh& Th = *pTh;
  
  pf << "TITLE = \" \"\n";
  pf << "VARIABLES = \"X\", \"Y\"";
  if (Th.dim==3)
    pf << ", \"Z\"";
  pf <<",\" "<< *varname <<"\""<< endl;
  if (Th.dim==2) {
    m = 3;
    shape = "TRIANGLE";
  }
  /*      else if (el->getShape()==LINE) {
	  m = 2;
	  shape = "LINESEG";
	  }
  */
  
  else if (Th.dim==3)
	 {
	   m = 4;
	   shape = "TETRAHEDRON";
	 }
  
  pf << "ZONE N=" << Th.nv  << ", E=" << Th.nt << ", F=FEPOINT, ET=" << shape << endl;
  for (int i=0;i<Th.nv;i++)
    pf << std::setprecision(5) << setw(18) << (R2) Th(i)  << " " << (*uh)[i] <<" \n" ;
  
  
  for (int k=0;k<Th.nt;++k)
    {
      for (n=0; n<m; n++)
	pf << Th(k,n)+1  << "  ";
      pf << endl;
    }
  
  pf.close();
	return 0;
}
double saveTecplot(string* const& file, Mesh* const& pTh,KN<double>* const& uh)
{
		 string shape;
  ofstream pf((*file).c_str());
  size_t n, m;
  Mesh& Th = *pTh;
  
  pf << "TITLE = \" \"\n";
  pf << "VARIABLES = \"X\", \"Y\"";
  if (Th.dim==3)
    pf << ", \"Z\"";
  pf <<", "<< "\"uh\"" << endl;
  if (Th.dim==2) {
    m = 3;
    shape = "TRIANGLE";
  }
  /*      else if (el->getShape()==LINE) {
	  m = 2;
	  shape = "LINESEG";
	  }
  */
  
  else if (Th.dim==3)
	 {
	   m = 4;
	   shape = "TETRAHEDRON";
	 }
  
  pf << "ZONE N=" << Th.nv  << ", E=" << Th.nt << ", F=FEPOINT, ET=" << shape << endl;
  for (int i=0;i<Th.nv;i++)
    pf << std::setprecision(5) << setw(18) << (R2) Th(i)  << " " << (*uh)[i] <<" \n" ;
  
  
  for (int k=0;k<Th.nt;++k)
    {
      for (n=0; n<m; n++)
	pf << Th(k,n)+1  << "  ";
      pf << endl;
    }
  
  pf.close();
	return 0;
}

double savetec_b(string* const& file, Mesh* const& pTh,KN<double>* const& uh, string* const& valname)
{
  // 提取网格数据
	
	Mesh& th = *pTh;
	double* x = new double[th.nv];
	double* y = new double[th.nv];
	double* u = new double[th.nv];
 	INTEGER4* cont = new INTEGER4[3*th.nt];
	for (int j=0;j<th.nt;j++){
		for (int i=0;i<3;i++){
			cont[j*3+i]=th(j,i)+1;
		//	cout<< cont[j*3+i] << " ";
		}
		//cout << endl;
	}

	// data 
	
	for (int j=0;j<th.nv;j++){
		x[j] = th.v(j).x;
		y[j] = th.v(j).y;
		u[j] = (*uh)[j];
		//cout << data[0*th.nv + j] << " "	;	
		//cout << data[1*th.nv + j] << " "	;	
		//cout << data[2*th.nv + j] << endl;		
	}

	INTEGER4 Debug = 1;
	INTEGER4 VIsDouble = 0;
	INTEGER4 FileFormat = 0; // 0 == PLT, 1 == SZPLT
	INTEGER4 FileType = 0;
	INTEGER4 I = 0; 

	// 设置
	I = TECINI142(
			(char*)"Freefem++2tecplot",
			(char*)"X Y U",
			file->c_str(),
			(char*)".",
			&FileFormat,
			&FileType,
			&Debug,
			&VIsDouble
			);
	INTEGER4 zonetype = 2;
	INTEGER4 np = th.nv;
	INTEGER4 nt = th.nt;
	INTEGER4 KMxOrNumFaces = 0;
	INTEGER4 ICellMax = 0;
	INTEGER4 JCellMax = 0;
	INTEGER4 KCellMax = 0;
	double SolutionTime= 0.0;
	INTEGER4 StrandID = 0;
	INTEGER4 ParentZone = 0;
	INTEGER4 IsBlock = 1;
	INTEGER4 NumFaceConnections = 0;
	INTEGER4 FaceNeighborMode = 0;
	INTEGER4 TotalNumFaceNodes = 0;
	INTEGER4 NumConnectedBoundaryFaces = 0;
	INTEGER4 TotalNumBoundaryConnections = 0;
	INTEGER4 PassiveVarList;
	INTEGER4 ValueLocation;
	INTEGER4 ShareVarFromZone = 0;
	INTEGER4 ShareConnectivityFromZone = 0;
	//cout << "init" << endl;
	//cout << np <<endl;
	//cout << th.nt <<endl;

	I = TECZNE142(  // 设置zone的属性
			file->c_str(),
			&zonetype,
			&np,
			&nt,
			&KMxOrNumFaces ,
			&ICellMax, 
			&JCellMax,
			&KCellMax,
			&SolutionTime,
			&StrandID,
			&ParentZone,
			&IsBlock, 
			&NumFaceConnections,
			&FaceNeighborMode,
			&TotalNumFaceNodes,
			&NumConnectedBoundaryFaces,
			&TotalNumBoundaryConnections,
			NULL,
			NULL,
			&ShareVarFromZone,
			&ShareConnectivityFromZone
			);
	//cout << "zone" << endl;
	INTEGER4 N=np;
	INTEGER4 isdouble=1;


	// 填入数据 有限元数据或顺序数据
	I = TECDAT142(&N,x,&isdouble);
	I = TECDAT142(&N,y,&isdouble);
	I = TECDAT142(&N,u,&isdouble);
	//cout << "dat" << endl;
			//or TECNODE142  // 填入有限元网格数据
	I = TECNOD142(cont);
	//cout << "nod" << endl;
	I = TECEND142();

	delete [] x;
	delete [] y;
	delete [] u;
	delete [] cont;
	return 1;
}

//   add the function name to the freefem++ table 
class Init { public:
	Init();
};
LOADINIT(Init);
Init::Init(){
	// Add function with 3 arguments
	//  Global.Add("funcs1","(",new OneOperator1s_<double, double>(funcs1)); 
	//  Global.Add("funcs2","(",new OneOperator2s_<double, double, double >(funcs2)); 
	//  Global.Add("funcs3","(",new OneOperator3s_<double, double, double, double  >(funcs3)); 
	Global.Add("savetec","(",new OneOperator3_<double, string*, Mesh*,KN<double>*>(saveTecplot)); 
	Global.Add("savetec","(",new OneOperator4_<double, string*, Mesh*,KN<double>*,string*>(savetec)); 
	Global.Add("savetecb","(",new OneOperator4_<double, string*, Mesh*,KN<double>*,string*>(savetec_b)); 
	//Global.Add("CppModTemplate4","(",new OneOperator4_<double, KN<double>*, KN<double>*, KN<double>*, KN<double>*>(CppModTemplate4)); 
	//Global.Add("CppModTemplate5","(",new OneOperator5_<double, KN<double>*, KN<double>*, KN<double>*, KN<double>*, KN<double>*>(CppModTemplate5)); 
	//Global.Add("CppModTemplate6","(",new OneOperator6_<double, KN<double>*, KN<double>*, KN<double>*, KN<double>*, KN<double>*, KN<double>*>(CppModTemplate6)); 
	//Global.Add("CppModTemplate7","(",new OneOperator7_<double, KN<double>*, KN<double>*, KN<double>*, KN<double>*, KN<double>*, KN<double>*, KN<double>*>(CppModTemplate7)); 
	//Global.Add("CppModTemplate8","(",new OneOperator8_<double, KN<double>*, KN<double>*, KN<double>*, KN<double>*, KN<double>*, KN<double>*, KN<double>*, KN<double>*>(CppModTemplate8)); 
}
