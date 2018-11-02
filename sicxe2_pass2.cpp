#include<string>
#include<bitset>
#include<string.h>
#include<sstream>
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<fstream>
#include<iomanip>
using namespace std;

int LOCCTR=0;
int STARTADRESS=0;
string SYMTAB[100][2];
int symtabsz=0;
int error=0;
int optabsz=101;
int PGM_LENGTH;
string PGM_NAME;
string OPTAB[][3]={
	{"ADD","18","3"},
	{"ADDF","58","3"},
	{"ADDR","90","2"},
	{"AND","40","3"},
	{"CLEAR","B4","2"},
	{"COMP","28","3"},
	{"COMPF","88","3"},
	{"COMPR","A0","2"},
	{"DIV","24","3"},
	{"DIVF","64","3"},
	{"DIVR","9C","2"},
	{"FIX","C4","1"},
	{"FLOAT","C0","1"},
	{"HIO","F4","1"},
	{"J","3C","3"},
	{"JEQ","30","3"},
	{"JGT","34","3"},
	{"JLT","38","3"},
	{"JSUB","48","3"},
	{"LDA","00","3"},
	{"LDB","68","3"},
	{"LDCH","50","3"},
	{"LDF","70","3"},
	{"LDL","08","3"},
	{"LDS","6C","3"},
	{"LDT","74","3"},
	{"LDX","04","3"},
	{"LPS","D0","3"},
	{"MUL","20","3"},
	{"MULF","60","3"},
	{"MULR","98","2"},
	{"NORM","C8","1"},
	{"OR","44","3"},
	{"RD","D8","3"},
	{"RMO","AC","2"},
	{"RSUB","4C","3"},
	{"SHIFTL","A4","2"},
	{"SHIFTR","A8","2"},
	{"SIO","F0","1"},
	{"SSK","EC","3"},
	{"STA","0C","3"},
	{"STB","78","3"},
	{"STCH","54","3"},
	{"STF","80","3"},
	{"STI","D4","3"},
	{"STL","14","3"},
	{"STS","7C","3"},
	{"STSW","E8","3"},
	{"STT","84","3"},
	{"STX","10","3"},
	{"SUB","1C","3"},
	{"SUBF","5C","3"},
	{"SVC","B0","2"},
	{"SUBR","94","2"},
	{"TD","E0","3"},
	{"TIO","F8","1"},
	{"TIX","2C","3"},
	{"TIXR","B8","2"},
	{"WD","DC","3"},
	


	{"+ADD","18","4"},
        {"+ADDF","58","4"},
       
        {"+AND","40","4"},
        
        {"+COMP","28","4"},
        {"+COMPF","88","4"},
        
        {"+DIV","24","4"},
        {"+DIVF","64","4"},
        
        
       
        
        {"+J","3C","4"},
        {"+JEQ","30","4"},
        {"+JGT","34","4"},
        {"+JLT","38","4"},
        {"+JSUB","48","4"},
        {"+LDA","00","4"},
        {"+LDB","68","4"},
        {"+LDCH","50","4"},
        {"+LDF","70","4"},
        {"+LDL","08","4"},
        {"+LDS","6C","4"},
        {"+LDT","74","4"},
        {"+LDX","04","4"},
	{"+LPS","D0","4"},
        {"+MUL","20","4"},
        {"+MULF","60","4"},
     
        
        {"+OR","44","4"},
        {"+RD","D8","4"},
        
        {"+RSUB","4C","4"},
        
        
     
        {"+SSK","EC","4"},
        {"+STA","0C","4"},
        {"+STB","78","4"},
        {"+STCH","54","4"},
        {"+STF","80","4"},
        {"+STI","D4","4"},
        {"+STL","14","4"},
        {"+STS","7C","4"},
        {"+STSW","E8","4"},
        {"+STT","84","4"},
        {"+STX","10","4"},
        {"+SUB","1C","4"},
        {"+SUBF","5C","4"},
       
       
        {"+TD","E0","4"},
       
        {"+TIX","2C","4"},
        
        {"+WD","DC","4"}

	};
int BASE_FLAG=0;
string BASE_V;	

int search_optab(string opcode){
	for(int i=0;i<optabsz;i++){
		if(OPTAB[i][0].compare(opcode)==0)
			return i;
	}
	return -1;
}

