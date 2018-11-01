
#include<string>
#include<bitset>
#include<string.h>
#include<sstream>
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include <iomanip>
#include<fstream>
using namespace std;
string operand_m[]={"","X'F1'",",",""};
int optabsz=101;
int symtabsz=5;
string SYMTAB[][2]={{"RETADR","0030"},{"LENGTH","0033"},{"RDREC","1036"},{"WRREC","105D"},{"BUFFER","0036"}};
string next1="0030";
string opcode="BYTE";
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
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
string displace(string source,string dest,int format){
		stringstream str;
		
		unsigned int x;   
		stringstream ss;
		ss << hex << source;
		ss >> x;
		
		unsigned int y;   
		stringstream dd;
		dd << hex << dest;
		dd >> y;
		y=y-x;
		
		stringstream res;
		res<<setfill('0') << setw(3)<<hex<<y;



		
		
		return res.str();
}
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
		
	
string OBJ_CODE="";
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
			
			int xbpe1;
			string hexv;
			 stringstream tt;

			
			xbpe1=(int)xbpe.to_ulong();
			tt<<hex<<xbpe1;

			
			hexv=tt.str();
			int ll=disp.length();
			while(ll<=3){
				disp="0"+disp;
				ll=disp.length();
			}
			
			OBJ_CODE+=hexv;
			OBJ_CODE+=disp;
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
			while(ll<=5){
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
int main(){
		assemble(opcode,operand_m,next1);
	cout<<OBJ_CODE;
return 1;
}	
	
	


	