int search_symtab(string label){
	for(int i=0;i<symtabsz;i++){
		if(SYMTAB[i][0].compare(label)==0)
			return i;
	}
	return -1;
}
int  load_pgm_length(){
	int val;
	fstream	pgm_l;
	pgm_l.open("program_length.txt",ios::in);
	string l;
	string line;
	getline(pgm_l,line);
	stringstream ss(line);
	ss>>l>>PGM_NAME;
	pgm_l.close();
	stringstream s(l);
	s>>val;
	return val;
	
}
string padd_zero(string val){
	int ll=val.length();
	while(ll<=3){
		val="0"+val;
		ll=val.length();
	}
	return val;
}
void load_symtab(){
fstream symtab;
string symbol,val,line;
symtab.open("symbol_table.txt",ios::in);
if(symtab.is_open())
{       

		while (getline(symtab, line))
		{	if(line.compare("")==0){
				break;
			}
			stringstream ss(line);
    	
    		if(ss >> symbol>>val)
    		{
				;
		
			}
			SYMTAB[symtabsz][0]=symbol;
			SYMTAB[symtabsz][1]=padd_zero(val);
			symtabsz++;
		}
		
			
			
}
symtab.close();
}
string HEADER;
void create_header(string pgm_name,string start_address,int  length){
string out;
stringstream ss;
ss << length;
out = ss.str();
	HEADER="H^"+pgm_name+"^"+start_address+"^"+out;
}
void write_header(char argv[]){
	char ff2[20];
        int i;
        strcpy(ff2,argv);
        for(i=0;i<strlen(argv);i++){
                if(ff2[i]=='.')
                        break;
        }
        ff2[i]='.';
        ff2[i+1]='o';
        ff2[i+2]='b';
        ff2[i+3]='j';
	fstream obj;
	//obj.open(ff2,ios::out);
        obj.open(ff2,ios::app);
	obj<<HEADER<<endl;
        obj.close();
}
string OBJ_CODE;
string TEXT_REC;
int tr_length=0;
void init_tr(string loc){
	stringstream ss;
	ss<<hex<<loc;
	TEXT_REC="T^"+ss.str()+"^"+"  ";
	tr_length=0;
}

void append_tr(){
	TEXT_REC+="^"+OBJ_CODE;
	//tr_length+=OBJ_L;
}
void write_tr(char argv[]){
	stringstream stream;
	//cout<<"ll"<<tr_length<<endl;
	//cout<<"hi";
	//cout<<"\nooop"<<tr_length<<endl;
	stream << hex <<tr_length;
	
	//cout<<"length"<<x<<endl;
	string hex_v( stream.str());
	cout<<"\nhexv"<<hex_v<<endl;
	TEXT_REC.at(7)=hex_v.at(0);
	TEXT_REC.at(8)=hex_v.at(1);

	char ff2[20];
        int i;
        strcpy(ff2,argv);
        for(i=0;i<strlen(argv);i++){
                if(ff2[i]=='.')
                        break;
        }
        ff2[i]='.';
        ff2[i+1]='o';
        ff2[i+2]='b';
        ff2[i+3]='j';
	fstream obj;
	//obj.open(ff2,ios::out);
        obj.open(ff2,ios::app);
        obj<<TEXT_REC<<endl;
        obj.close();

}
int err_mm=0;
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

string displace(string source,string dest,int format){
		stringstream str;
		
		signed int x;   
		stringstream ss;
		ss << hex << source;
		ss >> x;

		
		
		signed int y;   
		stringstream dd;
		dd << hex << dest;
		dd >> y;
		
		y=y-x;
		
		
		
		stringstream res;
		string r;
		//cout<<"here"<<hex<<-20<<endl;
		if(format==3){
			if(y<0)
			{	res<<setfill('0') << setw(3)<<hex<<(y&0xfff);
				
					
			r=res.str();
			
			
			}
			else
			{	res<<setfill('0') << setw(3)<<hex<<(y&0xfff);
			r=res.str();}
			
		}
			
		else if(format==4){
			if(y<0){
			res<<setfill('0') << setw(5)<<hex<<(y&0xfffff);
			r=res.str();
			
			}
			else{res<<setfill('0') << setw(5)<<hex<<(y&0xfffff);r=res.str();}
			//int l=r.length();
			
		}


		cout<<"\nlength disp"<<res.str().length()<<endl<<endl;
		
		cout<<"actual"<<r<<endl;
		return r;
}
/*int find_comm(string operand[],int om){
	for(int i=0;i<om;i++){
		if(operand[i].compare(",")==0)
			return i;
	}
	return -1;
}*/
string char_to_hex(string operand){
	cout<<operand<<endl;
	string res="";
	char arr[20];
	strcpy(arr,operand.c_str());
	for(int i=0;i<strlen(arr);i++){
		int asc=(int)arr[i];
		stringstream ss;
		ss<<hex<<asc;
		res+=ss.str();
	}
	return res;
}
		
	

int assemble(string opcode,string operand_m[],string next){
	int err=0;
	int s_o=search_optab(opcode);
	if(s_o>=0){
		string opcode_hex_s=OPTAB[s_o][1];
		if(OPTAB[s_o][2].compare("1")==0){//format1
				OBJ_CODE+=opcode_hex_s;	
				return 1;
		}
		else if(OPTAB[s_o][2].compare("2")==0){
			if(operand_m[1].compare("A")==0){
				OBJ_CODE=opcode_hex_s+"0";
			}
			else if(operand_m[1].compare("X")==0){
				OBJ_CODE=opcode_hex_s+"1";}
			else if(operand_m[1].compare("L")==0)
				OBJ_CODE=opcode_hex_s+"2";
			else if(operand_m[1].compare("B")==0)
				OBJ_CODE=opcode_hex_s+"3";
			else if(operand_m[1].compare("S")==0)
				OBJ_CODE=opcode_hex_s+"4";
			else if(operand_m[1].compare("T")==0)
				OBJ_CODE=opcode_hex_s+"5";
			else if(operand_m[1].compare("F")==0)
				OBJ_CODE=opcode_hex_s+"6";
			else
				err=1;
			if(operand_m[3].compare("A")==0){
				OBJ_CODE+="0";
			}
			else if(operand_m[3].compare("X")==0){
				OBJ_CODE+="1";}
			else if(operand_m[3].compare("L")==0)
				OBJ_CODE+="2";
			else if(operand_m[3].compare("B")==0)
				OBJ_CODE+="3";
			else if(operand_m[3].compare("S")==0)
				OBJ_CODE+="4";
			else if(operand_m[3].compare("T")==0)
				OBJ_CODE+="5";
			else if(operand_m[3].compare("F")==0)
				OBJ_CODE+="6";
			else if(operand_m[3].compare("")==0)
				OBJ_CODE+="0";//CHECK
			else if(is_number(operand_m[3])&&(opcode.compare("SHIFTL")==0||opcode.compare("SHIFTR")==0)){
				OBJ_CODE+=operand_m[3];//CHECK
			}
				
			else
				err=1;
			return 1;
		}
		else if(OPTAB[s_o][2].compare("3")==0){
			//cout<<"for 3";
			stringstream con;
			//string s = "0xA";
    			stringstream ss;
    			ss << hex << opcode_hex_s.at(1);
    			unsigned n;
   			ss >> n;
    			bitset<4> ni(n);
			bitset<4> xbpe("0000");
			//bitset<4>ni(opcode_hex_s.at(1));
			//cout<<opcode_hex_s.at(1)<<endl;
			//cout<<ni;
			string disp;
			if(operand_m[0].compare("#")==0){
				ni.set(0);
				int si=search_symtab(operand_m[1]);
				//cout<<si;
				if(si>=0){
					disp=displace(next,SYMTAB[si][1],3);
					xbpe.set(1);//set pc rel
				}
				else if(is_number(operand_m[1]))
					disp=operand_m[1];
				else
					err=1;
				
			}
			else if(operand_m[0].compare("@")==0){
				ni.set(1);
				cout<<ni<<endl;
				int si=search_symtab(operand_m[1]);
				if(si>=0){
					disp=displace(next,SYMTAB[si][1],3);
				}
				else
					err=1;
				xbpe.set(1);//set pc rel
			}
			else if(operand_m[0].compare("")==0){
				ni.set(0);ni.set(1);
				//cout<<"ni"<<ni;
				if(operand_m[3].compare("X")==0){
					xbpe.set(3);
					
				}
				
				int si=search_symtab(operand_m[1]);
				if(si>=0){
					//cout<<"sym"<<SYMTAB[si][1];
					disp=displace(next,SYMTAB[si][1],3);
				}

				xbpe.set(1);//set pc rel
			}
			else;
			

			stringstream conv;
			conv<<hex<<ni.to_ulong();
			opcode_hex_s.replace(1,1,conv.str());
			OBJ_CODE=opcode_hex_s;
			cout<<"\n obj1:"<<OBJ_CODE<<endl<<endl;
			int xbpe1;
			string hexv;
			 stringstream tt;

			
			xbpe1=(int)xbpe.to_ulong();
			tt<<hex<<xbpe1;

			
			hexv=tt.str();
			int ll=disp.length();
			while(ll<=2){
				disp="0"+disp;
				ll=disp.length();
			}
			
			OBJ_CODE+=hexv;
			cout<<"\n obj2:"<<OBJ_CODE<<endl<<endl;
			OBJ_CODE+=disp;
			cout<<"\n obj3:"<<OBJ_CODE<<endl<<endl;
			return 1;
		}
		else if(OPTAB[s_o][2].compare("4")==0){//format 4
			bitset<4> xbpe("0001");
			stringstream sd;
    			sd << hex << opcode_hex_s.at(1);
    			unsigned n;
   			sd >> n;
    			bitset<4> ni(n);
			string disp;
			if(operand_m[0].compare("#")==0){
				ni.set(0);ni.reset(1);
				int si=search_symtab(operand_m[1]);
				if(si>=0){
					disp=SYMTAB[si][1];
				}
				else if(is_number(operand_m[1])){
					stringstream ddec(operand_m[1]);
					int n;
					ddec>>n;
					stringstream shex;
					shex<<hex<<n;
					disp=shex.str();
					//cout<<"no";
				}
				else
					err=1;
				//xbpe.set(1)=1;//set pc rel
			}
			else if(operand_m[0].compare("@")==0){
				ni.set(1);
				int si=search_symtab(operand_m[1]);
				if(si>=0){
					disp=SYMTAB[si][1];
				}
				else
					err=1;
				//xbpe.set(1);//set pc rel
			}
			else if(operand_m[0].compare("")==0){
				ni.set(0);ni.set(1);
				if(operand_m[3].compare("X")==0){
					xbpe.set(3);
					
				}
				
				int si=search_symtab(operand_m[1]);
				if(si>=0){
					disp=SYMTAB[si][1];
				}
				//xbpe.set(1);//set pc rel
			}
			else;

			stringstream conv;
			conv<<hex<<ni.to_ulong();
			opcode_hex_s.replace(1,1,conv.str());
			OBJ_CODE=opcode_hex_s;
			
			int xbpe1;
			string hexv;
			 stringstream tt;

			
			xbpe1=(int)xbpe.to_ulong();
			tt<<hex<<xbpe1;

			
			hexv=tt.str();
			int ll=disp.length();
			while(ll<=4){
				disp="0"+disp;
				ll=disp.length();
			}
			
			OBJ_CODE+=hexv;
			OBJ_CODE+=disp;
			return 1;
		}
			
			
			
			
			
	}
	else{
		//check if symb word ,byte etc
		if(opcode.compare("WORD")==0){
			unsigned n;stringstream hh;
			stringstream no(operand_m[1]);
			no>>n;
			hh<<hex<<n;
			OBJ_CODE=hh.str();
			return 1;
		}
		else if(opcode.compare("BYTE")==0){
		
			if(operand_m[1].at(0)=='X'){
				OBJ_CODE=operand_m[1].substr(2,operand_m[1].length()-3);
			}
			else if(operand_m[1].at(0)=='C'){
				OBJ_CODE=char_to_hex(operand_m[1].substr(2,operand_m[1].length()-3));
			}
			else err=1;
			return 1;
		}
			
			
	}
}
int check_fit(){
	int sz=0;
	int init=0;
	for(int i=10;i<TEXT_REC.length();i++){
		if(TEXT_REC.at(i)=='^')
		{	
				continue;
		}
		
		sz++;
	}
	tr_length=sz/2;
	if(OBJ_CODE.length()/2+tr_length>30)
		return 0;
	else
		return 1;

}
int modify(string operand,string operand_m[]){
	operand_m[0]=operand_m[1]=operand_m[2]=operand_m[3]="";
	int start=0;
	int sz=0;
	if(operand.at(0)=='#'||operand.at(0)=='@'){
			operand_m[0]=operand.at(0);
			start=1;
			
	}
	else
		operand_m[0]="";
	sz++;
	//find comma
	int comm=operand.find(",");
	
	//append each operand
	if(comm>=0){
	operand_m[sz++]=operand.substr(start,comm-1);
	operand_m[sz++]=",";
	operand_m[sz++]=operand.substr(comm+1,operand.length());
	
	}
	else{	
		operand_m[sz++]=operand.substr(start,operand.length());
		operand_m[sz++]="";
		operand_m[sz++]="";
	}
	return sz;


 }



	

	

int search_symtab_all(string operand_m[],int om){
	return 1;//to complete
}


	
	
	
int err_s=0;
string loc_next;
int done=0;
int pass2(int lineno,string loc,string loc_next,string opcode,string operand,char argv[]){
	//do here
	//cout<<"pass operand"<<operand;
//	string operand_m=operand;
	string operand_m[4];
	//int statarr[10],lst;
	int om=modify(operand,operand_m);
	
	if(lineno==1){
		create_header(PGM_NAME,operand,PGM_LENGTH);
		write_header(argv);
		//cout<<"before start";
		if(opcode.compare("START")==0)
		{	//write listing line
			init_tr(loc);
			done=0;
			return 1;
		}
		else{	//cout<<"before init tr";
			init_tr(loc);
			//cout<<"after init_tr";
			int stat=search_optab(opcode);
			if(stat>=0){//opcode found
				if(operand.compare("")!=0){

					int stat2=search_symtab_all(operand_m,om);
					if(stat2>=0){
						assemble(opcode,operand_m,loc_next);done=0;
					}
					else{
						assemble(opcode,operand_m,loc_next);done=0;
						err_s=1;
					}
				}
				else
				{	assemble(opcode,operand_m,loc_next);done=0;}
			}
			else if(opcode.compare("BYTE")==0||opcode.compare("WORD")==0){//not opcode
				assemble(opcode,operand_m,loc_next);done=0;
			}
			else if(opcode.compare("BASE")==0){
                                BASE_FLAG=1;
                                int stat4=search_symtab_all(operand_m,om);
				if(stat4>=0)
                                	//BASE_V=SYMTAB[statarr[0]][1];
				done=0;
                                return 1;

                        }
                        else if(opcode.compare("NOBASE")==0){
                                BASE_FLAG=0;done=0;
                                return 1;
                        }
			else if((opcode.compare("RESW")==0|| opcode.compare("RESB")==0)&&done!=1)
			{		write_tr(argv);
					init_tr(loc);
					done=1;
			}

                        else;

			
			if(!check_fit()){
				write_tr(argv);
				init_tr(loc);
				done=1;
			}
			append_tr();
		}
		//write listing line
		return 1;
	}
	else{//not first line
	//	cout<<"before initr";
		//init_tr(loc);
//		cout<<"after initr";
			//cout<<"operand pp"<<operand;
                        int stat=search_optab(opcode);
                        if(stat>=0){//opcode found
                                if(operand.compare("")!=0){
                                        int stat2=search_symtab_all(operand_m,om);
                                        if(stat2>=0){
						
                                               assemble(opcode,operand_m,loc_next);done=0;
                                        }
                                        else{
                                                assemble(opcode,operand_m,loc_next);done=0;
                                                err_s=1;
                                        }
                                }
                                else
                                      assemble(opcode,operand_m,loc_next);
				    
                        }
                        else if(opcode.compare("BYTE")==0||opcode.compare("WORD")==0){//not opcode
                               // look ascii for conversion  assemble(operand,"","","","","");
				assemble(opcode,operand_m,loc_next);done=0;
                        }
                        else if(opcode.compare("BASE")==0){
				BASE_FLAG=1;
				int stat4=search_symtab(operand);done=0;
				if(stat4>=0)
				//BASE_V=SYMTAB[statarr[0]][1];
				return 1;
				
			}
			else if(opcode.compare("NOBASE")==0){
				BASE_FLAG=0;done=0;
				return 1;
			}
			else if((opcode.compare("RESW")==0|| opcode.compare("RESB")==0)&&done!=1)
			{		write_tr(argv);
					done=1;
					init_tr(loc);
			}
                        if(!check_fit()){
                                write_tr(argv);
				done=1;
                                init_tr(loc);
                        }
                        append_tr();
			
			cout<<"TEXT RECORD:"<<TEXT_REC;
                }
                //write listing line
                return 1;
}
	
void write_er(string opcode,string sym_v,string loc,char argv[]){
	string ER="E^"+loc+"^"+sym_v;
	fstream out;
	//write_tr(argv);
	char ff2[20];
        int i;
        strcpy(ff2,argv);
        for(i=0;i<strlen(argv);i++){
                if(ff2[i]=='.')
                        break;
        }
        ff2[i]='.';
        ff2[i+1]='o';
        ff2[i+2]='b';
        ff2[i+3]='j';
        out.open(ff2,ios::app);
        out<<ER<<endl;
        out.close();
}



int main(int argc,char *argv[]){
	
	load_symtab();
	PGM_LENGTH=load_pgm_length();
	fstream intermediate;
	string line,loc,opcode,operand;
	int lineno=0;
	
	
	fstream obj;
	
	
	char ff2[20];
	int i;
	strcpy(ff2,argv[1]);
	for(i=0;i<strlen(argv[1]);i++){
		if(ff2[i]=='.')
			break;
	}
	ff2[i]='.';
	ff2[i+1]='o';
	ff2[i+2]='b';
	ff2[i+3]='j';
	obj.open(ff2,ios::out);
	obj.close();
	string line2;
	intermediate.open(argv[1],ios::in);
	if(intermediate.is_open())
	{       

		while (getline(intermediate, line))
		{	lineno++;
			if(line.compare(" ")==0){
				write_tr(argv[1]);
				//fstream pgml;
				//pgml.open("program_length.txt",ios::out);
				
				//PGMLENGTH=LOCCTR-STARTADRESS;
				//stringstream ss5;
				//ss5<< hex << PGMLENGTH; 
				//string res_pgmlength ( ss5.str() );
				//cout<<"\n program length"<<res_pgmlength<<endl;
				//pgml<<res_pgmlength<<endl;
				//pgml.close();
				break;
				}
			
			//cout<<"length"<<line.length();
			cout<<"\nAssembling the instruction:"<<line<<"line no"<<lineno<<endl;
				
			
			if(line.at(0)=='.')
				continue;
			//cout<<"bb";
    			stringstream ss6(line);
		//cout<<"hikkk";	
    string last;
    			if(ss6 >> loc >> opcode >> operand){
				loc=padd_zero(loc);
		//		cout<<"read loc"<<loc;
    				getline(intermediate,line2);
		//		cout<<"next line:"<<line2;
				stringstream gg(line2);
				gg>>loc_next;
		//		cout<<"loc_next"<<loc_next;
				intermediate.seekg(-1*(line2.length()+1),ios::cur);
				;
		
			}
			else{	ss6>>opcode>>operand;
		//		cout<<"read loc"<<loc;
                                getline(intermediate,line2);
                                stringstream gg(line2);
                                gg>>loc_next;
				loc_next=padd_zero(loc_next);
                  //              cout<<"loc_next"<<loc_next;
                                intermediate.seekg(-1*(line2.length()+1),ios::cur);
		//		cout<<"hi";
				}

			/*else{
				intermediate.seekg(-1*line.length(),ios::cur);
				getline(intermediate,line);
				stringstream ss(line);
				opcode="";operand="";
				ss>>opcode>>operand;
				loc="";
					//cout<<"here";
				
				//else{
					cout<<"here"<<endl<<endl;
					source.seekg(-1*(line.length()),ios::cur);
					getline(source,line);
					stringstream ss2(line);
					ss2>>opcode
						label="";operand="";
					

				//}

			}*/
			
			//cout<<"label:"<<label<<"opcode:"<<opcode<<"operand:"<<operand<<endl;
			//ss6.close();
		//	cout<<"operand before call"<<operand;
			int p=pass2(lineno,loc,loc_next,opcode,operand,argv[1]);
			if(p==0){//update_block_table();
			 break;}
		//	cout<<"hello";
			//for(int i=0;i<block_sz;i++)
                        //	cout<<PGBLOCK[i]<<"\t"<<PGBLOCK[i]<<"\t"<<PGBLOCK[i]<<"\t"<<PGBLOCK[i]<<endl;

			//update_block_table();
			

    		
		}

		intermediate.close();
		int stat;
		if(operand.compare("")!=0){
			stat=search_symtab(operand);
			write_er(opcode,SYMTAB[stat][1],loc,argv[1]);
		}
		else
			write_er(opcode,"0",loc,argv[1]);
		
		
	}
	else cout<<"unable to open source file";
	
	
	
	return 0;

}



